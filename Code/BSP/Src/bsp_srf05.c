/**
 * @file       bsp_srf05.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Board support package for SRF05 Ultrasonic Distance Sensor
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_srf05.h"

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
TIM_HandleTypeDef htim1;
/* Private variables -------------------------------------------------------- */
static srf05_t srf05_device =
{
  .port = NULL,
  .pin_trigger = 0,
  .pin_echo = 0,
  .htim = NULL,
};

static srf05_handler_t srf05_bsp_handler =
{
  .status = SRF05_NOT_INIT,
  .srf05 = &srf05_device,
  .srf05_is_init = false,
};

/* Public implementations --------------------------------------------------- */

srf05_status_t bsp_srf05_gpio_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SRF05_GPIO_PORT, SRF05_GPIO_PIN_TRIGGER, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = SRF05_GPIO_PIN_TRIGGER;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SRF05_GPIO_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = SRF05_GPIO_PIN_ECHO;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SRF05_GPIO_PORT, &GPIO_InitStruct);
  return SRF05_OK;
}

srf05_status_t bsp_srf05_tim_init()
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  SRF05_HTIM.Instance = SRF05_TIM_INSTANCE;
  SRF05_HTIM.Init.Prescaler = 71;
  SRF05_HTIM.Init.CounterMode = TIM_COUNTERMODE_UP;
  SRF05_HTIM.Init.Period = 65535;
  SRF05_HTIM.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  SRF05_HTIM.Init.RepetitionCounter = 0;
  SRF05_HTIM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&SRF05_HTIM) != HAL_OK)
  {
    return SRF05_ERROR;
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&SRF05_HTIM, &sClockSourceConfig) != HAL_OK)
  {
    return SRF05_ERROR;
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&SRF05_HTIM, &sMasterConfig) != HAL_OK)
  {
    return SRF05_ERROR;
  }
  return SRF05_OK;
}

srf05_status_t bsp_srf05_init()
{
  // Initialize GPIOs
  BSP_SRF05_INIT_CHECK(bsp_srf05_gpio_init());

  // Initialize Timer
  BSP_SRF05_INIT_CHECK(bsp_srf05_tim_init());

  // Link BSP hardware resources to the SRF05 driver instance
  srf05_bsp_handler.srf05->port = SRF05_GPIO_PORT;
  srf05_bsp_handler.srf05->pin_trigger = SRF05_GPIO_PIN_TRIGGER;
  srf05_bsp_handler.srf05->pin_echo = SRF05_GPIO_PIN_ECHO;
  srf05_bsp_handler.srf05->htim = &SRF05_HTIM;

  srf05_status_t status = srf05_init(srf05_bsp_handler.srf05);
  if (status == SRF05_OK)
  {
    srf05_bsp_handler.srf05_is_init = true;
    srf05_bsp_handler.status = SRF05_OK; // Set BSP status to OK after successful init
  }
  else
  {
    srf05_bsp_handler.srf05_is_init = false;
    srf05_bsp_handler.status = status;
  }

  return SRF05_OK;
}

srf05_status_t bsp_srf05_trigger()
{
  BSP_SRF05_CHECK_HANDLER_INIT(&srf05_bsp_handler);
  BSP_SRF05_CHECK_STATUS(&srf05_bsp_handler, srf05_trigger(srf05_bsp_handler.srf05));
}

srf05_status_t bsp_srf05_get_distance_cm(float *distance_cm)
{
  BSP_SRF05_CHECK_HANDLER_INIT(&srf05_bsp_handler);
  BSP_SRF05_CHECK_STATUS(&srf05_bsp_handler, srf05_get_distance_cm(srf05_bsp_handler.srf05, distance_cm));
}

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */