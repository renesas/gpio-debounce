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

#include "FreeRTOS.h"
#include "task.h"

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

void start_debounce (void) {
#if DEBOUNCE_PRESET_CONFIG_USE
    APP_ERR_TRAP(rs_gpio_debounce_GenConfig(&g_gpio_debounce_cfg, sizeof(gpio_debounce_cfg_t)));
    APP_ERR_TRAP(rs_gpio_debounce_CheckConfig(&g_gpio_debounce_cfg));
#endif
    APP_ERR_TRAP(rs_gpio_debounce_Open(&g_gpio_debounce_ctrl, &g_gpio_debounce_cfg));

    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_PERIOD_MS));
        rs_gpio_debounce_Update(&g_gpio_debounce_ctrl);
    }
}
