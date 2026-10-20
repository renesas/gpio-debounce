/***********************************************************************************************************************
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/

#ifndef RS_GPIO_DEBOUNCE_DEMO_H_
#define RS_GPIO_DEBOUNCE_DEMO_H_

#include <rs_gpio_debounce/rs_gpio_debounce.h>

void start_debounce();
void button_cb(const gpio_debounce_callback_args_t * args);

#endif /* RS_GPIO_DEBOUNCE_DEMO_H_ */
