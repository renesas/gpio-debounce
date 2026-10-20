#include "unity_fixture.h"

TEST_GROUP_RUNNER(PIN_API_SPY)
{
    RUN_TEST_CASE(PIN_API_SPY, test_err_not_open)
    RUN_TEST_CASE(PIN_API_SPY, test_err_already_open)
    RUN_TEST_CASE(PIN_API_SPY, test_read)
    RUN_TEST_CASE(PIN_API_SPY, test_inject_error)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(PIN_API_SPY);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
