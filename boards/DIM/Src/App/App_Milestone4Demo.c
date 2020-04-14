#include "../../TL85/scripts/TL85.h"
#include "App_Milestone4Demo.h"
#include "App_CanTx.h"

TL85 void SetWheelSpeed(float wheel_speed)
{
    App_CanTx_SetPeriodicSignal_WHEEL_SPEED(can_tx, wheel_speed);

    if (wheel_speed > 15.0f)
        App_CanTx_SetPeriodicSignal_MOTOR_SHUTDOWN(can_tx, true);
    else
        App_CanTx_SetPeriodicSignal_MOTOR_SHUTDOWN(can_tx, false);
}

TL85 void SetBatteryVoltage(float battery_voltage)
{
    App_CanTx_SetPeriodicSignal_WHEEL_SPEED(can_tx, battery_voltage);

    if (battery_voltage > 35.0f)
        App_CanTx_SetPeriodicSignal_BATTERY_SHUTDOWN(can_tx, true);
    else
        App_CanTx_SetPeriodicSignal_BATTERY_SHUTDOWN(can_tx, false);
}

TL85 void SetTirePressure(float tire_pressure)
{
    App_CanTx_SetPeriodicSignal_WHEEL_SPEED(can_tx, tire_pressure);

    if (tire_pressure < 65.0f)
        App_CanTx_SetPeriodicSignal_LOW_TIRE_PRESSURE(can_tx, true);
    else
        App_CanTx_SetPeriodicSignal_LOW_TIRE_PRESSURE(can_tx, false);
}
