/**
 * @file main.c
 * @brief Handles main logic and control loop for the project.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"
#include "usart.h"
#include "pwm.h"

int main(void)
{
	usart_setup();
	cli_init();
	timer_setup();
	char buffer[20];
	int cli_counter = 0;
	int cli_result;
	cli_update(752, 20);
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
		}
		
	}
}
