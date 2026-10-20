/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "bsp_api.h"

#if DEBOUNCE_PRESET_CONFIG_USE // Use pre-set configuration for Debounce
#if defined(BOARD_RA2E3_FPB)
#ifndef _CONFIG_FPB_RA2E3_H
#define _CONFIG_FPB_RA2E3_H
#include <stdint.h>
#include "r_ioport.h"
#include "r_timer_api.h"
#include "r_agt.h"
#include "bsp_pin_cfg.h"
#include "rs_gpio_debounce.h"

extern const timer_instance_t g_timer0_preset;

/** Access the AGT instance using these structures when calling API functions directly (::p_api is not used). */
extern agt_instance_ctrl_t g_timer0_ctrl_preset;
extern const timer_cfg_t g_timer0_cfg_preset;

void debounce_config_gen(gpio_debounce_cfg_t *p_button_cfg, const ioport_instance_t *p_ioport, void (*p_callback)(gpio_debounce_callback_args_t const * const p_args));
#ifndef timer_isr
void timer_isr(timer_callback_args_t *p_args);
#endif

extern gpio_debounce_cfg_t g_gpio_debounce_cfg_ref;
extern gpio_debounce_ctrl_t g_gpio_debounce_ctrl_ref;

extern void button_cb(const gpio_debounce_callback_args_t *args);

#endif
#endif
#endif
