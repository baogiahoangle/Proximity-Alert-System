#include "driver_srf05.h"

#define SRF05_SOUND_VELOCITY_CM_PER_US   (0.0343f)

srf05_status_t srf05_init(srf05_t *srf05)
{
  if (srf05 == NULL || srf05->port == NULL || srf05->htim == NULL)
    return SRF05_PARAM_ERROR;
  
  return SRF05_OK;
}

srf05_status_t srf05_trigger(srf05_t *srf05)
{
  if (srf05 == NULL || srf05->port == NULL) 
    return SRF05_PARAM_ERROR;
  
  gpio_write_pin(srf05->port, srf05->pin_trigger, GPIO_STATE_SET);
  delay_ms(1);
  gpio_write_pin(srf05->port, srf05->pin_trigger, GPIO_STATE_RESET);

  return SRF05_OK;
}

srf05_status_t srf05_get_distance_cm(srf05_t *srf05, float *distance_cm)
{
  if (srf05 == NULL || srf05->port == NULL || distance_cm == NULL) 
    return SRF05_PARAM_ERROR;

  srf05_trigger(srf05);

  while (gpio_read_pin(srf05->port, srf05->pin_echo) == GPIO_STATE_RESET);

  TIM2_CNT = 0;
  while (gpio_read_pin(srf05->port, srf05->pin_echo) == GPIO_STATE_SET);

  uint32_t echo_duration = TIM2_CNT;
  
  *distance_cm = (echo_duration * SRF05_SOUND_VELOCITY_CM_PER_US) / 2.0f;

  if (*distance_cm > 10)
    *distance_cm = 10;

  if (*distance_cm < 0)
    *distance_cm = 0;

  return SRF05_OK;
}