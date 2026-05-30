#include "hal_exti.h"

void EXTI0_Init(void)
{
  // IRQs
  AFIO->EXTICR1.REG &= ~(uint32_t)(0xF << 0); // Clear bits
  EXTI->IMR.BITS.BIT0 = 1;
  EXTI->RTSR.BITS.BIT0 = 1;
  EXTI->FTSR.BITS.BIT0 = 0;
  
  NVIC_ISER0 |= (1 << 6);
}

void EXTI0_IRQHandler(void)
{
  // Interrupt exists
  if (EXTI->PR.BITS.BIT0)
  {
    EXTI->PR.REG |= (uint32_t)(1<< 0);
  }
}

uint8_t get_Pin_Number(uint16_t gpio_pin)
{
  for(uint8_t i = 0; i < 16; i++)
  {
    if (gpio_pin & (1 << i))
    {
      return i;
    }
  }
  return 0xFF;
}

void EXTI_Init(uint16_t gpio_pin, volatile gpio_t *port, uint8_t type)
{
  uint8_t port_code;
  uint8_t pin; 
  if (port == GPIOA)
  {
    port_code = 0;
  }
  else if (port == GPIOB)
  {
    port_code = 1;
  }
  else if (port == GPIOC)
  {
    port_code = 2;
  }
  else
  {
    return;
  }
  pin = get_Pin_Number(gpio_pin);
  uint32_t shift = (pin % 4) * 4;
  if (pin < 4)
  {
    AFIO->EXTICR1.REG &= (uint32_t)~(0xF << shift);
    AFIO->EXTICR1.REG |= (uint32_t)(port_code << shift);
  } 
  else if (pin < 8)
  {
    AFIO->EXTICR2.REG &= (uint32_t)~(0xF << shift);
    AFIO->EXTICR2.REG |= (uint32_t)(port_code << shift);
  }
  else if (pin < 12)
  {
    AFIO->EXTICR3.REG &= (uint32_t)~(0xF << shift);
    AFIO->EXTICR3.REG |= (uint32_t)(port_code << shift);
  }
  else
  {
    AFIO->EXTICR4.REG &= (uint32_t)~(0xF << shift);
    AFIO->EXTICR4.REG |= (uint32_t)(port_code << shift);
  }
  
  EXTI->IMR.REG |= (1 << pin);
  
  if (type == EXTI_RISING_MODE)
  {
    EXTI->RTSR.REG |= (1 << pin);
    EXTI->FTSR.REG &= ~(1 << pin);
  }
  else if (type == EXTI_FALLING_MODE)
  {
    EXTI->RTSR.REG &= ~(1 << pin);
    EXTI->FTSR.REG |= (1 << pin);
  }
  else
  {
    EXTI->RTSR.REG |= (1 << pin);
    EXTI->FTSR.REG |= (1 << pin);
  }
  
  if (pin <= 4)
  {
    NVIC_ISER0 |= (1 << (6 + pin));
  }
  else if (pin <= 9)
  {
    NVIC_ISER0 |= (1 << 23);
  }
  else if (pin <= 15)
  {
    NVIC_ISER1 |= (1 << 8);
  }
}
