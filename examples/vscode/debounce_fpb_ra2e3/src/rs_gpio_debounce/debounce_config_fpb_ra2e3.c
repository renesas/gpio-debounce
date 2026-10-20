/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/* Pre-set configuration source file - do not edit */
#include "bsp_api.h"

#if DEBOUNCE_PRESET_CONFIG_USE // Use pre-set configuration for Debounce
#if defined(BOARD_RA2E3_FPB)

#include "debounce_config_fpb_ra2e3.h"
#include "common_data.h"

ioport_instance_ctrl_t g_ioport_ctrl_preset;
const ioport_instance_t g_ioport_preset =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl_preset, .p_cfg = &g_bsp_pin_cfg, };

agt_instance_ctrl_t g_timer0_ctrl_preset;
const agt_extended_cfg_t g_timer0_extend_preset =
{ .count_source = AGT_CLOCK_PCLKB,
  .agto = AGT_PIN_CFG_DISABLED,
  .agtoab_settings_b.agtoa = AGT_PIN_CFG_DISABLED,
  .agtoab_settings_b.agtob = AGT_PIN_CFG_DISABLED,
  .measurement_mode = AGT_MEASURE_DISABLED,
  .agtio_filter = AGT_AGTIO_FILTER_NONE,
  .enable_pin = AGT_ENABLE_PIN_NOT_USED,
  .trigger_edge = AGT_TRIGGER_EDGE_RISING,
  .counter_bit_width = AGT_COUNTER_BIT_WIDTH_16, };
const timer_cfg_t g_timer0_cfg_preset =
{ .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.005 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0xea60,
  .duty_cycle_counts = 0x7530, .source_div = (timer_source_div_t) 1, .channel = 0, .p_callback = timer_isr,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = &g_timer0_extend_preset,
  .cycle_end_ipl = (3),
#if defined(VECTOR_NUMBER_AGT0_INT)
    .cycle_end_irq       = VECTOR_NUMBER_AGT0_INT,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0_preset =
{ .p_ctrl = &g_timer0_ctrl_preset, .p_cfg = &g_timer0_cfg_preset, .p_api = &g_timer_on_agt };

gpio_debounce_cfg_t g_gpio_debounce_cfg_ref = {
    .active_level = BSP_IO_LEVEL_LOW,
    .count_to_active = 5,
    .count_to_inactive = 5,
    .event_enable_mask = GPIO_DEBOUNCE_EVENT_PRESSED | GPIO_DEBOUNCE_EVENT_RELEASED,
    .p_ioport = &g_ioport,
    .portpin = BSP_IO_PORT_02_PIN_00,
    .p_callback = &button_cb,
    .p_context = NULL
};

gpio_debounce_ctrl_t g_gpio_debounce_ctrl_ref = {0};

#endif
#endif
