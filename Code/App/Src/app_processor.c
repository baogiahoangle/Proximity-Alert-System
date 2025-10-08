/**
 * @file       app_processor.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Implementation of the application layer for a distance sensing and display system.
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "app_processor.h"

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

static app_handler_t app_handler =
{
  .is_init = false,
  .status = APP_ERROR
};

/* Public implementations --------------------------------------------------- */
app_status_t app_processor_init()
{
  bsp_system_clock_init();
  bsp_st7735_init();
  bsp_srf05_init();
  bsp_led_init();
  app_handler.is_init = true;
  app_handler.status = APP_OK;

  return APP_OK;
}

app_status_t app_processor_host(uint8_t x)
{
  APP_CHECK_HANDLER_INIT(&app_handler);

  static uint8_t last_x = 2;
  static uint8_t y = 80;
  
  uint16_t color = (last_x < 64) ? ST7735_BLUE : ST7735_WHITE;
  
	// Clear the previous host position
  for(uint8_t dx = 0; dx < 4; dx++)
  {
    for(uint8_t dy = 0; dy < 4; dy++)
    {
      bsp_st7735_draw_pixel(last_x + dx, y + dy, color);
    }
  }

  for(uint8_t dx = 0; dx < 4; dx++)
  {
    for(uint8_t dy = 0; dy < 4; dy++)
    {
      bsp_st7735_draw_pixel(x + dx, y + dy, ST7735_RED);
    }
  }

  if (x < 64) 
  {
    bsp_led_on();
    bsp_st7735_draw_string_center(10, "DANGEROUS", font_7x10, ST7735_RED, ST7735_WHITE);
  }

  else
  {
    bsp_led_off();
		bsp_st7735_fill_rectangle(10, 10, 50, 19, ST7735_WHITE);
		bsp_st7735_fill_rectangle(78, 10, 118, 19, ST7735_WHITE);
    bsp_st7735_draw_string_center(10, "SAFE", font_7x10, ST7735_GREEN, ST7735_WHITE);
  }

  last_x = x;
  return APP_OK;
}

app_status_t app_processor_operates()
{
	static float distance = 0;
  static uint8_t host_position = 0;
  bsp_srf05_get_distance_cm(&distance);
  host_position = (distance * 10);
  app_processor_host(host_position);
	return APP_OK;
}


/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */