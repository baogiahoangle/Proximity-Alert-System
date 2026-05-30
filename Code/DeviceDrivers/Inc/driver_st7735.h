#ifndef __DRIVER_ST7735_H
#define __DRIVER_ST7735_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hal_gpio.h"
#include <stdio.h>
#include <stdbool.h>
#include "asset_st7735_font.h"
#include "math.h"
#include <string.h>

#define ST7735_WIDTH                          (128)
#define ST7735_HEIGHT                         (160)

#define ST7735_BLACK                          (0x0000)
#define ST7735_WHITE                          (0xFFFF)
#define ST7735_BLUE                           (0xFE00)
#define ST7735_GREEN                          (0x07E0)
#define ST7735_RED                            (0x001F)
#define ST7735_YELLOW                         (0xFFE0)
#define ST7735_MAGENTA                        (0xF81F)
#define ST7735_CYAN                           (0x07FF)

typedef struct
{
  gpio_t *port;
  uint16_t pin_cs;
  uint16_t pin_a0;
  uint16_t pin_reset;
  SPI_HandleTypeDef *hspi;
}
st7735_t;

typedef enum
{
  ST7735_OK          = 0x00U,
  ST7735_ERROR       = 0x01U,
  ST7735_BUSY        = 0x02U,
  ST7735_PARAM_ERROR = 0x03U,
  ST7735_SPI_ERROR   = 0x04U,
  ST7735_NOT_INIT    = 0x05U
}
st7735_status_t;

typedef struct
{
  bool st7735_is_init;
  st7735_status_t status;
  st7735_t *st7735;
}
st7735_handler_t;

typedef struct
{
  uint8_t cmd;
  uint8_t num_args;
  const uint8_t *args;
}
st7735_init_cmd_t;

st7735_status_t st7735_write_cmd(st7735_t *me, uint8_t cmd);
st7735_status_t st7735_write_data(st7735_t *me, uint8_t data);
st7735_status_t st7735_send_cmd_list(st7735_t *me, const st7735_init_cmd_t *cmd_list);
st7735_status_t st7735_init(st7735_t *me);
st7735_status_t st7735_set_pos(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
st7735_status_t st7735_draw_pixel(st7735_t *me, uint8_t x, uint8_t y, uint16_t color);
st7735_status_t st7735_draw_char(st7735_t *me, uint8_t x, uint8_t y, char ch, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t st7735_draw_string(st7735_t *me, uint8_t x, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t st7735_full_screen(st7735_t *me, uint16_t color);
st7735_status_t st7735_draw_rectangle(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
st7735_status_t st7735_draw_rhombus(st7735_t *me, uint8_t x, uint8_t y, uint8_t d, uint16_t color);
st7735_status_t st7735_draw_circle(st7735_t *me, uint8_t x, uint8_t y, uint8_t r, uint16_t color);
st7735_status_t st7735_fill_rectangle(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
st7735_status_t st7735_fill_rhombus(st7735_t *me, uint8_t x, uint8_t y, uint8_t d, uint16_t color);
st7735_status_t st7735_draw_string_center(st7735_t *me, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t st7735_draw_password_mask(st7735_t *me, uint8_t entered_digits, uint8_t total_digits, uint8_t y, uint16_t active_color, uint16_t inactive_color);

#ifdef __cplusplus
}
#endif

#endif /* __DRIVER_ST7735_H */