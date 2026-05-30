#ifndef __BSP_SRF05_H
#define __BSP_SRF05_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_srf05.h"

#define BSP_VERSION_1

#ifdef BSP_VERSION_1
#define SRF05_GPIO_PORT                  GPIOB
#define SRF05_GPIO_PIN_TRIGGER           GPIO_PIN_5
#define SRF05_GPIO_PIN_ECHO              GPIO_PIN_6

#define SRF05_HTIM                       htim1
#define SRF05_TIM_INSTANCE               TIM1
#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
#define SRF05_GPIO_PORT                  GPIOB
#define SRF05_GPIO_PIN_TRIGGER           GPIO_PIN_5
#define SRF05_GPIO_PIN_ECHO              GPIO_PIN_6

#define SRF05_HTIM                       htim2
#define SRF05_TIM_INSTANCE               TIM2
#endif /* BSP_VERSION_2 */

#define BSP_SRF05_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->srf05_is_init || (handler)->status != SRF05_OK) { \
            return SRF05_NOT_INIT; \
        } \
        (handler)->status = SRF05_BUSY; \
    } while(0)

#define BSP_SRF05_CHECK_STATUS(handler, function) \
    do { \
           srf05_status_t status = (function); \
           (handler)->status = status; \
           return (status); \
    } while(0)

#define BSP_SRF05_INIT_CHECK(func_call) \
    do { \
        srf05_status_t status = (func_call); \
        if (status != SRF05_OK) { \
            return status; \
        } \
    } while(0)

srf05_status_t bsp_srf05_gpio_init();
srf05_status_t bsp_srf05_tim_init();
srf05_status_t bsp_srf05_init();
srf05_status_t bsp_srf05_trigger();
srf05_status_t bsp_srf05_get_distance_cm(float *distance_cm);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SRF05_H */