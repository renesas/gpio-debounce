#include "rs_gpio_debounce_cfg_fake.h"
#include "bsp_api.h"
#include "rs_gpio_debounce.h"
#include "pin_data.h"

static void stub_callback (gpio_debounce_callback_args_t const * const p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

const gpio_debounce_cfg_t g_gpio_debounce_cfg_ref =
{
    .active_level      = BSP_IO_LEVEL_HIGH,
    .count_to_active   = 5,
    .count_to_inactive = 5,
    .event_enable_mask = GPIO_DEBOUNCE_EVENT_PRESSED | GPIO_DEBOUNCE_EVENT_RELEASED,
    .portpin           = 0x100,
    .p_ioport          = &g_ioport,
    .p_callback        = stub_callback,
    .p_context         = (void *) -1
};
