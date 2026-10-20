#include "lpm_data.h"
#include "lpm_spy.h"

lpm_instance_ctrl_t g_lpm0_ctrl;
lpm_cfg_t           g_lpm0_cfg;

const lpm_instance_t g_lpm0 =
{
    .p_ctrl = &g_lpm0_ctrl,
    .p_cfg  = &g_lpm0_cfg,
    .p_api  = &g_lpm_on_lpm,
};
