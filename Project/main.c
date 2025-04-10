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
#include "stdbool.h"
#include "usart.h"
#include "pwm.h"
#include "adc.h"
#include "systick.h"
#include "pid.h"
void time_delay(int time);
void SysTick_Handler(void);

static char BUFFER[20] = "";
static int CLI_COUNTER = 0;
static uint32_t CURRENT_PULSE;
static int CURRENT_ADC;
static bool SELF_BALANCING = false;

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
	pid controller;
	pid_init(&controller);
	while(1)
	{
		CURRENT_PULSE = TIM4->CCR2;
		CURRENT_ADC = (int)ADC1->DR;
		if(SELF_BALANCING == true)
			CURRENT_PULSE = (uint32_t)pid_update(&controller, SETPOINT, CURRENT_ADC);
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
	cli_update(CURRENT_PULSE, CURRENT_ADC);
	SysTick->VAL = 0;
	
}

void USART2_IRQHandler(void) 
{
  volatile unsigned int IIR;
    IIR = USART2->SR;
    if (IIR & USART_SR_RXNE)
		{
      USART2->SR &= ~USART_SR_RXNE;
			int cli_result = cli_receive(BUFFER, CLI_COUNTER);
			switch (cli_result)
		{
			case REMOVE_CHARACTER:
				CLI_COUNTER--;
				break;
			
			case DO_NOTHING:
				break;
			
			case ADD_CHARACTER:
				CLI_COUNTER++;
				break;
			
			case CLI_ERROR:
				usart_print("error, invalid input. enter 'help' for a list of commands");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				CLI_COUNTER = 0;
				break;
			
			case GET_VERSION:
				usart_print(PROGRAM_VERSION);
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				CLI_COUNTER = 0;
				break;
			
			case GET_HELP:
				usart_print("-v: shows program version, [ and ] change duty cycle (lower and raise)");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				CLI_COUNTER = 0;
				break;
			
			case DECREASE_DUTY:
				change_duty(-10);
				break;
			
			case INCREASE_DUTY:
				change_duty(10);
				break;
			
			case START_SELF_BALANCING:
				if(SELF_BALANCING == false)
				{
					usart_print("Self balancing commencing.");
					SELF_BALANCING = true;
				}
				else
					usart_print("Already self balancing.");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				CLI_COUNTER = 0;
				break;
				
			case STOP_SELF_BALANCING:
				if(SELF_BALANCING == true)
				{
					usart_print("Self balancing stopped.");
					SELF_BALANCING = false;
				}
				else
					usart_print("Not currently self balancing.");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				CLI_COUNTER = 0;
				break;
		}
		}
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
