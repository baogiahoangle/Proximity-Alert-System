#ifdef __cplusplus
extern "C" {
#endif

#include "srv_display.h"

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

#ifdef __cplusplus
}
#endif