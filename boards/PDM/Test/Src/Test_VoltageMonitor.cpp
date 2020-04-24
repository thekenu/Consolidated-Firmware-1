#include <math.h>
#include "Test_VoltageMonitor.h"

extern "C"
{
#include "App_VoltageMonitor.h"
}

FAKE_VALUE_FUNC(float, get_voltage);
FAKE_VALUE_FUNC(float, get_min_voltage);
FAKE_VALUE_FUNC(float, get_max_voltage);
FAKE_VOID_FUNC(error_callback, struct VoltageMonitor *);

class VoltageMonitorTest : public PdmTest
{
  protected:
    virtual void SetUp()
    {
        voltage_monitor = App_VoltageMonitor_Create(
            get_voltage, get_min_voltage, get_max_voltage, error_callback);

        RESET_FAKE(get_voltage);
        RESET_FAKE(get_min_voltage);
        RESET_FAKE(get_max_voltage);
        RESET_FAKE(error_callback);

        FFF_RESET_HISTORY();
    }
    virtual void TearDown() { App_VoltageMonitor_Destroy(voltage_monitor); }

    struct VoltageMonitor *voltage_monitor;

    const float MIN_VOLTAGE = 5.0f;
    const float MAX_VOLTAGE = 6.0f;
};

TEST_F(VoltageMonitorTest, check_voltage_in_range)
{
    get_voltage_fake.return_val     = (MIN_VOLTAGE + MAX_VOLTAGE) / 2.0f;
    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    App_VoltageMonitor_Tick(voltage_monitor);

    ASSERT_EQ(App_VoltageMonitor_GetStatus(voltage_monitor), VOLTAGE_IN_RANGE);
}

TEST_F(VoltageMonitorTest, check_undervoltage)
{
    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    get_voltage_fake.return_val = MIN_VOLTAGE;
    App_VoltageMonitor_Tick(voltage_monitor);
    ASSERT_EQ(App_VoltageMonitor_GetStatus(voltage_monitor), VOLTAGE_IN_RANGE);
    ASSERT_EQ(error_callback_fake.call_count, 0);

    get_voltage_fake.return_val =
        std::nextafter(MIN_VOLTAGE, std::numeric_limits<float>::min());
    App_VoltageMonitor_Tick(voltage_monitor);
    ASSERT_EQ(App_VoltageMonitor_GetStatus(voltage_monitor), UNDERVOLTAGE);
    ASSERT_EQ(error_callback_fake.call_count, 1);
}

TEST_F(VoltageMonitorTest, check_overvoltage)
{
    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    get_voltage_fake.return_val = MAX_VOLTAGE;
    App_VoltageMonitor_Tick(voltage_monitor);
    ASSERT_EQ(App_VoltageMonitor_GetStatus(voltage_monitor), VOLTAGE_IN_RANGE);
    ASSERT_EQ(error_callback_fake.call_count, 0);

    get_voltage_fake.return_val =
        std::nextafter(MAX_VOLTAGE, std::numeric_limits<float>::max());
    App_VoltageMonitor_Tick(voltage_monitor);
    ASSERT_EQ(App_VoltageMonitor_GetStatus(voltage_monitor), OVERVOLTAGE);
    ASSERT_EQ(error_callback_fake.call_count, 1);
}
