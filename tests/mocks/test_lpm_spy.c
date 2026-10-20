#include "lpm_data.h"
#include "lpm_spy.h"
#include "unity_fixture.h"

#define TEST_ASSERT_SUCCESS(err)    TEST_ASSERT_EQUAL(FSP_SUCCESS, (err))

bool callback_fired = false;

TEST_GROUP(LPM_SPY);

TEST_SETUP(LPM_SPY)
{
}

TEST_TEAR_DOWN(LPM_SPY)
{
    g_lpm_on_lpm.close(&g_lpm0_ctrl);
    callback_fired = false;
}

/**---------------------------**/
/** Individual Function Tests **/
/**---------------------------**/

TEST(LPM_SPY, test_open_close)
{
    fsp_err_t err = g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg);
    TEST_ASSERT_SUCCESS(err);
    err = g_lpm_on_lpm.close(g_lpm0.p_ctrl);
    TEST_ASSERT_SUCCESS(err);
}

TEST(LPM_SPY, test_already_open)
{
    fsp_err_t err = g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg);
    TEST_ASSERT_SUCCESS(err);
    err = g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ALREADY_OPEN, err);
}

TEST(LPM_SPY, test_no_open)
{
    fsp_err_t err = g_lpm_on_lpm.close(g_lpm0.p_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
    err = g_lpm_on_lpm.lowPowerModeEnter(g_lpm0.p_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
}

static void fake_callback (void)
{
    callback_fired = true;
}

TEST(LPM_SPY, test_correctly_initialize_ctrl)
{
    g_lpm0_ctrl.callback_fn = fake_callback;
    TEST_ASSERT_SUCCESS(g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg));

    TEST_ASSERT_EQUAL(true, g_lpm0_ctrl.callback_fn == NULL);
}

TEST(LPM_SPY, test_correctly_clear_ctrl)
{
    TEST_ASSERT_SUCCESS(g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg));
    lpm_spy_set_callback(g_lpm0.p_ctrl, &fake_callback);
    TEST_ASSERT_SUCCESS(g_lpm_on_lpm.close(g_lpm0.p_ctrl));

    TEST_ASSERT_EQUAL(true, g_lpm0_ctrl.callback_fn == NULL);
}

TEST(LPM_SPY, test_callback)
{
    TEST_ASSERT_SUCCESS(g_lpm_on_lpm.open(g_lpm0.p_ctrl, g_lpm0.p_cfg));
    lpm_spy_set_callback(g_lpm0.p_ctrl, &fake_callback);

    fsp_err_t err = R_LPM_LowPowerModeEnter(g_lpm0.p_ctrl);
    TEST_ASSERT_SUCCESS(err);
    TEST_ASSERT_EQUAL(true, callback_fired);
}
