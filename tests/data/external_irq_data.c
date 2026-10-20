#include "external_irq_spy.h"
#include "r_external_irq_api.h"

irq_spy_instance_ctrl_t g_external_irq0_ctrl;
irq_spy_instance_cfg_t  g_external_irq0_cfg;

const external_irq_instance_t g_external_irq0 =
{
    .p_ctrl = &g_external_irq0_ctrl,
    .p_cfg  = (external_irq_cfg_t *) &g_external_irq0_cfg,
    .p_api  = &g_external_irq_on_irq_spy,
};
