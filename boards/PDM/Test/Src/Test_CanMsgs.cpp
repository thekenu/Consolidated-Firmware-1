#include "Test_Pdm.h"

extern "C"
{
#include "App_CanMsgs.h"
}

// PDM-21
TEST(CanMsgsTest, state_machine_message_frequency)
{
    ASSERT_GE(HZ_TO_MS(100), CANMSGS_PDM_STATE_MACHINE_CYCLE_TIME_MS);
}

// PDM-2
TEST(CanMsgsTest, heartbeat_message_frequency)
{
    ASSERT_GE(HZ_TO_MS(10), CANMSGS_PDM_HEARTBEAT_CYCLE_TIME_MS);
}

// PDM-11
TEST(CanMsgsTest, current_sensing_message_frequency)
{
    ASSERT_GE(HZ_TO_MS(1), CANMSGS_PDM_AUX1_AUX2_CURRENT_CYCLE_TIME_MS);
    ASSERT_GE(HZ_TO_MS(1), CANMSGS_PDM_ENERGY_METER_CURRENT_CYCLE_TIME_MS);
    ASSERT_GE(HZ_TO_MS(1), CANMSGS_PDM_AIRSHDN_CANGLV_CURRENT_CYCLE_TIME_MS);
    ASSERT_GE(HZ_TO_MS(1), CANMSGS_PDM_INVERTER_CURRENT_CYCLE_TIME_MS);
}
