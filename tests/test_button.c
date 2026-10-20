#include "rs_gpio_debounce.h"
#include "unity_fixture.h"
#include "test_shared.h"

#include "button_data.h"
#include "pin_data.h"

#include "pin_api_spy.h"

const gpio_debounce_instance_t * p_button0 = &g_button_instance[0];
const gpio_debounce_instance_t * p_button1 = &g_button_instance[1];
const gpio_debounce_instance_t * p_button2 = &g_button_instance[2];
const gpio_debounce_instance_t * p_button3 = &g_button_instance[3];
const gpio_debounce_instance_t * p_button4 = &g_button_instance[4];

static void close_all_buttons (void)
{
    const size_t arr_size = sizeof(g_button_instance) / sizeof(gpio_debounce_instance_t);
    for (size_t i = 0; i < arr_size; i++)
    {
        const gpio_debounce_instance_t * p_inst = &g_button_instance[i];
        rs_gpio_debounce_Close(p_inst->p_ctrl);
    }
}

TEST_GROUP(BUTTON);

TEST_SETUP(BUTTON)
{
    g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
}

TEST_TEAR_DOWN(BUTTON)
{
    close_all_buttons();
    g_ioport.p_api->close(&g_ioport_ctrl);
}

/**---------------------------**/
/** Individual Function Tests **/
/**---------------------------**/

// Successfully opening and closing a button should return FSP_SUCCESS.
TEST(BUTTON, test_open_close)
{
    fsp_err_t err;
    err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    err = rs_gpio_debounce_Close(p_button0->p_ctrl);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
}

// When opening the button, the ctrl structure should be inigith proper values
TEST(BUTTON, test_correctly_initialized_ctrl)
{
    gpio_debounce_ctrl_t * p_inst_ctrl = p_button0->p_ctrl;

    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_Open(p_inst_ctrl, p_button0->p_cfg));

    TEST_ASSERT_EQUAL_INT(true, p_inst_ctrl->open);

    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->counter);
    TEST_ASSERT_EQUAL_INT(GPIO_DEBOUNCE_LEVEL_LOW, p_inst_ctrl->level);
    TEST_ASSERT_EQUAL_PTR(p_button0->p_cfg->p_callback, p_inst_ctrl->cfg.p_callback);

    // from cfg
    TEST_ASSERT_EQUAL_INT(p_button0->p_cfg->portpin, p_inst_ctrl->cfg.portpin);
    TEST_ASSERT_EQUAL_INT(p_button0->p_cfg->active_level, p_inst_ctrl->cfg.active_level);
    TEST_ASSERT_EQUAL_INT(p_button0->p_cfg->event_enable_mask, p_inst_ctrl->cfg.event_enable_mask);
    TEST_ASSERT_EQUAL_INT(p_button0->p_cfg->count_to_active, p_inst_ctrl->cfg.count_to_active);
    TEST_ASSERT_EQUAL_INT(p_button0->p_cfg->count_to_inactive, p_inst_ctrl->cfg.count_to_inactive);
    TEST_ASSERT_EQUAL_PTR(p_button0->p_cfg->p_ioport, p_inst_ctrl->cfg.p_ioport);

    // callback memory
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->callback_memory.portpin);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->callback_memory.event);
    TEST_ASSERT_EQUAL_PTR(p_button0->p_cfg->p_context, p_inst_ctrl->cfg.p_context);
}

