#include "unity_fixture.h"

TEST_GROUP_RUNNER(BUTTON)
{
    RUN_TEST_CASE(BUTTON, test_open_close)
    RUN_TEST_CASE(BUTTON, test_correctly_initialized_ctrl)
    RUN_TEST_CASE(BUTTON, test_close_correctly_clears_ctrl)
    RUN_TEST_CASE(BUTTON, test_button_read)
    RUN_TEST_CASE(BUTTON, test_debounce)

    // RUN_TEST_CASE(BUTTON, test_debounce_flag)
    RUN_TEST_CASE(BUTTON, test_debounce_different_count_settings)
    RUN_TEST_CASE(BUTTON, test_debounce_active_level)
    RUN_TEST_CASE(BUTTON, test_is_open)
    RUN_TEST_CASE(BUTTON, test_callbacks_full)
    RUN_TEST_CASE(BUTTON, test_event_mask)
    RUN_TEST_CASE(BUTTON, test_callback_arg_params)
}

TEST_GROUP_RUNNER(BUTTON_PARAM_CHECK)
{
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_error_on_update_when_ioport_read_fails)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_open)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_open_counter_values)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_close)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_getlevel)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_setcallback)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_update)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_param_button_isopen)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_error_without_open)
    RUN_TEST_CASE(BUTTON_PARAM_CHECK, test_error_already_open)
}

static void runAllTests (void)
{
    RUN_TEST_GROUP(BUTTON);
    RUN_TEST_GROUP(BUTTON_PARAM_CHECK);
}

int main (int argc, const char * argv[])
{
    return UnityMain(argc, argv, runAllTests);
}
