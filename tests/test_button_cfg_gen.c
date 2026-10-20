#include "bsp_api.h"
#include "rs_gpio_debounce_cfg_fake.h"
#include "unity_fixture.h"
#include "rs_gpio_debounce.h"
#include "rs_gpio_debounce_cfg_gen.h"

TEST_GROUP(BUTTON_CFG_GEN);

TEST_SETUP(BUTTON_CFG_GEN)
{
}

TEST_TEAR_DOWN(BUTTON_CFG_GEN)
{
}

/** Individual Function Tests **/

// The get config size fn should get you the size of the config struct.
TEST(BUTTON_CFG_GEN, cfg_get_size)
{
    fsp_err_t err;
    uint32_t  size;
    err = rs_gpio_debounce_GetConfigSize(&size);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    TEST_ASSERT_EQUAL(sizeof(gpio_debounce_cfg_t), size);
}

TEST(BUTTON_CFG_GEN, cfg_gen)
{
    gpio_debounce_cfg_t cfg = {0};
    fsp_err_t           err;
    err = rs_gpio_debounce_GenConfig(&cfg, sizeof(gpio_debounce_cfg_t));
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    TEST_ASSERT_EQUAL(g_gpio_debounce_cfg_ref.active_level, cfg.active_level);
    TEST_ASSERT_EQUAL(g_gpio_debounce_cfg_ref.count_to_active, cfg.count_to_active);
    TEST_ASSERT_EQUAL(g_gpio_debounce_cfg_ref.count_to_inactive, cfg.count_to_inactive);
    TEST_ASSERT_EQUAL(g_gpio_debounce_cfg_ref.event_enable_mask, cfg.event_enable_mask);
    TEST_ASSERT_EQUAL(g_gpio_debounce_cfg_ref.portpin, cfg.portpin);
    TEST_ASSERT_EQUAL_PTR(g_gpio_debounce_cfg_ref.p_callback, cfg.p_callback);
    TEST_ASSERT_EQUAL_PTR(g_gpio_debounce_cfg_ref.p_ioport, cfg.p_ioport);
    TEST_ASSERT_EQUAL_PTR(g_gpio_debounce_cfg_ref.p_context, cfg.p_context);
}

TEST(BUTTON_CFG_GEN, cfg_check)
{
    gpio_debounce_cfg_t cfg = {0};

    fsp_err_t err;
    err = rs_gpio_debounce_CheckConfig(&cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_DATA, err);
    err = rs_gpio_debounce_GenConfig(&cfg, sizeof(gpio_debounce_cfg_t));
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
    err = rs_gpio_debounce_CheckConfig(&cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
}

/** Error Checking **/

TEST(BUTTON_CFG_GEN, cfg_get_size_error)
{
    fsp_err_t err;
    err = rs_gpio_debounce_GetConfigSize(NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}

TEST(BUTTON_CFG_GEN, cfg_gen_error)
{
    gpio_debounce_cfg_t cfg = {0};

    fsp_err_t err;
    err = rs_gpio_debounce_GenConfig(NULL, sizeof(gpio_debounce_cfg_t));
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_POINTER, err);

    err = rs_gpio_debounce_GenConfig(&cfg, (size_t) 2);
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_ARGUMENT, err);
}

TEST(BUTTON_CFG_GEN, cfg_check_error)
{
    fsp_err_t err = rs_gpio_debounce_CheckConfig(NULL);
    TEST_ASSERT_EQUAL(FSP_ERR_INVALID_POINTER, err);
}
