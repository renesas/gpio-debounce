#include "lpm_spy.h"
#include "bsp_api.h"
#include "r_lpm_api.h"

fsp_err_t R_LPM_Open (lpm_ctrl_t * const p_api_ctrl, const lpm_cfg_t * const p_cfg)
{
    FSP_PARAMETER_NOT_USED(p_cfg);

    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->lpm_open == false, FSP_ERR_ALREADY_OPEN);

    p_ctrl->lpm_open    = true;
    p_ctrl->callback_fn = NULL;

    return FSP_SUCCESS;
}

fsp_err_t R_LPM_Close (lpm_ctrl_t * const p_api_ctrl)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->lpm_open == true, FSP_ERR_NOT_OPEN);

    p_ctrl->lpm_open    = false;
    p_ctrl->callback_fn = NULL;

    return FSP_SUCCESS;
}

fsp_err_t R_LPM_LowPowerModeEnter (lpm_ctrl_t * const p_api_ctrl)
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->lpm_open == true, FSP_ERR_NOT_OPEN);

    if (p_ctrl->callback_fn != NULL)
    {
        p_ctrl->callback_fn();
    }

    return FSP_SUCCESS;
}

void lpm_spy_set_callback (lpm_ctrl_t * const p_api_ctrl, void (*callback_fn) (void))
{
    lpm_instance_ctrl_t * p_ctrl = (lpm_instance_ctrl_t *) p_api_ctrl;

    p_ctrl->callback_fn = callback_fn;
}

const lpm_api_t g_lpm_on_lpm =
{
    .open              = R_LPM_Open,
    .close             = R_LPM_Close,
    .lowPowerModeEnter = R_LPM_LowPowerModeEnter,
};
