/**@addtogroup Ball_Control
 * this group is responsible for the hardware elements used to control the ping pong
 * ball. This includes the servo as well as the IR sensor.
 * @{
 * @file pwm.c
 * @brief Handles pwm related functions.
 * @author Quinn Maloney
 */
 
#include "pwm.h"
#include "constants.h"

/**
 * @brief Initializes TIMER4 for pwm usage.
 * @details Enables APB2ENR on GPIOB and APB1ENR on TIMER4, sets PB7
 * to be an alternate function output, as well as set up TIM4 values.
 * PSC set to 71 and ARR set to 20000 making the output 50Hz. (explained in
 * pwm_calculations.txt in documentation on github. TIM4->CCR2 set to
 * 1500 initially (center point). Used to set up PWM to be used.
 */
void pwm_setup()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
	GPIOB->CRL = 0xB4444444;

	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->CR1 = 0;
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
	TIM4->CCER |=TIM_CCER_CC2E;
	
	TIM4->PSC = 71;
	TIM4->ARR = 20000;
	TIM4->CCR2 = MIN_DUTY;
	
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Changes duty cycle of TIMER4 Ch 2.
 * @details Takes a value (int) and adds it to the TIM4->CCR2
 * register. If this value is < MIN_DUTY or > MAX_DUTY it will not
 * change the duty cycle. Otherwise TIM4->CCR2 = this new value.
 * used to change duty cycle.
 * @param change (int) a positive or negative value to increment/
 * decrement the duty cycle of TIM4->CCR2.
 */
void change_duty(int change)
{
	uint16_t new_duty = TIM4->CCR2 + change;
	
	if(new_duty > MAX_DUTY)
		TIM4->CCR2 = MAX_DUTY;
	else if(new_duty < MIN_DUTY)
		TIM4->CCR2 = MIN_DUTY;
	else
		TIM4->CCR2 = new_duty;
}
/** @} */
