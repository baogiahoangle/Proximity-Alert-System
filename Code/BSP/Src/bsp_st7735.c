#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_st7735.h"

#define ST7735_HSPI                       hspi1
#define ST7735_HSPI_INSTANCE              SPI1

static st7735_t st7735_device = 
{
  .port = NULL,
  .pin_cs = 0,
  .pin_a0 = 0,
  .pin_reset = 0,
  .hspi = NULL,
};

static st7735_handler_t st7735_bsp_handler = 
{
  .st7735 = &st7735_device,
  .st7735_is_init = false,
  .status = ST7735_ERROR,
};

st7735_status_t bsp_st7735_gpio_init(void)
{
  ST7735_HAL_SPI_PORT_CLK_ENABLE();
  ST7735_HAL_GPIO_PORT_CLK_ENABLE();

  gpio_config(ST7735_GPIO_PORT, ST7735_GPIO_PIN_CS, GPIO_MODE_OUTPUT_PP);
  gpio_config(ST7735_GPIO_PORT, ST7735_GPIO_PIN_A0, GPIO_MODE_OUTPUT_PP);
  gpio_config(ST7735_GPIO_PORT, ST7735_GPIO_PIN_RST, GPIO_MODE_OUTPUT_PP);

  return ST7735_OK;
}

st7735_status_t bsp_st7735_spi_init(void)
{
  ST7735_HAL_SPI_CLK_ENABLE();
  ST7735_HAL_SPI_PORT_CLK_ENABLE();

  spi1_init_master();
  return ST7735_OK;
}

st7735_status_t bsp_st7735_init(void)
{
  BSP_ST7735_INIT_CHECK(bsp_st7735_gpio_init());
  BSP_ST7735_INIT_CHECK(bsp_st7735_spi_init());

  st7735_bsp_handler.st7735->port = ST7735_GPIO_PORT;
  st7735_bsp_handler.st7735->pin_cs = ST7735_GPIO_PIN_CS;
  st7735_bsp_handler.st7735->pin_a0 = ST7735_GPIO_PIN_A0;
  st7735_bsp_handler.st7735->pin_reset = ST7735_GPIO_PIN_RST;
  st7735_bsp_handler.st7735->hspi = ST7735_HSPI;

  st7735_status_t status = st7735_init(st7735_bsp_handler.st7735);
  if (status == ST7735_OK)
  {
    st7735_bsp_handler.st7735_is_init = true;
    st7735_bsp_handler.status = ST7735_OK;
  }
  else
  {
    st7735_bsp_handler.st7735_is_init = false;
    st7735_bsp_handler.status = status;
  }

  return status;
}

st7735_status_t bsp_st7735_write_cmd(uint8_t cmd)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_write_cmd(st7735_bsp_handler.st7735, cmd));
}

st7735_status_t bsp_st7735_write_data(uint8_t data)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_write_data(st7735_bsp_handler.st7735, data));
}

st7735_status_t bsp_st7735_set_pos(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_set_pos(st7735_bsp_handler.st7735, x0, y0, x1, y1));
}

st7735_status_t bsp_st7735_draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_pixel(st7735_bsp_handler.st7735, x, y, color));
}

st7735_status_t bsp_st7735_draw_char(uint8_t x, uint8_t y, char ch, font_t font, uint16_t color, uint16_t bgcolor)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_char(st7735_bsp_handler.st7735, x, y, ch, font, color, bgcolor));
}

st7735_status_t bsp_st7735_draw_string(uint8_t x, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_string(st7735_bsp_handler.st7735, x, y, str, font, color, bgcolor));
}

st7735_status_t bsp_st7735_full_screen(uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_full_screen(st7735_bsp_handler.st7735, color));
}

st7735_status_t bsp_st7735_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_rectangle(st7735_bsp_handler.st7735, x0, y0, x1, y1, color));
}

st7735_status_t bsp_st7735_draw_rhombus(uint8_t x, uint8_t y, uint8_t d, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_rhombus(st7735_bsp_handler.st7735, x, y, d, color));
}

st7735_status_t bsp_st7735_draw_circle(uint8_t x, uint8_t y, uint8_t r, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_circle(st7735_bsp_handler.st7735, x, y, r, color));
}

st7735_status_t bsp_st7735_fill_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_fill_rectangle(st7735_bsp_handler.st7735, x0, y0, x1, y1, color));
}

st7735_status_t bsp_st7735_fill_rhombus(uint8_t x, uint8_t y, uint8_t d, uint16_t color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_fill_rhombus(st7735_bsp_handler.st7735, x, y, d, color));
}

st7735_status_t bsp_st7735_draw_string_center(uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_string_center(st7735_bsp_handler.st7735, y, str, font, color, bgcolor));
}

st7735_status_t bsp_st7735_draw_password_mask(uint8_t entered_digits, uint8_t total_digits, uint8_t y, uint16_t active_color, uint16_t inactive_color)
{
  BSP_ST7735_CHECK_HANDLER_INIT(&st7735_bsp_handler);
  BSP_ST7735_CHECK_STATUS(&st7735_bsp_handler, st7735_draw_password_mask(st7735_bsp_handler.st7735, entered_digits, total_digits, y, active_color, inactive_color));
}

#ifdef __cplusplus
}
#endif