/***********************************************************************************************************************
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#include "rs_gpio_debounce_cfg_gen.h"
#include "bsp_api.h"
#include "rs_gpio_debounce.h"
#include <string.h>

extern const gpio_debounce_cfg_t g_gpio_debounce_cfg_ref;

fsp_err_t rs_gpio_debounce_GetConfigSize (uint32_t * p_size) {
    FSP_ASSERT(p_size != NULL);
    *p_size = sizeof(gpio_debounce_cfg_t);

    return FSP_SUCCESS;
}

fsp_err_t rs_gpio_debounce_GenConfig (gpio_debounce_cfg_t * const p_cfg, uint32_t const config_size) {
    FSP_ERROR_RETURN(p_cfg != NULL, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(sizeof(gpio_debounce_cfg_t) == config_size, FSP_ERR_INVALID_ARGUMENT);

    memcpy(p_cfg, &g_gpio_debounce_cfg_ref, config_size);

    return FSP_SUCCESS;
}

fsp_err_t rs_gpio_debounce_CheckConfig (gpio_debounce_cfg_t const * const p_cfg)
{
    FSP_ERROR_RETURN(p_cfg != NULL, FSP_ERR_INVALID_POINTER);

    FSP_ERROR_RETURN(p_cfg->active_level == g_gpio_debounce_cfg_ref.active_level, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->count_to_active == g_gpio_debounce_cfg_ref.count_to_active, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->count_to_inactive == g_gpio_debounce_cfg_ref.count_to_inactive, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->event_enable_mask == g_gpio_debounce_cfg_ref.event_enable_mask, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->portpin == g_gpio_debounce_cfg_ref.portpin, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->p_callback == g_gpio_debounce_cfg_ref.p_callback, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->p_ioport == g_gpio_debounce_cfg_ref.p_ioport, FSP_ERR_INVALID_DATA);
    FSP_ERROR_RETURN(p_cfg->p_context == g_gpio_debounce_cfg_ref.p_context, FSP_ERR_INVALID_DATA);

    return FSP_SUCCESS;
}
