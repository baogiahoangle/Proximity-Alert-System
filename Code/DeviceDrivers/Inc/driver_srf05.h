#ifndef __DRIVER_SRF05_H
#define __DRIVER_SRF05_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "hal_gpio.h"
#include "hal_tim.h"

typedef struct
{
  gpio_t *port;
  uint16_t pin_trigger;
  uint16_t pin_echo;
  uint16_t htim;
}
srf05_t;

typedef enum
{
  SRF05_OK          = 0x00U,
  SRF05_ERROR       = 0x01U,
  SRF05_BUSY        = 0x02U,
  SRF05_PARAM_ERROR = 0x03U,
  SRF05_TIM_ERROR   = 0x04U,
  SRF05_NOT_INIT    = 0x05U
}
srf05_status_t;

typedef struct
{
  bool srf05_is_init;
  srf05_status_t status;
  srf05_t *srf05;
}
srf05_handler_t;

srf05_status_t srf05_init(srf05_t *srf05);
srf05_status_t srf05_trigger(srf05_t *srf05);
srf05_status_t srf05_get_distance_cm(srf05_t *srf05, float *distance_cm);

#ifdef __cplusplus
}
#endif

#endif /* __DRIVER_SRF05_H */