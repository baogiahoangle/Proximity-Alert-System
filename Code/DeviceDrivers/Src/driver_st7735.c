#include "driver_st7735.h"

#define ST7735_SOFT_RESET                     (0x01)
#define ST7735_SLEEP_OUT                      (0x11)
#define ST7735_DISPLAY_ON                     (0x29)
#define ST7735_DISPLAY_INVERSION_OFF          (0x20)

#define ST7735_MEMORY_DATA_ACCESS_CONTROL     (0x36)
#define ST7735_INTERFACE_PIXEL_FORMAT         (0x3A)
#define ST7735_COLUMN_ADDRESS_SET             (0x2A)
#define ST7735_ROW_ADDRESS_SET                (0x2B)
#define ST7735_MEMORY_WRITE                   (0x2C)

#define ST7735_FRAME_RATE_CONTROL_NORMAL      (0xB1)
#define ST7735_FRAME_RATE_CONTROL_IDLE        (0xB2)
#define ST7735_FRAME_RATE_CONTROL_PARTIAL     (0xB3)
#define ST7735_DISPLAY_INVERSION_CONTROL      (0xB4)

#define ST7735_POWER_CONTROL_1                (0xC0)
#define ST7735_POWER_CONTROL_2                (0xC1)
#define ST7735_POWER_CONTROL_3                (0xC2)
#define ST7735_POWER_CONTROL_4                (0xC3)
#define ST7735_POWER_CONTROL_5                (0xC4)
#define ST7735_VCOM_CONTROL_1                 (0xC5)

#define ST7735_POSITIVE_GAMMA_CORRECTION      (0xE0)
#define ST7735_NEGATIVE_GAMMA_CORRECTION      (0xE1)

#define ST7735_CMD_END                        (0xFF)

#define ST7735_RESET_DELAY                    (20U)
#define ST7735_INIT_DELAY                     (150U)
#define ST7735_SLEEP_OUT_DELAY                (255U)
#define ST7735_DISPLAY_ON_DELAY               (100U)
#define ST7735_SPI_TIMEOUT                    (100U)

#define ST7735_CHECK_STATUS(call) \
    do { \
        st7735_status_t status = (call); \
        if (status != ST7735_OK) { \
            return status; \
        } \
    } while(0)

const uint8_t ST7735_FRAME_RATE_CONTROL_NORMAL_VAL[] = {0x01, 0x2C, 0x2D};
const uint8_t ST7735_FRAME_RATE_CONTROL_IDLE_VAL[] = {0x01, 0x2C, 0x2D};
const uint8_t ST7735_FRAME_RATE_CONTROL_PARTIAL_VAL[] = {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};
const uint8_t ST7735_DISPLAY_INVERSION_CONTROL_VAL[] = {0x07};
const uint8_t ST7735_POWER_CONTROL_1_VAL[] = {0xA2, 0x02, 0x84};
const uint8_t ST7735_POWER_CONTROL_2_VAL[] = {0xC5};
const uint8_t ST7735_POWER_CONTROL_3_VAL[] = {0x0A, 0x00};
const uint8_t ST7735_POWER_CONTROL_4_VAL[] = {0x8A, 0x2A};
const uint8_t ST7735_POWER_CONTROL_5_VAL[] = {0x8A, 0xEE};
const uint8_t ST7735_VCOM_CONTROL_1_VAL[] = {0x0E};
const uint8_t ST7735_POSITIVE_GAMMA_CORRECTION_VAL[] = {0x0F, 0x1A, 0x0F, 0x18, 0x2F, 0x28, 0x20, 0x22, 0x1F, 0x1B, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10};
const uint8_t ST7735_NEGATIVE_GAMMA_CORRECTION_VAL[] = {0x0F, 0x1B, 0x0F, 0x17, 0x33, 0x2C, 0x29, 0x2E, 0x30, 0x30, 0x39, 0x3F, 0x00, 0x07, 0x03, 0x10};
const uint8_t ST7735_MEMORY_DATA_ACCESS_CONTROL_VAL = 0xC8;
const uint8_t ST7735_INTERFACE_PIXEL_FORMAT_VAL = 0x05;

static const st7735_init_cmd_t init_cmds[] = {
  {ST7735_FRAME_RATE_CONTROL_NORMAL, 3, ST7735_FRAME_RATE_CONTROL_NORMAL_VAL},
  {ST7735_FRAME_RATE_CONTROL_IDLE, 3, ST7735_FRAME_RATE_CONTROL_IDLE_VAL},
  {ST7735_FRAME_RATE_CONTROL_PARTIAL, 6, ST7735_FRAME_RATE_CONTROL_PARTIAL_VAL},
  {ST7735_DISPLAY_INVERSION_CONTROL, 1, ST7735_DISPLAY_INVERSION_CONTROL_VAL},
  {ST7735_POWER_CONTROL_1, 3, ST7735_POWER_CONTROL_1_VAL},
  {ST7735_POWER_CONTROL_2, 1, ST7735_POWER_CONTROL_2_VAL},
  {ST7735_POWER_CONTROL_3, 2, ST7735_POWER_CONTROL_3_VAL},
  {ST7735_POWER_CONTROL_4, 2, ST7735_POWER_CONTROL_4_VAL},
  {ST7735_POWER_CONTROL_5, 2, ST7735_POWER_CONTROL_5_VAL},
  {ST7735_VCOM_CONTROL_1, 1, ST7735_VCOM_CONTROL_1_VAL},
  {ST7735_POSITIVE_GAMMA_CORRECTION, 16, ST7735_POSITIVE_GAMMA_CORRECTION_VAL},
  {ST7735_NEGATIVE_GAMMA_CORRECTION, 16, ST7735_NEGATIVE_GAMMA_CORRECTION_VAL},
  {ST7735_CMD_END, 0, NULL}
};

st7735_status_t st7735_write_cmd(st7735_t *me, uint8_t cmd)
{
  if (me == NULL || me->hspi == NULL) 
    return ST7735_PARAM_ERROR;

  gpio_write_pin(me->port, me->pin_a0, GPIO_STATE_RESET);
  gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_RESET);

  if (HAL_SPI_Transmit(me->hspi, &cmd, 1, ST7735_SPI_TIMEOUT) != HAL_OK)
  {
    gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_SET);
    return ST7735_SPI_ERROR;
  }
  
  gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_SET);
  return ST7735_OK;
}

st7735_status_t st7735_write_data(st7735_t *me, uint8_t data)
{
  if (me == NULL || me->hspi == NULL) 
    return ST7735_PARAM_ERROR;

  gpio_write_pin(me->port, me->pin_a0, GPIO_STATE_SET);
  gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_RESET);

  if (HAL_SPI_Transmit(me->hspi, &data, 1, ST7735_SPI_TIMEOUT) != HAL_OK)
  {
    gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_SET);
    return ST7735_SPI_ERROR;
  }
  
  gpio_write_pin(me->port, me->pin_cs, GPIO_STATE_SET);
  return ST7735_OK;
}

st7735_status_t st7735_send_cmd_list(st7735_t *me, const st7735_init_cmd_t *cmd_list)
{
  if (me == NULL || cmd_list == NULL) 
    return ST7735_PARAM_ERROR;

  for (uint8_t i = 0; cmd_list[i].cmd != ST7735_CMD_END; i++) {
    uint8_t cmd = cmd_list[i].cmd;
    ST7735_CHECK_STATUS(st7735_write_cmd(me, cmd));

    for (uint8_t j = 0; j < cmd_list[i].num_args; j++) {
      ST7735_CHECK_STATUS(st7735_write_data(me, cmd_list[i].args[j]));
    }
  }
  return ST7735_OK;
}

st7735_status_t st7735_init(st7735_t *me)
{
  if (me == NULL || me->hspi == NULL || me->port == NULL) 
    return ST7735_PARAM_ERROR;
  
  gpio_write_pin(me->port, me->pin_reset, GPIO_STATE_RESET);
  HAL_Delay(ST7735_RESET_DELAY);
  gpio_write_pin(me->port, me->pin_reset, GPIO_STATE_SET);
  HAL_Delay(ST7735_INIT_DELAY);

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_SOFT_RESET));
  HAL_Delay(ST7735_INIT_DELAY);
  
  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_SLEEP_OUT));
  HAL_Delay(ST7735_SLEEP_OUT_DELAY);
  
  ST7735_CHECK_STATUS(st7735_send_cmd_list(me, init_cmds));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_MEMORY_DATA_ACCESS_CONTROL));
  ST7735_CHECK_STATUS(st7735_write_data(me, ST7735_MEMORY_DATA_ACCESS_CONTROL_VAL));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_INTERFACE_PIXEL_FORMAT));
  ST7735_CHECK_STATUS(st7735_write_data(me, ST7735_INTERFACE_PIXEL_FORMAT_VAL));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_DISPLAY_INVERSION_OFF));

  ST7735_CHECK_STATUS(st7735_set_pos(me, 0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1));
  
  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_DISPLAY_ON));
  HAL_Delay(ST7735_DISPLAY_ON_DELAY);
  
  return ST7735_OK;
}

st7735_status_t st7735_set_pos(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (x0 >= ST7735_WIDTH || y0 >= ST7735_HEIGHT || 
      x1 >= ST7735_WIDTH || y1 >= ST7735_HEIGHT ||
      x1 < x0 || y1 < y0) 
  {
    return ST7735_PARAM_ERROR;
  }

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_COLUMN_ADDRESS_SET));
  ST7735_CHECK_STATUS(st7735_write_data(me, 0x00));
  ST7735_CHECK_STATUS(st7735_write_data(me, x0));
  ST7735_CHECK_STATUS(st7735_write_data(me, 0x00));
  ST7735_CHECK_STATUS(st7735_write_data(me, x1));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_ROW_ADDRESS_SET));
  ST7735_CHECK_STATUS(st7735_write_data(me, 0x00));
  ST7735_CHECK_STATUS(st7735_write_data(me, y0));
  ST7735_CHECK_STATUS(st7735_write_data(me, 0x00));
  ST7735_CHECK_STATUS(st7735_write_data(me, y1));
  
  return ST7735_OK;
}

st7735_status_t st7735_draw_pixel(st7735_t *me, uint8_t x, uint8_t y, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (x >= ST7735_WIDTH || y >= ST7735_HEIGHT) 
    return ST7735_PARAM_ERROR;

  ST7735_CHECK_STATUS(st7735_set_pos(me, x, y, x, y));
  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_MEMORY_WRITE));
  ST7735_CHECK_STATUS(st7735_write_data(me, (uint8_t)(color >> 8)));
  ST7735_CHECK_STATUS(st7735_write_data(me, (uint8_t)(color & 0xFF)));
  
  return ST7735_OK;
}

st7735_status_t st7735_draw_char(st7735_t *me, uint8_t x, uint8_t y, char ch, font_t font, uint16_t color, uint16_t bgcolor)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (ch < 32 || ch > 127) 
    return ST7735_PARAM_ERROR;
  if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT) || 
     ((x + font.width) > ST7735_WIDTH) || 
     ((y + font.height) > ST7735_HEIGHT))
  {
    return ST7735_PARAM_ERROR;
  }

  uint16_t line;

  for(uint8_t i = 0; i < font.height; i++)
  {
    line = font.data[(ch - 32) * font.height + i];
    for(uint8_t j = 0; j < font.width; j++)
    {
      if((line << j) & 0x8000)
        ST7735_CHECK_STATUS(st7735_draw_pixel(me, x + j, y + i, color));
      else
        ST7735_CHECK_STATUS(st7735_draw_pixel(me, x + j, y + i, bgcolor));
    }
  }
  return ST7735_OK;
}

st7735_status_t st7735_draw_string(st7735_t *me, uint8_t x, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor)
{
  if (!str || !me) 
    return ST7735_PARAM_ERROR;
  
  uint8_t current_x = x;
  uint8_t current_y = y;

  while(*str)
  {
    if((current_x + font.width) > ST7735_WIDTH)
    {
      current_x = 0;
      current_y += font.height;
      if((current_y + font.height) > ST7735_HEIGHT)
        break;
    }

    ST7735_CHECK_STATUS(st7735_draw_char(me, current_x, current_y, *str, font, color, bgcolor));
    
    current_x += font.width;
    str++;
  }
  return ST7735_OK;
}

st7735_status_t st7735_full_screen(st7735_t *me, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  
  ST7735_CHECK_STATUS(st7735_set_pos(me, 0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_MEMORY_WRITE));
  for(uint16_t i = 0; i < ST7735_WIDTH * ST7735_HEIGHT; i++)
  {
    ST7735_CHECK_STATUS(st7735_write_data(me, color >> 8));
    ST7735_CHECK_STATUS(st7735_write_data(me, color & 0xFF));
  }
  return ST7735_OK;
}

st7735_status_t st7735_draw_rectangle(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (x0 >= ST7735_WIDTH || y0 >= ST7735_HEIGHT || 
      x1 >= ST7735_WIDTH || y1 >= ST7735_HEIGHT ||
      x1 < x0 || y1 < y0) 
  {
    return ST7735_PARAM_ERROR;
  }

  ST7735_CHECK_STATUS(st7735_set_pos(me, x0, y0, x1, y1));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_MEMORY_WRITE));
  for(uint16_t x = x0; x <= x1; x++)
  {
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x, y0, color));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x, y1, color));
  }
  for(uint16_t y = y0; y <= y1; y++)
  {
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x0, y, color));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x1, y, color));
  }
  return ST7735_OK;
}

