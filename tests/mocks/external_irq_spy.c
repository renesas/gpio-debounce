#include "external_irq_spy.h"
#include "bsp_api.h"
#include "r_external_irq_api.h"

fsp_err_t Spy_ExternalIrqOpen (external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg)
{
    FSP_PARAMETER_NOT_USED(p_cfg);

    irq_spy_instance_ctrl_t * p_ctrl = (irq_spy_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == false, FSP_ERR_ALREADY_OPEN);

    p_ctrl->open = true;

    return FSP_SUCCESS;
}

fsp_err_t Spy_ExternalIrqClose (external_irq_ctrl_t * const p_api_ctrl)
{
    irq_spy_instance_ctrl_t * p_ctrl = (irq_spy_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == true, FSP_ERR_NOT_OPEN);

    p_ctrl->open = false;

    return FSP_SUCCESS;
}

fsp_err_t Spy_ExternalIrqEnable (external_irq_ctrl_t * const p_api_ctrl)
{
    irq_spy_instance_ctrl_t * p_ctrl = (irq_spy_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == true, FSP_ERR_NOT_OPEN);

    p_ctrl->enabled = true;

    return FSP_SUCCESS;
}

fsp_err_t Spy_ExternalIrqDisable (external_irq_ctrl_t * const p_api_ctrl)
{
    irq_spy_instance_ctrl_t * p_ctrl = (irq_spy_instance_ctrl_t *) p_api_ctrl;
    FSP_ERROR_RETURN(p_ctrl->open == true, FSP_ERR_NOT_OPEN);

    p_ctrl->enabled = false;

    return FSP_SUCCESS;
}

bool external_irq_spy_is_enabled (irq_spy_instance_ctrl_t * const p_ctrl)
{
    return p_ctrl->enabled;
}

const external_irq_api_t g_external_irq_on_irq_spy =
{
    .open    = &Spy_ExternalIrqOpen,
    .close   = &Spy_ExternalIrqClose,
    .enable  = &Spy_ExternalIrqEnable,
    .disable = &Spy_ExternalIrqDisable,
};
