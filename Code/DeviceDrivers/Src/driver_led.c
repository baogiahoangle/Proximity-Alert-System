#include "driver_led.h"

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