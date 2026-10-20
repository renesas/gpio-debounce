#ifndef BUTTON_DATA_H
#define BUTTON_DATA_H
#include "rs_gpio_debounce.h"

#define BUTTON_ARRLEN    5

extern gpio_debounce_cfg_t      g_button_cfg[BUTTON_ARRLEN];
extern gpio_debounce_ctrl_t     g_button_ctrl[BUTTON_ARRLEN];
extern gpio_debounce_instance_t g_button_instance[BUTTON_ARRLEN];

#endif
