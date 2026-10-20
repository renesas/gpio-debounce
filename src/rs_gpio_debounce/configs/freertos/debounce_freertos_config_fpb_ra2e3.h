/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "bsp_api.h"

#if DEBOUNCE_PRESET_CONFIG_USE         // Use pre-set configuration for Debounce
 #if defined(BOARD_RA2E3_FPB)
  #ifndef _CONFIG_FPB_RA2E3_H
   #define _CONFIG_FPB_RA2E3_H
   #include <stdint.h>
   #include "r_ioport.h"

   #include "bsp_pin_cfg.h"
   #include "rs_gpio_debounce.h"

extern gpio_debounce_cfg_t  g_gpio_debounce_cfg_ref;
extern gpio_debounce_ctrl_t g_gpio_debounce_ctrl_ref;
extern void button_cb(const gpio_debounce_callback_args_t * p_args);

  #endif
 #endif
#endif
