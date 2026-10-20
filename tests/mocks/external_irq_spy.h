#ifndef EXTERNAL_IRQ_SPY_H_
#define EXTERNAL_IRQ_SPY_H_
#include "r_external_irq_api.h"

typedef struct st_irq_spy_instance_ctrl
{
    uint32_t open;                     ///< Used to determine if channel control block is in use
    uint32_t enabled;                  ///< Used to determine if external IRQ is enabled
} irq_spy_instance_ctrl_t;

/** User configuration structure, used in open function */
typedef struct st_irq_spy_instance_cfg
{
    uint8_t                         channel;          ///< Hardware channel used.
    uint8_t                         ipl;              ///< Interrupt priority
    IRQn_Type                       irq;              ///< Interrupt number assigned to this instance
    external_irq_trigger_t          trigger;          ///< Trigger setting.
    external_irq_clock_source_div_t clock_source_div; ///< Digital filter clock divisor setting.
    bool filter_enable;                               ///< Digital filter enable/disable selection.

    /** Callback provided external input trigger occurs. */
    void (* p_callback)(external_irq_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref external_irq_callback_args_t. */
    void       * p_context;
    void const * p_extend;             ///< External IRQ hardware dependent configuration.
} irq_spy_instance_cfg_t;

extern const external_irq_api_t g_external_irq_on_irq_spy;

fsp_err_t Spy_ExternalIrqOpen(external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg);

fsp_err_t Spy_ExternalIrqEnable(external_irq_ctrl_t * const p_api_ctrl);

fsp_err_t Spy_ExternalIrqDisable(external_irq_ctrl_t * const p_api_ctrl);

// fsp_err_t Spy_ExternalIrqCallbackSet(external_irq_ctrl_t * const          p_api_ctrl,
// void (                             * p_callback)(external_irq_callback_args_t *),
// void * const                         p_context,
// external_irq_callback_args_t * const p_callback_memory);

fsp_err_t Spy_ExternalIrqClose(external_irq_ctrl_t * const p_api_ctrl);

bool external_irq_spy_is_enabled(irq_spy_instance_ctrl_t * const p_ctrl);

#endif
