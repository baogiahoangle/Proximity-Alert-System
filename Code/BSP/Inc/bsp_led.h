/**
 * @file       bsp_led.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Board support package for led
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "driver_led.h"

#define BSP_VERSION_1

#ifdef BSP_VERSION_1
/* Public defines ----------------------------------------------------------- */
/* GPIO Configuration */
#define LED_GPIO_PORT    GPIOB
#define LED_GPIO_PIN     GPIO_PIN_4

#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
/* Public defines ----------------------------------------------------------- */
/* GPIO Configuration */
#endif /* BSP_VERSION_2 */

/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */

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

/* Public variables --------------------------------------------------------- */
/* Public APIs -------------------------------------------------------------- */
/**
 * @brief         Initializes GPIO pins for LED operation.
 * 
 * @return        led_status_t LED_OK if GPIOs initialized successfully,
 *                             LED_ERROR if any error occurs during initialization.
 * 
 * @note          Configures LED pin as output.
 */
led_status_t bsp_led_gpio_init();

/**
 * @brief         This function maps the hardware resources (GPIO) to the
 *                LED driver structure.
 *
 * @param[in]     None
 *
 * @return        led_status_t LED_OK if initialization is successful,
 *                             LED_ERROR if any error occurs during initialization.
 *
 * @note          None
 */
led_status_t bsp_led_init();

/**
 * @brief         Turn on the LED.
 *
 * @param[in]     None
 *
 * @return        led_status_t LED_OK if operation is successful,
 *                             LED_ERROR if any error occurs during operation.
 *
 * @note          None
 */
led_status_t bsp_led_on();

/**
 * @brief         Turn off the LED.
 *
 * @param[in]     None
 *
 * @return        led_status_t LED_OK if operation is successful,
 *                             LED_ERROR if any error occurs during operation.
 *
 * @note          None
 */
led_status_t bsp_led_off();

/**
 * @brief         Toggle the LED state.
 *
 * @param[in]     None
 *
 * @return        led_status_t LED_OK if operation is successful,
 *                             LED_ERROR if any error occurs during operation.
 *
 * @note          None
 */
led_status_t bsp_led_toggle();
/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __BSP_LED_H */

/* End of file -------------------------------------------------------------- */