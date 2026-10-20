#include "unity_fixture.h"
#include "external_irq_data.h"

#define TEST_ASSERT_SUCCESS(err)    TEST_ASSERT_EQUAL(FSP_SUCCESS, (err))
TEST_GROUP(EXTERNAL_IRQ_SPY);

TEST_SETUP(EXTERNAL_IRQ_SPY)
{
}

TEST_TEAR_DOWN(EXTERNAL_IRQ_SPY)
{
    g_external_irq_on_irq_spy.close(&g_external_irq0_ctrl);
}

/**---------------------------**/
/** Individual Function Tests **/
/**---------------------------**/

TEST(EXTERNAL_IRQ_SPY, test_open_close)
{
    fsp_err_t err = g_external_irq_on_irq_spy.open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    TEST_ASSERT_SUCCESS(err);
    err = g_external_irq_on_irq_spy.close(&g_external_irq0_ctrl);
    TEST_ASSERT_SUCCESS(err);
}

TEST(EXTERNAL_IRQ_SPY, test_already_open)
{
    fsp_err_t err = g_external_irq_on_irq_spy.open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    TEST_ASSERT_SUCCESS(err);
    err = g_external_irq_on_irq_spy.open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    TEST_ASSERT_EQUAL(FSP_ERR_ALREADY_OPEN, err);
}

TEST(EXTERNAL_IRQ_SPY, test_no_open)
{
    fsp_err_t err = g_external_irq_on_irq_spy.close(g_external_irq0.p_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
    err = g_external_irq_on_irq_spy.enable(g_external_irq0.p_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
    err = g_external_irq_on_irq_spy.disable(g_external_irq0.p_ctrl);
    TEST_ASSERT_EQUAL(FSP_ERR_NOT_OPEN, err);
}

TEST(EXTERNAL_IRQ_SPY, test_enable_disable)
{
    fsp_err_t err = g_external_irq_on_irq_spy.open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);
    TEST_ASSERT_SUCCESS(err);

    g_external_irq_on_irq_spy.enable(g_external_irq0.p_ctrl);
    bool status = external_irq_spy_is_enabled(g_external_irq0.p_ctrl);
    TEST_ASSERT_EQUAL_INT(true, status);
    g_external_irq_on_irq_spy.disable(g_external_irq0.p_ctrl);
    status = external_irq_spy_is_enabled(g_external_irq0.p_ctrl);
    TEST_ASSERT_EQUAL_INT(false, status);

    err = g_external_irq_on_irq_spy.close(&g_external_irq0_ctrl);
    TEST_ASSERT_SUCCESS(err);
}
