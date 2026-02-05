/**
 * @file       driver_led.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-17-9
 * @author     Hoang Le
 * @brief      Driver for led
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "driver_led.h"

/* Public implementations --------------------------------------------------- */
led_status_t led_init(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  gpio_write_pin(led->port, led->pin, GPIO_STATE_RESET);
  return LED_OK;
}

led_status_t led_on(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  gpio_write_pin(led->port, led->pin, GPIO_STATE_SET);
  return LED_OK;
}

led_status_t led_off(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  gpio_write_pin(led->port, led->pin, GPIO_STATE_RESET);
  return LED_OK;
}

/* End of file -------------------------------------------------------------- */