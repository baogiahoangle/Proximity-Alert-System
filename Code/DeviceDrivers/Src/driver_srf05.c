/**
 * @file       driver_st7735.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-17-9
 * @author     Hoang Le
 * @brief      Driver for SRF05 Ultrasonic Distance Sensor
 * @note       None
 * @example    None
 */

/* Public includes ---------------------------------------------------------- */
#include "driver_srf05.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */
#define SRF05_SOUND_VELOCITY_CM_PER_US   (0.0343f)  /**< Speed of sound in cm/us at 20°C */

/* Private enumerate/structure ---------------------------------------------- */
/* Private macros ----------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Private prototypes ------------------------------------------------------- */
/* Public implementations --------------------------------------------------- */

srf05_status_t srf05_init(srf05_t *srf05)
{
  if (srf05 == NULL || srf05->port == NULL || srf05->htim == NULL)
    return SRF05_PARAM_ERROR;
  
  if (HAL_TIM_Base_Start(srf05->htim) != HAL_OK) 
    return SRF05_TIM_ERROR;
  
  return SRF05_OK;
}

srf05_status_t srf05_trigger(srf05_t *srf05)
{
  if (srf05 == NULL || srf05->port == NULL) 
    return SRF05_PARAM_ERROR;
  
  HAL_GPIO_WritePin(srf05->port, srf05->pin_trigger, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(srf05->port, srf05->pin_trigger, GPIO_PIN_RESET);

  return SRF05_OK;
}

srf05_status_t srf05_get_distance_cm(srf05_t *srf05, float *distance_cm)
{
  if (srf05 == NULL || srf05->port == NULL || distance_cm == NULL) 
    return SRF05_PARAM_ERROR;
  srf05_trigger(srf05);
  uint32_t start_tick = HAL_GetTick();
  while (HAL_GPIO_ReadPin(srf05->port, srf05->pin_echo) == GPIO_PIN_RESET);
  /*
  {
    if ((HAL_GetTick() - start_tick) > 100) 
      return SRF05_BUSY; // Timeout waiting for echo to go high
  }
  */
  
  __HAL_TIM_SET_COUNTER(srf05->htim, 0);
  while (HAL_GPIO_ReadPin(srf05->port, srf05->pin_echo) == GPIO_PIN_SET);
  /*
  {
    if ((HAL_GetTick() - start_tick) > 100) 
      return SRF05_BUSY; // Timeout waiting for echo to go low
  }
  */
  uint32_t echo_duration = __HAL_TIM_GET_COUNTER(srf05->htim);
  
  *distance_cm = (echo_duration * SRF05_SOUND_VELOCITY_CM_PER_US) / 2.0f;
	
	if (*distance_cm > 10)
	{
    *distance_cm = 10;
	}
	
	if (*distance_cm < 0)
	{
    *distance_cm = 0;
	}
  return SRF05_OK;
}
/* Private implementations -------------------------------------------------- */


/* End of file -------------------------------------------------------------- */