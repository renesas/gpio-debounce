#include "bsp_api.h"
#include "test_shared.h"
#include "pin_api_spy.h"
#include "r_ioport_api.h"

int  iter = 0;
bool open = false;

#define INVALID_ERR    99999

fsp_err_t cur_err = INVALID_ERR;

#define INJECT_ERR()                  \
        if (cur_err != INVALID_ERR) { \
            fsp_err_t save = cur_err; \
            cur_err = INVALID_ERR;    \
            return save;              \
        }

const ioport_api_t g_ioport_on_ioport =
{
    .open    = R_PinSpy_Open,
    .close   = R_PinSpy_Close,
    .pinRead = R_PinSpy_PinRead
};

fsp_err_t R_PinSpy_Open (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg) {
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_cfg);

    INJECT_ERR();
    if (open)
    {
        return FSP_ERR_ALREADY_OPEN;
    }

    iter = 0;
    open = true;

    return FSP_SUCCESS;
}

fsp_err_t R_PinSpy_Close (ioport_ctrl_t * const p_ctrl) {
    FSP_PARAMETER_NOT_USED(p_ctrl);

    INJECT_ERR();
    if (!open)
    {
        return FSP_ERR_NOT_OPEN;
    }

    iter = 0;
    open = false;

    return FSP_SUCCESS;
}

fsp_err_t R_PinSpy_PinRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value) {
    FSP_PARAMETER_NOT_USED(p_ctrl);

    INJECT_ERR();
    if (!open)
    {
        return FSP_ERR_NOT_OPEN;
    }

    if (pin == PORTPIN_1)
    {
        *p_pin_value = (bsp_io_level_t) arr1[iter];
    }
    else
    {
        *p_pin_value = (bsp_io_level_t) arr2[iter];
    }

    return FSP_SUCCESS;
}

void pin_spy_advance_tick (void) {
    if (iter < TEST_ARRLEN)
    {
        iter += 1;
    }

    if (iter >= TEST_ARRLEN)
    {
        iter = 0;
    }
}

int pin_spy_get_tick (void) {
    return iter;
}

void pin_spy_inject_error (fsp_err_t err) {
    cur_err = err;
}
