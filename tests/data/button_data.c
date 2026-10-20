#include "button_data.h"
#include "pin_data.h"
#include "rs_gpio_debounce.h"

gpio_debounce_cfg_t g_button_cfg[] =
{
    {
        .portpin           = 0x100, .count_to_active = 3, .count_to_inactive = 3, .active_level = BSP_IO_LEVEL_HIGH,
        .p_ioport          = &g_ioport, .p_callback = 0,
        .event_enable_mask = (GPIO_DEBOUNCE_EVENT_RELEASED | GPIO_DEBOUNCE_EVENT_PRESSED), .p_context = (void *) -1
    },
    {
        .portpin           = 0x200, .count_to_active = 3, .count_to_inactive = 3, .active_level = BSP_IO_LEVEL_HIGH,
        .p_ioport          = &g_ioport, .p_callback = 0,
        .event_enable_mask = (GPIO_DEBOUNCE_EVENT_RELEASED | GPIO_DEBOUNCE_EVENT_PRESSED)
    },
    {
        .portpin  = 0x300, .count_to_active = 3, .count_to_inactive = 2, .active_level = BSP_IO_LEVEL_HIGH,
        .p_ioport = &g_ioport, .p_callback = 0
    },
    {
        .portpin  = 0x400, .count_to_active = 3, .count_to_inactive = 3, .active_level = BSP_IO_LEVEL_LOW,
        .p_ioport = &g_ioport, .p_callback = 0
    },
    {
        .portpin           = 0x500, .count_to_active = 3, .count_to_inactive = 3, .active_level = BSP_IO_LEVEL_HIGH,
        .p_ioport          = &g_ioport, .p_callback = 0,
        .event_enable_mask = GPIO_DEBOUNCE_EVENT_PRESSED
    },
};

gpio_debounce_ctrl_t g_button_ctrl[] =
{
    {},
    {},
    {},
    {},
    {},
};

gpio_debounce_instance_t g_button_instance[] =
{
    {.p_ctrl = &g_button_ctrl[0], .p_cfg = &g_button_cfg[0]},
    {.p_ctrl = &g_button_ctrl[1], .p_cfg = &g_button_cfg[1]},
    {.p_ctrl = &g_button_ctrl[2], .p_cfg = &g_button_cfg[2]},
    {.p_ctrl = &g_button_ctrl[3], .p_cfg = &g_button_cfg[3]},
    {.p_ctrl = &g_button_ctrl[4], .p_cfg = &g_button_cfg[4]},
};
