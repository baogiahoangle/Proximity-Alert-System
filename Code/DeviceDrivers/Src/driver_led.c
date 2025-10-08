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

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Private prototypes ------------------------------------------------------- */
/* Public implementations --------------------------------------------------- */
led_status_t led_init(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
  return LED_OK;
}

led_status_t led_on(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
  return LED_OK;
}

led_status_t led_off(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
  return LED_OK;
}

led_status_t led_toggle(led_t *led)
{
  if (led == NULL || led->port == NULL)
    return LED_ERROR;
  HAL_GPIO_TogglePin(led->port, led->pin);
  return LED_OK;
}
/* Private implementations -------------------------------------------------- */


/* End of file -------------------------------------------------------------- */