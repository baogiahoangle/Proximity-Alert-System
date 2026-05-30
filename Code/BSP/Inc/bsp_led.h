#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_led.h"

#define BSP_VERSION_1

#ifdef BSP_VERSION_1
#define LED_GPIO_PORT    GPIOB
#define LED_GPIO_PIN     GPIO_PIN_4
#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
#endif /* BSP_VERSION_2 */

#define BSP_LED_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->is_init || (handler)->status != LED_OK) { \
            return LED_ERROR; \
        } \
    } while(0)

#define BSP_LED_INIT_CHECK(func_call) \
    do { \
        led_status_t status = (func_call); \
        if (status != LED_OK) { \
            return status; \
        } \
    } while(0)

#define BSP_LED_CHECK_STATUS(handler, function) \
    do { \
           led_status_t status = (function); \
           (handler)->status = status; \
           return (status); \
    } while(0)

led_status_t bsp_led_gpio_init();
led_status_t bsp_led_init();
led_status_t bsp_led_on();
led_status_t bsp_led_off();

#ifdef __cplusplus
}
#endif

#endif /* __BSP_LED_H */