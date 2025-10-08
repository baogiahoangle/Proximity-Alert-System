/**
 * @file       srv_display.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Implementation of the system service layer for display system.
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "srv_display.h"

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Public implementations --------------------------------------------------- */
void srv_display()
{
  bsp_st7735_draw_rectangle(0, 0, 127, 159, ST7735_MAGENTA);
  for(uint8_t x = 1; x < ST7735_WIDTH - 1; x++)
  {
    uint16_t color = (x < 64) ? ST7735_BLUE : ST7735_WHITE;
    for(uint8_t y = 1; y < ST7735_HEIGHT - 1; y++)
    {
			bsp_st7735_draw_pixel(x, y, color);
    }
  }
	return;
}

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */