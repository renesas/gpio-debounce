/***********************************************************************************************************************
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#if DEBOUNCE_PRESET_CONFIG_USE
 #include <rs_gpio_debounce/rs_gpio_debounce_cfg_gen.h>
#endif
#include "hal_data.h"
#include "r_ioport.h"
#include "rs_gpio_debounce/rs_gpio_debounce.h"

#define APP_ERR_TRAP(err)    ({                                  \
        if (((err) != FSP_SUCCESS)) {                            \
            __asm("BKPT #0\n");}       /* Trap upon the error */ \
    })

gpio_debounce_ctrl_t g_gpio_debounce_ctrl = {0};
gpio_debounce_cfg_t  g_gpio_debounce_cfg  = {0};

void button_cb (const gpio_debounce_callback_args_t * p_args) {
    if (p_args->event == GPIO_DEBOUNCE_EVENT_PRESSED)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_HIGH);
    }
    else if (p_args->event == GPIO_DEBOUNCE_EVENT_RELEASED)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
    }
}

void timer_isr (timer_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    rs_gpio_debounce_Update(&g_gpio_debounce_ctrl);
}

void start_debounce (void) {
    const timer_instance_t * p_timer_instance;

#if DEBOUNCE_PRESET_CONFIG_USE
    extern const timer_instance_t g_timer0_preset;
    p_timer_instance = &g_timer0_preset;
    APP_ERR_TRAP(rs_gpio_debounce_GenConfig(&g_gpio_debounce_cfg, sizeof(gpio_debounce_cfg_t)));
    APP_ERR_TRAP(rs_gpio_debounce_CheckConfig(&g_gpio_debounce_cfg));
#else
    p_timer_instance = &g_timer0;
#endif

    APP_ERR_TRAP(rs_gpio_debounce_Open(&g_gpio_debounce_ctrl, &g_gpio_debounce_cfg));

    R_AGT_Open(p_timer_instance->p_ctrl, p_timer_instance->p_cfg);
    R_AGT_Start(p_timer_instance->p_ctrl);
}
