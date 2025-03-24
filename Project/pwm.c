
#include "pwm.h"

void timer_setup()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	// bit 3: IOPBEN=1, enable GPIOB clock
    
	GPIOB->CRL = 0xB4444444;

	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->CR1 = 0;
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	TIM4->CCER |=TIM_CCER_CC2E;
	
	TIM4->PSC = 72;
	TIM4->ARR = 20000;
	TIM4->CCR2 = 1500;
	
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->CR1 |= TIM_CR1_CEN;
}

void change_duty()
{
	TIM4->CR1 |= TIM_CR1_URS;
}
