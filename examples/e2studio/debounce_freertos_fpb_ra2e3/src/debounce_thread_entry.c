#include <debounce_thread.h>

extern void start_debounce(void);

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void debounce_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    start_debounce();
}
