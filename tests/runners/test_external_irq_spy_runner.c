#include "unity_fixture.h"

TEST_GROUP_RUNNER(EXTERNAL_IRQ_SPY)
{
    RUN_TEST_CASE(EXTERNAL_IRQ_SPY, test_open_close)
    RUN_TEST_CASE(EXTERNAL_IRQ_SPY, test_already_open)
    RUN_TEST_CASE(EXTERNAL_IRQ_SPY, test_no_open)
    RUN_TEST_CASE(EXTERNAL_IRQ_SPY, test_enable_disable)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(EXTERNAL_IRQ_SPY);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
