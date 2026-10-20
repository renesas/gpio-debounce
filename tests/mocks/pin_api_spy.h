#ifndef _PIN_API_SPY_H
#define _PIN_API_SPY_H

#include "r_ioport_api.h"

#define PORTPIN_1    0x100
#define PORTPIN_2    0x200

extern const ioport_api_t g_ioport_on_ioport;

fsp_err_t R_PinSpy_Open(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_PinSpy_Close(ioport_ctrl_t * const p_ctrl);
fsp_err_t R_PinSpy_PinRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);

void pin_spy_advance_tick(void);
int  pin_spy_get_tick(void);
void pin_spy_inject_error(fsp_err_t err);

#endif
