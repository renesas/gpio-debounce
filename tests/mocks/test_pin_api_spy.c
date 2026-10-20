#include "bsp_api.h"
#include "unity_fixture.h"

#include "pin_api_spy.h"
#include "test_shared.h"
#include "pin_data.h"

TEST_GROUP(PIN_API_SPY);

TEST_SETUP(PIN_API_SPY)
{
}

TEST_TEAR_DOWN(PIN_API_SPY)
{
    g_ioport.p_api->close(&g_ioport_ctrl);
}

TEST(PIN_API_SPY, test_err_not_open)
{
    fsp_err_t err = g_ioport.p_api->close(&g_ioport_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);

    bsp_io_level_t pin_val;
    err = g_ioport.p_api->pinRead(&g_ioport_ctrl, PORTPIN_1, &pin_val);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
}

TEST(PIN_API_SPY, test_err_already_open)
{
    fsp_err_t err = g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    err = g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ALREADY_OPEN, err);
}

TEST(PIN_API_SPY, test_read)
{
    fsp_err_t err = g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    int temp_arr[TEST_ARRLEN]  = {};
    int temp_arr2[TEST_ARRLEN] = {};

    for (int i = 0; i < TEST_ARRLEN; i++)
    {
        bsp_io_level_t pin_val;

        err = g_ioport.p_api->pinRead(&g_ioport_ctrl, PORTPIN_1, &pin_val);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
        temp_arr[i] = (int) pin_val;

        err = g_ioport.p_api->pinRead(&g_ioport_ctrl, PORTPIN_2, &pin_val);
        TEST_ASSERT_EQUAL(FSP_SUCCESS, err);
        temp_arr2[i] = (int) pin_val;

        pin_spy_advance_tick();
    }

    TEST_ASSERT_EQUAL_INT32_ARRAY(arr1, temp_arr, TEST_ARRLEN);
    TEST_ASSERT_EQUAL_INT32_ARRAY(arr2, temp_arr2, TEST_ARRLEN);
}

TEST(PIN_API_SPY, test_inject_error)
{
    fsp_err_t err = g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    pin_spy_inject_error(FSP_ERR_NOT_OPEN);
    err = g_ioport.p_api->open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);

    pin_spy_inject_error(FSP_ERR_NOT_OPEN);
    bsp_io_level_t pin_val;
    err = g_ioport.p_api->pinRead(&g_ioport_ctrl, PORTPIN_1, &pin_val);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);

    err = g_ioport.p_api->pinRead(&g_ioport_ctrl, PORTPIN_1, &pin_val);
    TEST_ASSERT_EQUAL(FSP_SUCCESS, err);

    pin_spy_inject_error(FSP_ERR_ASSERTION);
    err = g_ioport.p_api->close(&g_ioport_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_ASSERTION, err);
}
