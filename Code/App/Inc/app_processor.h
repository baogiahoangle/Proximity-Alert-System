#ifndef __APP_PROCESSOR_H
#define __APP_PROCESSOR_H 

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_system_clock.h"
#include "bsp_st7735.h"
#include "bsp_srf05.h"
#include "bsp_led.h"

typedef enum
{
  APP_OK            = 0x00U,
  APP_ERROR         = 0x01U,
  APP_BUSY          = 0x02U,
  APP_NOT_INIT      = 0x03U
}
app_status_t;

typedef struct
{
  bool is_init;
  app_status_t status;
}
app_handler_t;

#define APP_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->is_init || (handler)->status != APP_OK) { \
            return APP_NOT_INIT; \
        } \
    } while(0)

app_status_t app_processor_init();
app_status_t app_processor_host(uint8_t x);
app_status_t app_processor_operates();

#ifdef __cplusplus
}
#endif

#endif /* __APP_PROCESSOR_H */