//// When closing the button, the ctrl structure should be reset to default values.
TEST(BUTTON, test_close_correctly_clears_ctrl)
{
    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg));

    gpio_debounce_ctrl_t * p_inst_ctrl = p_button0->p_ctrl;

    // placing junk values in p_ctrl and callback_memory
    p_inst_ctrl->counter        = 2;
    p_inst_ctrl->cfg.p_callback = (void *) 2;

    p_inst_ctrl->callback_memory.portpin   = 2;
    p_inst_ctrl->callback_memory.event     = 2;
    p_inst_ctrl->callback_memory.p_context = (void *) 2;

    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_Close(p_inst_ctrl));

    TEST_ASSERT_EQUAL_INT(false, p_inst_ctrl->open);

    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->counter);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->level);
    TEST_ASSERT_EQUAL_PTR(NULL, p_inst_ctrl->cfg.p_callback);

    // from cfg
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->cfg.portpin);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->cfg.active_level);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->cfg.event_enable_mask);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->cfg.count_to_active);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->cfg.count_to_inactive);
    TEST_ASSERT_EQUAL_PTR(NULL, p_inst_ctrl->cfg.p_ioport);
    TEST_ASSERT_EQUAL_PTR(NULL, p_inst_ctrl->cfg.p_context);

    // callback memory
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->callback_memory.portpin);
    TEST_ASSERT_EQUAL_INT(0, p_inst_ctrl->callback_memory.event);
    TEST_ASSERT_EQUAL_PTR(NULL, p_inst_ctrl->callback_memory.p_context);
}

// The user should be able to read the debounced level of a single button
TEST(BUTTON, test_button_read)
{
    fsp_err_t err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    gpio_debounce_level_t out;
    err = rs_gpio_debounce_GetLevel(p_button0->p_ctrl, &out);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT32(GPIO_DEBOUNCE_LEVEL_LOW, out);
}

/**--------------------------**/
/** Parameter Checking Tests **/
/**--------------------------**/
TEST_GROUP(BUTTON_PARAM_CHECK);

TEST_SETUP(BUTTON_PARAM_CHECK)
{
    g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
}

