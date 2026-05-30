#include "hal_spi.h"

void spi1_init_master(void)
{
  gpio_config(PORT_SCK, PIN_SCK, GPIO_MODE_AF_PP);
  gpio_config(PORT_MOSI, PIN_MOSI, GPIO_MODE_AF_PP);
  gpio_config(PORT_MISO, PIN_MISO, GPIO_MODE_INPUT_FLOATING);
  gpio_config(PORT_CS, PIN_CS, GPIO_MODE_OUTPUT_PP);
  
  SPI1_CR1 = 0x0000;
  SPI1_CR1 |= (1 << 2); //Master 
  SPI1_CR1 |= (0x05 << 3); // Baud rate control 
  SPI1_CR1 |= (1 << 9); // Software slave management
  SPI1_CR1 |= (1 << 8); // Internal slave selected 
  SPI1_CR1 |= (1 << 6); // Enable SPI 
  
  gpio_write_pin(PORT_CS, PIN_CS, GPIO_STATE_SET);
}

void spi1_send(uint8_t data)
{
  gpio_write_pin(PORT_CS, PIN_CS, GPIO_STATE_RESET);
  while(!(SPI1_SR & (1 << 1))){}
  SPI1_DR = data;
  while(!(SPI1_SR & (1 << 0))){}
  uint32_t check_data_receive = SPI1_DR;
  while((SPI1_SR & (1 << 7))){}
  gpio_write_pin(PORT_CS, PIN_CS, GPIO_STATE_SET);
}
