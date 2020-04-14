#include "../../TL85/scripts/TL85.h"
#include "App_Milestone4Demo.h"
#include "App_CanTx.h"

static float prv_wheel_speed;
static float prv_battery_voltage;
static float prv_tire_pressure;

TL85 void SetWheelSpeed(float wheel_speed)
{
    prv_wheel_speed = wheel_speed;

    if (prv_wheel_speed > 15.0f)
    {
        struct CanMsgs_fault_outputs_t payload;
        payload.motor_shutdown = true;
        (void)payload;
        //        App_CanTx_SendNonPeriodicMsg_DIM_STARTUP(can_tx, &payload);
    }
}

TL85 void SetBatteryVoltage(float battery_voltage)
{
    prv_battery_voltage = battery_voltage;
}

TL85 void SetTirePressure(float tire_pressure)
{
    prv_tire_pressure = tire_pressure;
}
