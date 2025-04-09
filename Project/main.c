/**
 * @file main.c
 * @brief Handles main logic and control loop for the project.
 * @author Quinn Maloney
 * @version 1.0.0 March 25, 2025 Milestone Build
 * @detailed This is the main control file for this project.
 * it contains the main while(1){} loop which at the current
 * build gets input and updates the hardware values to display them
 * to the terminal.
 */
 
#include "stm32f10x.h"
#include "usart.h"
#include "pwm.h"
#include "adc.h"
#include "systick.h"
void time_delay(int time);
void SysTick_Handler(void);

static uint32_t current_pulse;
static uint32_t current_adc;

/**
 * @brief Main control function for the program.
 * @details calls initialization functions and runs logic for the
 * program including a switch statement to handle input from the terminal.
 */
int main(void)
{
	usart_setup();
	cli_setup();
	pwm_setup();
	adc_setup();
	systick_setup();
	ADC1->CR2 = 0x00000001;
	while(1)
	{
		current_pulse = TIM4->CCR2;
		current_adc = ADC1->DR;
		time_delay(500000);
		time_delay(500000);
		time_delay(500000);
		ADC1->CR2 = 0x00000001;
	}
}

void time_delay(int time)
{
	for(volatile int i = 0; i < time; i++);
}

void SysTick_Handler(void)
{
	cli_update(current_pulse, current_adc);
	SysTick->VAL = 0;
	
}
 /*! \mainpage Ball Height Controller
 *
 * \section intro_sec Description
 *
 * This is the documentation for the ENSE481 Ball Heigh Controller Project.<br>
 * This project utilizes a fan to move a ping pong ball inside a tube.<br> It uses a servo
 * to change airflow in the tube to balance the ping pong ball <br>in different locations. It uses
 * an IR sensor to get location info of the ping pong ball.
 *
 * \section install_sec Additional Information
 *
 * Author:     Quinn Maloney<br>
 * SID:        200431628<br>
 * Professor:  Dr. Karim Naqvi<br>
 * Version:    1.0.0 March 25, 2025 Milestone Build
 */
