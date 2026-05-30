#ifndef __BSP_ST7735_H
#define __BSP_ST7735_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver_st7735.h" 

#define BSP_VERSION_1

#ifdef BSP_VERSION_1
#define ST7735_GPIO_PORT                  GPIOB
#define ST7735_GPIO_PIN_CS                GPIO_PIN_0
#define ST7735_GPIO_PIN_A0                GPIO_PIN_1
#define ST7735_GPIO_PIN_RST               GPIO_PIN_10

#define ST7735_SPI_GPIO_PORT              GPIOA
#define ST7735_SPI_SCK_PIN                GPIO_PIN_5
#define ST7735_SPI_MISO_PIN               GPIO_PIN_6
#define ST7735_SPI_MOSI_PIN               GPIO_PIN_7

#define ST7735_HAL_SPI_PORT_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define ST7735_HAL_GPIO_PORT_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define ST7735_HAL_SPI_CLK_ENABLE()       __HAL_RCC_SPI1_CLK_ENABLE()

#define ST7735_HSPI                       hspi1
#define ST7735_HSPI_INSTANCE              SPI1
#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
#define ST7735_GPIO_PORT                  GPIOB
#define ST7735_GPIO_PIN_CS                GPIO_PIN_0
#define ST7735_GPIO_PIN_A0                GPIO_PIN_1
#define ST7735_GPIO_PIN_RST               GPIO_PIN_10

#define ST7735_SPI_GPIO_PORT              GPIOA
#define ST7735_SPI_SCK_PIN                GPIO_PIN_5
#define ST7735_SPI_MISO_PIN               GPIO_PIN_6
#define ST7735_SPI_MOSI_PIN               GPIO_PIN_7

#define ST7735_HAL_SPI_PORT_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define ST7735_HAL_GPIO_PORT_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define ST7735_HAL_SPI_CLK_ENABLE()       __HAL_RCC_SPI1_CLK_ENABLE()

#define ST7735_HSPI                       hspi1
#define ST7735_HSPI_INSTANCE              SPI1
#endif /* BSP_VERSION_2 */

#define BSP_ST7735_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->st7735_is_init || (handler)->status != ST7735_OK) { \
            return ST7735_NOT_INIT; \
        } \
        (handler)->status = ST7735_BUSY; \
    } while(0)

#define BSP_ST7735_CHECK_STATUS(handler, function) \
    do { \
           st7735_status_t status = (function); \
           (handler)->status = status; \
           return (status); \
    } while(0)

#define BSP_ST7735_INIT_CHECK(func_call) \
    do { \
        st7735_status_t _status = (func_call); \
        if (_status != ST7735_OK) { \
            return _status; \
        } \
    } while(0)

st7735_status_t bsp_st7735_gpio_init(void);
st7735_status_t bsp_st7735_spi_init(void);
st7735_status_t bsp_st7735_init(void);
st7735_status_t bsp_st7735_write_cmd(uint8_t cmd);
st7735_status_t bsp_st7735_write_data(uint8_t data);
st7735_status_t bsp_st7735_set_pos(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
st7735_status_t bsp_st7735_draw_pixel(uint8_t x, uint8_t y, uint16_t color);
st7735_status_t bsp_st7735_draw_char(uint8_t x, uint8_t y, char ch, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t bsp_st7735_draw_string(uint8_t x, uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t bsp_st7735_full_screen(uint16_t color);
st7735_status_t bsp_st7735_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
st7735_status_t bsp_st7735_draw_rhombus(uint8_t x, uint8_t y, uint8_t d, uint16_t color);
st7735_status_t bsp_st7735_draw_circle(uint8_t x, uint8_t y, uint8_t r, uint16_t color);
st7735_status_t bsp_st7735_fill_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
st7735_status_t bsp_st7735_fill_rhombus(uint8_t x, uint8_t y, uint8_t d, uint16_t color);
st7735_status_t bsp_st7735_draw_string_center(uint8_t y, char *str, font_t font, uint16_t color, uint16_t bgcolor);
st7735_status_t bsp_st7735_draw_password_mask(uint8_t entered_digits, uint8_t total_digits, uint8_t y, uint16_t active_color, uint16_t inactive_color);
st7735_status_t bsp_st7735_display();

#ifdef __cplusplus
}
#endif

#endif /* __BSP_ST7735_H */