TEST_TEAR_DOWN(BUTTON_PARAM_CHECK)
{
    close_all_buttons();
    g_ioport.p_api->close(&g_ioport_ctrl);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_open)
{
    fsp_err_t err = rs_gpio_debounce_Open(NULL, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);

    err = rs_gpio_debounce_Open(p_button0->p_ctrl, NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);

    gpio_debounce_cfg_t fake_cfg =
    {
        .portpin = PORTPIN_1, .p_ioport = NULL,
    };

    err = rs_gpio_debounce_Open(p_button0->p_ctrl, &fake_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

// The count_to_active and count_to_inactive parameters are not allowed to be set to 0
TEST(BUTTON_PARAM_CHECK, test_param_button_open_counter_values)
{
    gpio_debounce_cfg_t fake_cfg =
    {
        .portpin           = PORTPIN_2,
        .count_to_active   = 0,
        .count_to_inactive = 3,
        .active_level      = BSP_IO_LEVEL_HIGH,
        .p_ioport          = &g_ioport,
        .p_callback        = 0,
        .event_enable_mask = 0
    };

    fsp_err_t err = rs_gpio_debounce_Open(p_button0->p_ctrl, &fake_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_ARGUMENT, err);

    fake_cfg.count_to_active   = 3;
    fake_cfg.count_to_inactive = 0;

    err = rs_gpio_debounce_Open(p_button0->p_ctrl, &fake_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_ARGUMENT, err);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_close)
{
    fsp_err_t err = rs_gpio_debounce_Close(NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_getlevel)
{
    gpio_debounce_level_t level;
    fsp_err_t             err = rs_gpio_debounce_GetLevel(NULL, &level);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);

    err = rs_gpio_debounce_GetLevel(p_button0->p_ctrl, NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

static void stub_callback (gpio_debounce_callback_args_t const * const p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_setcallback)
{
    int       context;
    fsp_err_t err = rs_gpio_debounce_SetCallback(NULL, &stub_callback, (void *) &context);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_update)
{
    fsp_err_t err = rs_gpio_debounce_Update(NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

TEST(BUTTON_PARAM_CHECK, test_param_button_isopen)
{
    bool      result;
    fsp_err_t err = rs_gpio_debounce_IsOpen(NULL, &result);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);

    err = rs_gpio_debounce_IsOpen(p_button0->p_ctrl, NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

// When a button is closed no other methods should be able to be called for a button object
TEST(BUTTON_PARAM_CHECK, test_error_without_open)
{
    gpio_debounce_level_t out;

    fsp_err_t err1 = rs_gpio_debounce_Close(p_button0->p_ctrl);
    fsp_err_t err2 = rs_gpio_debounce_GetLevel(p_button0->p_ctrl, &out);
    fsp_err_t err3 = rs_gpio_debounce_Update(p_button0->p_ctrl);
    fsp_err_t err4 = rs_gpio_debounce_SetCallback(p_button0->p_ctrl, NULL, NULL);

    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err1);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err2);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err3);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err4);
}

TEST(BUTTON_PARAM_CHECK, test_error_already_open)
{
    fsp_err_t err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ALREADY_OPEN, err);
}

// When an ioport read fails, the button update method should return an error.
TEST(BUTTON_PARAM_CHECK, test_error_on_update_when_ioport_read_fails)
{
    fsp_err_t err;
    err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    g_ioport.p_api->close(&g_ioport_ctrl);

    err = rs_gpio_debounce_Update(p_button0->p_ctrl);

    TEST_ASSERT_EQUAL(FSP_ERR_ABORTED, err);
}

/**--------------------------**/
/** Full Functionality Tests **/
/**--------------------------**/

static void debounce_and_test_arr (const gpio_debounce_instance_t * p_button,
                                   const int                      * expected_arr,
                                   const size_t                     arr_len,
                                   bool                             open_close)
{
    fsp_err_t err;

    if (open_close)
    {
        err = rs_gpio_debounce_Open(p_button->p_ctrl, p_button->p_cfg);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    }

    int temp_arr[TEST_ARRLEN] = {};

    for (size_t i = 0; i < arr_len; i++)
    {
        err = rs_gpio_debounce_Update(p_button->p_ctrl);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

        gpio_debounce_level_t out;
        err = rs_gpio_debounce_GetLevel(p_button->p_ctrl, &out);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

        if ((out != GPIO_DEBOUNCE_LEVEL_HIGH) && (out != GPIO_DEBOUNCE_LEVEL_LOW))
        {
            TEST_FAIL_MESSAGE("GPIO debounce level must be must be valid.");
        }

        temp_arr[i] = out;

        pin_spy_advance_tick();
    }

    if (open_close)
    {
        err = rs_gpio_debounce_Close(p_button->p_ctrl);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    }

    TEST_ASSERT_EQUAL_INT32_ARRAY(expected_arr, temp_arr, TEST_ARRLEN);
}

// The debounced level of a button should be set to a value that appears consecutively for a given number of cycles
TEST(BUTTON, test_debounce)
{
    debounce_and_test_arr(p_button0, arr1_expected, TEST_ARRLEN, true);
    debounce_and_test_arr(p_button1, arr2_expected, TEST_ARRLEN, true);
}

// The number of cycles before a debouncing decision is made should be configurable
TEST(BUTTON, test_debounce_different_count_settings)
{
    const int different_count_settings_expected[TEST_ARRLEN] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0};
    debounce_and_test_arr(p_button2, different_count_settings_expected, TEST_ARRLEN, true);
}

// The user should be able to configure whether the active level is high or low.
TEST(BUTTON, test_debounce_active_level)
{
    static const int inverted_active_level_expected[TEST_ARRLEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
    debounce_and_test_arr(p_button3, inverted_active_level_expected, TEST_ARRLEN, true);
}

// The isOpen function should return a boolean value for whether the button is open or not.
TEST(BUTTON, test_is_open)
{
    bool result = false;

    fsp_err_t err = rs_gpio_debounce_IsOpen(p_button0->p_ctrl, &result);

    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL(false, result);

    err = rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    err = rs_gpio_debounce_IsOpen(p_button0->p_ctrl, &result);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL(1, result);

    err = rs_gpio_debounce_Close(p_button0->p_ctrl);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
}

long int context_placeholder   = -1;
bool     callback_params_valid = false;
static void callback_check_params (const gpio_debounce_callback_args_t * const args)
{
    if ((args->portpin == PORTPIN_1) && (args->p_context == (void *) context_placeholder))
    {
        callback_params_valid = true;
    }
}

// The button_callback_args_t supplied to the callback should have the proper values populated.
// The test_callbacks_full and test_event_mask tests test the args->event parameter.
TEST(BUTTON, test_callback_arg_params)
{
    // Loading from cfg
    g_button_cfg[0].p_callback = callback_check_params;

    rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);

    for (int i = 0; i < BUTTON_ARRLEN; i++)
    {
        rs_gpio_debounce_Update(p_button0->p_ctrl);
        pin_spy_advance_tick();
    }

    g_button_cfg[0].p_callback = NULL;
    TEST_ASSERT_EQUAL(true, callback_params_valid);

    rs_gpio_debounce_Close(p_button0->p_ctrl);

    // Using SetCallback
    context_placeholder = 1000;
    rs_gpio_debounce_Open(p_button0->p_ctrl, p_button0->p_cfg);

    rs_gpio_debounce_SetCallback(p_button0->p_ctrl, callback_check_params, &context_placeholder);

    for (int i = 0; i < BUTTON_ARRLEN; i++)
    {
        rs_gpio_debounce_Update(p_button0->p_ctrl);
        pin_spy_advance_tick();
    }
}

struct full_test_cb_state_t
{
    int * active_arr_actual;
    int * inactive_arr_actual;
};

static void callback (gpio_debounce_callback_args_t const * const p_args) {
    int tick = pin_spy_get_tick();
    struct full_test_cb_state_t * ctx = (struct full_test_cb_state_t *) p_args->p_context;
    ctx->active_arr_actual[tick]   = 0;
    ctx->inactive_arr_actual[tick] = 0;
    if (p_args->event == GPIO_DEBOUNCE_EVENT_PRESSED)
    {
        ctx->active_arr_actual[tick] = 1;
    }

    if (p_args->event == GPIO_DEBOUNCE_EVENT_RELEASED)
    {
        ctx->inactive_arr_actual[tick] = 1;
    }
}

static void debounce_and_test_with_callback (const gpio_debounce_instance_t * p_button,
                                             const int                      * arr_expected,
                                             const int                      * active_expected,
                                             const int                      * inactive_expected)
{
    int active_arr_actual[TEST_ARRLEN]   = {0};
    int inactive_arr_actual[TEST_ARRLEN] = {0};

    struct full_test_cb_state_t cb_state =
    {
        .active_arr_actual   = active_arr_actual,
        .inactive_arr_actual = inactive_arr_actual,
    };

    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_Open(p_button->p_ctrl, p_button->p_cfg));
    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_SetCallback(p_button->p_ctrl, &callback, (void *) &cb_state));

    debounce_and_test_arr(p_button, arr_expected, TEST_ARRLEN, false);

    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_SetCallback(p_button->p_ctrl, NULL, NULL));
    TEST_ASSERT_EQUAL(FSP_SUCCESS, rs_gpio_debounce_Close(p_button->p_ctrl));

    TEST_ASSERT_EQUAL_INT32_ARRAY(active_expected, active_arr_actual, TEST_ARRLEN);
    TEST_ASSERT_EQUAL_INT32_ARRAY(inactive_expected, inactive_arr_actual, TEST_ARRLEN);

    // TEST_ASSERT_EQUAL_INT32_ARRAY(debouncing_expected, debouncing_arr_actual, TEST_ARRLEN);
}

// The user should be able to set a callback that is invoked when the button level variable changes
TEST(BUTTON, test_callbacks_full)
{
    const int active_expected[TEST_ARRLEN]   = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    const int inactive_expected[TEST_ARRLEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};

    debounce_and_test_with_callback(p_button1, arr2_expected, active_expected, inactive_expected);
}

// The user should be able to set a mask that controls which events the callback should be fired for.
TEST(BUTTON, test_event_mask)
{
    const int active_expected[TEST_ARRLEN]   = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    const int inactive_expected[TEST_ARRLEN] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    debounce_and_test_with_callback(p_button4, arr2_expected, active_expected, inactive_expected);
}
