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
  rcc_enable_port_b();
  gpio_config(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_MODE_OUTPUT_PP);

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

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */