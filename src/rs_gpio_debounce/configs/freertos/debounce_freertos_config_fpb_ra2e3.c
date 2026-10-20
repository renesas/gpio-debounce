/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/* Pre-set configuration source file - do not edit */
#include "bsp_api.h"

#if DEBOUNCE_PRESET_CONFIG_USE         // Use pre-set configuration for Debounce
 #if defined(BOARD_RA2E3_FPB)

  #include <rs_gpio_debounce/debounce_freertos_config_fpb_ra2e3.h>
  #include "bsp_api.h"
  #include "common_data.h"

gpio_debounce_cfg_t g_gpio_debounce_cfg_ref =
{
    .active_level      = BSP_IO_LEVEL_LOW,
    .count_to_active   = 5,
    .count_to_inactive = 5,
    .event_enable_mask = GPIO_DEBOUNCE_EVENT_PRESSED | GPIO_DEBOUNCE_EVENT_RELEASED,
    .p_ioport          = &g_ioport,
    .portpin           = BSP_IO_PORT_02_PIN_00,
    .p_callback        = &button_cb,
    .p_context         = NULL
};

gpio_debounce_ctrl_t g_gpio_debounce_ctrl_ref = {0};

 #endif
#endif
