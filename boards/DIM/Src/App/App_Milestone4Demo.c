#include "../../TL85/scripts/TL85.h"
#include "App_Milestone4Demo.h"
#include "App_CanTx.h"

static float prv_battery_voltage;
static float prv_tire_pressure;

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
    prv_battery_voltage = battery_voltage;
}

TL85 void SetTirePressure(float tire_pressure)
{
    prv_tire_pressure = tire_pressure;
}
