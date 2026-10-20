#include "unity_fixture.h"

TEST_GROUP_RUNNER(BUTTON_CFG_GEN)
{
    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_get_size)
    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_get_size_error)

    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_gen)
    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_gen_error)

    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_check)
    RUN_TEST_CASE(BUTTON_CFG_GEN, cfg_check_error)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(BUTTON_CFG_GEN);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
