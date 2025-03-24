/**
 * @file main.c
 * @brief Handles main logic and control loop for the project.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"
#include "usart.h"
#include "pwm.h"
#include "adc.h"

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
	ADC1->CR2 = 0x00000001; // readies ADC for another conversion
	while(1)
	{
		cli_result = cli_receive(buffer, cli_counter);
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
				usart_print("-v: shows program version.");
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
		cli_update(TIM4->CCR2, ADC1->DR);
		ADC1->CR2 = 0x00000001;
	}
}
