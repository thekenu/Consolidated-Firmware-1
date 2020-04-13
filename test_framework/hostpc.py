import cantools
import can
import os
import time
import json
import argparse
import pprint
import asyncio
from termcolor import colored

def _get_signal_id(mock_signal_lut, signal_name):
    """
    Given a signal name, return the corresponding mock signal ID
    """
    for mock_signal in mock_signal_lut:
        if mock_signal['signal_name'] == signal_name:
            return mock_signal['signal_id']

    raise Exception('Could not find signal in the list of available mock signals')

def _get_message_by_signal_name(dbc, signal_name):
    """
    Given a signal name, find the message in the DBC containing the signal
    """
    for message in dbc.messages:
        for signal in message.signals:
            if signal_name == signal.name:      
                return message

    raise Exception(
            'Could not find any message containing signal <{}> in the DBC'.format(signal_name))

def _get_expected_fault_signal(
        value,
        fault_threshold,
        is_fault_above_threshold,
        is_fault_active_high):

    expected_fault_signal = 0 # Placeholder value
    if is_fault_above_threshold == True:
        if value > fault_threshold:
            # Expecting a fault
            expected_fault_signal = 1 if is_fault_active_high == True else 0
        else:
            # Not expecting a fault
            expected_fault_signal = 0 if is_fault_active_high == True else 1
    else:
        if value > fault_threshold:
            # Not expecting a fault
            expected_fault_signal = 0 if is_fault_active_high == True else 1
        else:
            # Expecting a fault
            expected_fault_signal = 1 if is_fault_active_high == True else 0

    return expected_fault_signal

def dbc_init(dbc):
    return cantools.database.load_file(dbc)

def can_init(can_bustype, can_bitrate, can_channel):
    """
    can_bustype: String
    can_bitrate: Integer
    can_channel: String
    """
    os.system("sudo ip link set {} type can bitrate {}".format(can_channel, can_bitrate))
    os.system("sudo ip link set up {}".format(can_channel))
    return can.interface.Bus(bustype=can_bustype, channel=can_channel, bitrate=can_bitrate)

def plot_csv(csv, signal):
    """
    Plot the csv data for the given signal
    """
    data = pd.read_csv(csv)
    x = data['timestamp']
    y = data['value']

    plt.cla() # Clear the plot each time to avoid overlapping lines
    
    plt.plot(x, y, label='Signal Value')
    plot.legeng(loc='upper left')
    plt.tight_layout() # FIXME: Is this distracting?


async def test_cb(bus, dbc, test, reader, mock_signal_lut):
    fault_threshold = test['Threshold_Value']
    start_value = test['Start_Value']
    end_value = test['End_Value']
    step_value = test['Step_Value']
    
    signal_injection_msg = dbc.get_message_by_name('SIGNAL_INJECTION')
    signal_id = _get_signal_id(mock_signal_lut, test['Mock_CAN_Signal_Name'])

    # Send message for each value
    for value in range(start_value, end_value, step_value):
        print(colored(
            "{} [INJECT] {} = {}".format(test['Test_Name'], test['Mock_CAN_Signal_Name'], str(value)),
            'yellow'))

        # Inject signal value
        signal_injection_payload = signal_injection_msg.encode({
            'Value': value,
            'Signal_ID': signal_id,
            'Enable_Override': 1,})
        start_message = can.Message(
            arbitration_id = signal_injection_msg.frame_id,
            data = signal_injection_payload,
            is_extended_id = False)
        bus.send(start_message)
    
        # @warning: The message reception is built with the assumption that
        #           the device-under-test will be continuously broadcasting
        #           message! If it doesn't, the test will block and never
        #           complete (TODO: Validate it really doesn't complete)
        
        # Drop all the received message for 1 second
        start_ms = int(round(time.time() * 1000))
        delay_ms = 1000
        while (int(round(time.time() * 1000)) - start_ms) < delay_ms:
            received_message = await reader.get_message()
          
        # Wait until we received the message containing the fault signal
        fault_message = _get_message_by_signal_name(
            dbc,
            test['Fault_CAN_Signal_Name'])
        while received_message.arbitration_id != fault_message.frame_id:
            received_message = await reader.get_message()

        # Calculate the expected fault signal value
        expected_fault_signal = _get_expected_fault_signal(
            value,
            fault_threshold,
            test['Fault_Above_Threshold_(T/F)'],
            test['Fault_Active_High_(T/F)'])
        print(colored(
            "{} [EXPECT] {} = {}".format(test['Test_Name'],
                                         test['Fault_CAN_Signal_Name'],
                                         expected_fault_signal),
            'blue'))

        # Check what fault signal value we measured
        decoded_message = dbc.decode_message(
            received_message.arbitration_id,
            received_message.data)
        fault_signal = decoded_message[test['Fault_CAN_Signal_Name']]
        print(colored(
            "{} [ACTUAL] {} = {}".format(test['Test_Name'],
                                         test['Fault_CAN_Signal_Name'],
                                         fault_signal),
            'blue'))

    # Stop injecting signal
    stop_message_payload = signal_injection_msg.encode({
       'Value': 0, # This field is ignored so it's given an arbitrary value
       'Signal_ID': signal_id,
       'Enable_Override': 0})
    stop_message = can.Message(
        arbitration_id = signal_injection_msg.frame_id,
        data = stop_message_payload,
        is_extended_id = False)
    bus.send(stop_message)
    
async def run_tests(bus, tests, dbc, mock_signal_lut):
    readers = {}
    for test in tests:
        readers[test['Test_Name']] = can.AsyncBufferedReader()

    loop = asyncio.get_event_loop()

    # To pass the readers into the Notifier, we must convert it into a list.
    # Note that the order doesn't matter as long as each test gets an
    # unique reader. So we simply use list(myDict.value()) for conversion.
    notifier = can.Notifier(bus, list(readers.values()), loop=loop)

    await asyncio.gather(
            *(test_cb(bus, dbc, test, readers[test['Test_Name']], mock_signal_lut)
            for test in tests))

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--test_json')
    parser.add_argument('--signal_json')
    parser.add_argument('--dbc')
    args = parser.parse_args()

    with open(args.test_json) as f:
      tests = json.load(f)['Tests']

    with open(args.signal_json) as f:
        mock_signal_lut = json.load(f)['Mock_Signals']

    bus = can_init('socketcan', 500000, 'vcan0')
    dbc = dbc_init(args.dbc)

    loop = asyncio.get_event_loop()
    loop.run_until_complete(run_tests(bus, tests, dbc, mock_signal_lut))
    loop.close()


if __name__ == '__main__':
    main()
