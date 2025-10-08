/**
 * @file       driver_led.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-17-9
 * @author     Hoang Le
 * @brief      Driver for led
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/**
 * @brief  led configuration structure
 * @note   Contains GPIO port/pin for led signal
 */
typedef struct
{
  GPIO_TypeDef *port;       /**< GPIO port for led pin */
  uint16_t pin;             /**< GPIO pin for led signal */
}
led_t;

/**
 * @brief  Display operation status codes
 * @note   Used to track the success/failure of display operations
 */
typedef enum
{
  LED_OK         = 0x00U,  /**< Operation completed successfully */
  LED_ERROR      = 0x01U,  /**< Operation failed */
}
led_status_t;

/**
 * @brief  Display handler structure for tracking display state
 * @note   Maintains initialization status and current operation state
 */
typedef struct
{
  bool is_init;         /**< Indicates if the led is initialized */
  led_status_t status;  /**< Current operation status */
}
led_handler_t;

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Public APIs -------------------------------------------------------------- */

/**
 * @brief  Initialize the led
 * @param  led: Pointer to led configuration structure
 * 
 * @return led_status_t: Status of the initialization operation
 */
led_status_t led_init(led_t *led);

/**
 * @brief  Turn on the led
 * @param  led: Pointer to led configuration structure
 * 
 * @return led_status_t: Status of the operation
 */
led_status_t led_on(led_t *led);

/**
 * @brief  Turn off the led
 * @param  led: Pointer to led configuration structure
 * 
 * @return led_status_t: Status of the operation
 */
led_status_t led_off(led_t *led);

/**
 * @brief  Toggle the led state
 * @param  led: Pointer to led configuration structure
 * 
 * @return led_status_t: Status of the operation
 */
led_status_t led_toggle(led_t *led);
/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __DRIVER_LED_H */

/* End of file -------------------------------------------------------------- */