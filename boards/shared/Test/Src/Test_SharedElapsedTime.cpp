#include "Test_Shared.h"

extern "C"
{
#include "App_SharedElapsedTime.h"
}

FAKE_VALUE_FUNC(uint32_t, elapsed_time_get_current_ms);

class SharedElapsedTimeTest : public testing::Test
{
  protected:
    void SetUp() override
    {
        // Reset the fake get-time function before _Create is called so the
        // elapsed time starts at t = 0ms
        RESET_FAKE(elapsed_time_get_current_ms);

        elapsed_time =
            App_SharedElapsedTime_Create(elapsed_time_get_current_ms);
    }

    void TearDown() override
    {
        TearDownObject(elapsed_time, App_SharedElapsedTime_Destroy);
    }

    struct ElapsedTime *elapsed_time;
};

TEST_F(SharedElapsedTimeTest, no_time_elapsed)
{
    ASSERT_EQ(0, App_SharedElapsedTime_Get(elapsed_time));
}

TEST_F(SharedElapsedTimeTest, no_time_elapsed_since_reset)
{
    App_SharedElapsedTime_Reset(elapsed_time);
    ASSERT_EQ(0, App_SharedElapsedTime_Get(elapsed_time));
}

TEST_F(SharedElapsedTimeTest, short_time_elapsed)
{
    const std::array small_ms = { 1, 2, 3, 4, 5 };

    for (auto &ms : small_ms)
    {
        elapsed_time_get_current_ms_fake.return_val = ms;
        ASSERT_EQ(ms, App_SharedElapsedTime_Get(elapsed_time));
    }
}

TEST_F(SharedElapsedTimeTest, long_time_elapsed)
{
    const std::array large_ms = { 1000000, 2000000, 3000000, 4000000, 5000000 };

    for (auto &ms : large_ms)
    {
        elapsed_time_get_current_ms_fake.return_val = ms;
        ASSERT_EQ(ms, App_SharedElapsedTime_Get(elapsed_time));
    }
}

TEST_F(SharedElapsedTimeTest, multiple_resets)
{
    // Suppose a non-zero amount of time has elapsed
    elapsed_time_get_current_ms_fake.return_val = 1;

    // After a reset, the elapsed time should be zero
    App_SharedElapsedTime_Reset(elapsed_time);
    ASSERT_EQ(0, App_SharedElapsedTime_Get(elapsed_time));

    // Suppose some more time has elapsed, make sure only the delta time is
    // accounted for
    elapsed_time_get_current_ms_fake.return_val += 10;
    ASSERT_EQ(10, App_SharedElapsedTime_Get(elapsed_time));

    // After another reset, the elapsed time should once again be zero
    App_SharedElapsedTime_Reset(elapsed_time);
    ASSERT_EQ(0, App_SharedElapsedTime_Get(elapsed_time));
}


TEST_F(SharedElapsedTimeTest, current_ms_overflow)
{

}
