/***********************************************************************************************************************
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#ifndef RS_GPIO_DEBOUNCE_CFG_GEN_H_
#define RS_GPIO_DEBOUNCE_CFG_GEN_H_

#include "bsp_api.h"
#include "rs_gpio_debounce.h"

fsp_err_t rs_gpio_debounce_GetConfigSize(uint32_t * p_size);
fsp_err_t rs_gpio_debounce_GenConfig(gpio_debounce_cfg_t * const p_cfg, uint32_t const config_size);
fsp_err_t rs_gpio_debounce_CheckConfig(gpio_debounce_cfg_t const * const p_cfg);

#endif