st7735_status_t st7735_draw_rhombus(st7735_t *me, uint8_t x, uint8_t y, uint8_t d, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (d == 0 || (d % 2) != 0)
    return ST7735_PARAM_ERROR;

  uint8_t half_d = d / 2;

  if (x < half_d || x + half_d >= ST7735_WIDTH || 
      y < half_d || y + half_d >= ST7735_HEIGHT) 
  {
    return ST7735_PARAM_ERROR;
  }

  for (uint8_t i = 0; i <= half_d; i++) {
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x - i, y + (half_d - i), color));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x + i, y + (half_d - i), color));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x - i, y - (half_d - i), color));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, x + i, y - (half_d - i), color));
  }
  return ST7735_OK;
}

st7735_status_t st7735_draw_circle(st7735_t *me, uint8_t x, uint8_t y, uint8_t r, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (r == 0)
    return ST7735_PARAM_ERROR;

  if (x < r || x + r >= ST7735_WIDTH || 
      y < r || y + r >= ST7735_HEIGHT) 
  {
    return ST7735_PARAM_ERROR;
  }

  for(uint16_t angle = 0; angle < 360; angle++)
  {
    uint8_t px = x + (uint8_t)(r * cos(angle * 3.14159 / 180.0));
    uint8_t py = y + (uint8_t)(r * sin(angle * 3.14159 / 180.0));
    ST7735_CHECK_STATUS(st7735_draw_pixel(me, px, py, color));
  }
  return ST7735_OK;
}

st7735_status_t st7735_fill_rectangle(st7735_t *me, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (x0 >= ST7735_WIDTH || y0 >= ST7735_HEIGHT || 
      x1 >= ST7735_WIDTH || y1 >= ST7735_HEIGHT ||
      x1 < x0 || y1 < y0) 
  {
    return ST7735_PARAM_ERROR;
  }

  ST7735_CHECK_STATUS(st7735_set_pos(me, x0, y0, x1, y1));

  ST7735_CHECK_STATUS(st7735_write_cmd(me, ST7735_MEMORY_WRITE));
  for(uint16_t i = 0; i < (x1 - x0 + 1) * (y1 - y0 + 1); i++)
  {
    ST7735_CHECK_STATUS(st7735_write_data(me, color & 0xFF));
    ST7735_CHECK_STATUS(st7735_write_data(me, color >> 8));
  }
  return ST7735_OK;
}

st7735_status_t st7735_fill_rhombus(st7735_t *me, uint8_t x, uint8_t y, uint8_t d, uint16_t color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (d == 0 || (d % 2) != 0)
    return ST7735_PARAM_ERROR;

  uint8_t half_d = d / 2;

  if (x < half_d || x + half_d >= ST7735_WIDTH || 
      y < half_d || y + half_d >= ST7735_HEIGHT) 
  {
    return ST7735_PARAM_ERROR;
  }

  for (uint8_t i = 0; i <= half_d; i++) {
    ST7735_CHECK_STATUS(st7735_fill_rectangle(me, x - i, y - (half_d - i), x + i, y - (half_d - i), color));
    ST7735_CHECK_STATUS(st7735_fill_rectangle(me, x - i, y + (half_d - i), x + i, y + (half_d - i), color));
  }
  return ST7735_OK;
}

st7735_status_t st7735_draw_string_center(st7735_t *me, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor)
{
  if (!str || !me) 
    return ST7735_PARAM_ERROR;
  
  uint16_t str_len = strlen(str);
  uint16_t pixel_width = str_len * font.width;

  if (pixel_width > ST7735_WIDTH) 
    return ST7735_PARAM_ERROR;
  uint8_t x = (ST7735_WIDTH - pixel_width) / 2;

  return st7735_draw_string(me, x, y, str, font, color, bgcolor);
}

st7735_status_t st7735_draw_password_mask(st7735_t *me, uint8_t entered_digits, uint8_t total_digits, uint8_t y, uint16_t active_color, uint16_t inactive_color)
{
  if (me == NULL) 
    return ST7735_PARAM_ERROR;
  if (entered_digits > total_digits || total_digits == 0 || total_digits > 10) 
    return ST7735_PARAM_ERROR;

  uint8_t rhombus_d = 8;
  uint8_t spacing = 4;
  uint8_t total_mask_width = total_digits * rhombus_d + (total_digits - 1) * spacing;
  uint8_t start_x = (ST7735_WIDTH - total_mask_width) / 2;
  uint8_t current_x_center;

  for (uint8_t i = 0; i < total_digits; i++)
  {
    current_x_center = start_x + (rhombus_d / 2) + (i * (rhombus_d + spacing));
    if (i < entered_digits)
    {
      ST7735_CHECK_STATUS(st7735_fill_rhombus(me, current_x_center, y, rhombus_d, active_color));
    }
    else
    {
      ST7735_CHECK_STATUS(st7735_draw_rhombus(me, current_x_center, y, rhombus_d, inactive_color));
    }
  }
  
  return ST7735_OK;
}