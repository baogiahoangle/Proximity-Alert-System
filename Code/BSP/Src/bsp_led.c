/**
 * @file       bsp_led.c
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
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_led.h"

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static led_t led_device =
{
  .port = NULL,
  .pin = 0,
};

static led_handler_t led_bsp_handler =
{
  .is_init = false,
  .status = LED_ERROR,
};

/* Public implementations --------------------------------------------------- */

led_status_t bsp_led_gpio_init()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = LED_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

  return LED_OK;
}

led_status_t bsp_led_init()
{
  // Initialize GPIOs
  BSP_LED_INIT_CHECK(bsp_led_gpio_init());

  led_bsp_handler.is_init = true;
  led_device.port = LED_GPIO_PORT;
  led_device.pin = LED_GPIO_PIN;

  led_status_t status = led_init(&led_device);
  if (status == LED_OK)
  {
    led_bsp_handler.status = LED_OK; 
  }
  else
  {
    led_bsp_handler.is_init = false;
    led_bsp_handler.status = status;
  }

  return status;
}

led_status_t bsp_led_on()
{
  BSP_LED_CHECK_HANDLER_INIT(&led_bsp_handler);
  BSP_LED_CHECK_STATUS(&led_bsp_handler, led_on(&led_device));
}

led_status_t bsp_led_off()
{
  BSP_LED_CHECK_HANDLER_INIT(&led_bsp_handler);
  BSP_LED_CHECK_STATUS(&led_bsp_handler, led_off(&led_device));
}

led_status_t bsp_led_toggle()
{
  BSP_LED_CHECK_HANDLER_INIT(&led_bsp_handler);
  BSP_LED_CHECK_STATUS(&led_bsp_handler, led_toggle(&led_device));
}

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */