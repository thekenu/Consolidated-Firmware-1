#include "fff.h"
#include "gtest/gtest.h"

extern "C"
{
#include "App_VoltageCheck.h"

    DEFINE_FFF_GLOBALS;
    FAKE_VALUE_FUNC(float, get_voltage);
    FAKE_VALUE_FUNC(float, get_min_voltage);
    FAKE_VALUE_FUNC(float, get_max_voltage);
}

class VoltageCheckTest : public testing::Test
{
  protected:
    virtual void SetUp()
    {
        RESET_FAKE(get_voltage);
        RESET_FAKE(get_min_voltage);
        RESET_FAKE(get_max_voltage);

        FFF_RESET_HISTORY();

        voltage_check = App_VoltageCheck_Create(
            get_voltage, get_min_voltage, get_max_voltage);
    }
    virtual void TearDown() { App_VoltageCheck_Destroy(voltage_check); }

    struct VoltageCheck *voltage_check;

    const float MIN_VOLTAGE = 5.0f;
    const float MAX_VOLTAGE = 6.0f;
};

TEST_F(VoltageCheckTest, check_voltage_normal)
{
    get_voltage_fake.return_val = (MIN_VOLTAGE + MAX_VOLTAGE) / 2.0f;

    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    App_VoltageCheck_Tick(voltage_check);

    ASSERT_EQ(App_VoltageCheck_GetStatus(voltage_check), VOLTAGECHECK_NORMAL);
}

TEST_F(VoltageCheckTest, check_voltage_underflow)
{
    get_voltage_fake.return_val = MIN_VOLTAGE - 0.1f;

    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    App_VoltageCheck_Tick(voltage_check);

    ASSERT_EQ(
        App_VoltageCheck_GetStatus(voltage_check), VOLTAGECHECK_UNDERVOLTAGE);
}

TEST_F(VoltageCheckTest, check_voltage_overflow)
{
    get_voltage_fake.return_val = MAX_VOLTAGE + 0.1f;

    get_min_voltage_fake.return_val = MIN_VOLTAGE;
    get_max_voltage_fake.return_val = MAX_VOLTAGE;

    App_VoltageCheck_Tick(voltage_check);

    ASSERT_EQ(
        App_VoltageCheck_GetStatus(voltage_check), VOLTAGECHECK_OVERVOLTAGE);
}
