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
	char buffer[20];
	int cli_counter = 0;
	int cli_result;
	cli_update(TIM4->CCR2, ADC1->DR);
	ADC1->CR2 = 0x00000001;
	while(1)
	{
		/*cli_result = cli_receive(buffer, cli_counter);
		
		switch (cli_result)
		{
			case REMOVE_CHARACTER:
				cli_counter--;
				break;
			
			case DO_NOTHING:
				break;
			
			case ADD_CHARACTER:
				cli_counter++;
				break;
			
			case CLI_ERROR:
				usart_print("error, invalid input. enter 'help' for a list of commands");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				cli_counter = 0;
				break;
			
			case GET_VERSION:
				usart_print(PROGRAM_VERSION);
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				cli_counter = 0;
				break;
			
			case GET_HELP:
				usart_print("-v: shows program version, [ and ] change duty cycle (lower and raise)");
				usart_print("\n");
			  usart_print("\n");
				usart_print("\r");
			  usart_print(">> ");
				cli_counter = 0;
				break;
			
			case DECREASE_DUTY:
				change_duty(-100);
				break;
			
			case INCREASE_DUTY:
				change_duty(100);
				break;
		}
		*/
		//cli_update(TIM4->CCR2, ADC1->DR);
		ADC1->CR2 = 0x00000001;
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
