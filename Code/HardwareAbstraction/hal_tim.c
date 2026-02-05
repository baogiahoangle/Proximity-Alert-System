#include "hal_tim.h"
#include "hal_exti.h"

uint8_t blink_status = 0;

void tim2_init_it(void)
{
  TIM2_PSC = 7999; 
  TIM2_ARR = 999;
  TIM2_DIER |= (1 << 0);
  TIM2_CR1 |= (1 << 0);
  NVIC_ISER0 |= (1 << 28); 
}

void TIM2_IRQHandler(void)
{
  if (TIM2_SR & 0x01)
  {
    if (blink_status == 1)
    {
      blink_status = 0;
    }
    else
    {
      blink_status = 1;
    }
    TIM2_SR &= ~(uint32_t)(1 << 0);
  }
}

void delay_ms(uint32_t ms)
{
  TIM3_PSC = 7999; 
  TIM3_ARR = ms;
  TIM3_CNT = 0;
  TIM3_CR1 |= (1 << 0);
  while(TIM3_CNT < ms);
  TIM3_CR1 &= ~(uint32_t)(1 << 0);
  TIM3_CNT = 0;
}
