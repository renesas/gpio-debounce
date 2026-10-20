#include "unity_fixture.h"

TEST_GROUP_RUNNER(LPM_SPY)
{
    RUN_TEST_CASE(LPM_SPY, test_open_close)
    RUN_TEST_CASE(LPM_SPY, test_already_open)
    RUN_TEST_CASE(LPM_SPY, test_no_open)
    RUN_TEST_CASE(LPM_SPY, test_correctly_initialize_ctrl)
    RUN_TEST_CASE(LPM_SPY, test_correctly_clear_ctrl)
    RUN_TEST_CASE(LPM_SPY, test_callback)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(LPM_SPY);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
