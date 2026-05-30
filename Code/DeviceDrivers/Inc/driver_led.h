#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "hal_rcc.h"
#include "hal_gpio.h"

typedef struct
{
  gpio_t *port;
  uint16_t pin;
}
led_t;

typedef enum
{
  LED_OK         = 0x00U,
  LED_ERROR      = 0x01U,
}
led_status_t;

typedef struct
{
  bool is_init;
  led_status_t status;
}
led_handler_t;

led_status_t led_init(led_t *led);
led_status_t led_on(led_t *led);
led_status_t led_off(led_t *led);

#ifdef __cplusplus
}
#endif

#endif /* __DRIVER_LED_H */