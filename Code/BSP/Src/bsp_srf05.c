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
  rcc_enable_port_b();

  /*Configure GPIO pin : PB5 */
  gpio_config(SRF05_GPIO_PORT, SRF05_GPIO_PIN_TRIGGER, GPIO_MODE_OUTPUT_PP);

  /*Configure GPIO pin : PB6 */
  gpio_config(SRF05_GPIO_PORT, SRF05_GPIO_PIN_ECHO, GPIO_MODE_INPUT);
  return SRF05_OK;
}

srf05_status_t bsp_srf05_tim_init()
{
  tim2_init_it();
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
  srf05_bsp_handler.srf05->htim = SRF05_HTIM;

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