#ifndef __EXTI_H
#define __EXTI_H

#include "hal_type.h"
#include "hal_afio.h"
#include "hal_gpio.h"

#define EXTI_RISING_MODE   0X00
#define EXTI_FALLING_MODE  0x01
#define EXTI_BOTH_MODE     0x02

#define NVIC_ISER0      *((uint32_t*)(0xE000E100))
#define NVIC_ISER1      *((uint32_t*)(0xE000E104))
typedef struct
{
  __32BIT IMR;
  __32BIT EMR;
  __32BIT RTSR;
  __32BIT FTSR;
  __32BIT SWIER;
  __32BIT PR;
} exti_t;

#define EXTI ((volatile exti_t*)(0x40010400UL))

void EXTI0_Init(void);
void EXTI0_IRQHandler(void);
uint8_t get_Pin_Number(uint16_t gpio_pin);

void EXTI_Init(uint16_t pin, volatile gpio_t *port, uint8_t type);

#endif
