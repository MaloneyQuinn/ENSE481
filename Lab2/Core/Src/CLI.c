/*
 * CLI.c
 *
 *  Created on: Oct 7, 2024
 *      Author: qkmal
 */

#include "CLI.h"


void start_CLI()
{
	uint8_t uart_byte_buff[1];
	uint8_t word[20];
	char newLineMessage[] = "Enter a command: ";
	char error[] = "Error: not a valid command. Type 'help' to see commands";
	char help[] = "'test' runs a series of speed tests and prints the results, 'clock' shows the clock details of timer4.";
	int characterCounter = 0;
	char newLine = '\n';
	char cr = '\r';

	for(int x = 0; x < sizeof newLineMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);

	while (1)
	{
		HAL_UART_Receive(&huart2, uart_byte_buff, 1, 1000000);
		HAL_UART_Transmit(&huart2, (unsigned char *)&uart_byte_buff[0], 1, 100);
		if (uart_byte_buff[0] == 0x0D)
		{
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			if (word[0] == 't' && word[1] == 'e' && word[2] == 's' && word[3] == 't')
			{
				run_test();
				uart_byte_buff[0] = 0;
				characterCounter = 0;
			}

			else if (word[0] == 'c' && word[1] == 'l' && word[2] == 'o' && word[3] == 'c' && word[4] == 'k')
			{
				clock_info();
				uart_byte_buff[0] = 0;
				characterCounter = 0;
			}

			else if (word[0] == 'h' && word[1] == 'e' && word[2] == 'l' && word[3] == 'p')
			{

				uart_byte_buff[0] = 0;
				characterCounter = 0;
				for(int x = 0; x < sizeof help; x++)
					HAL_UART_Transmit(&huart2, (unsigned char *)&help[x], 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			}
			else
			{
				uart_byte_buff[0] = 0;
				characterCounter = 0;
				for(int x = 0; x < sizeof error; x++)
						HAL_UART_Transmit(&huart2, (unsigned char *)&error[x], 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			}
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			for(size_t i = 0; i < sizeof word; i++)
				word[i] = 0;
		}
		else if (uart_byte_buff[0] == 0x7F)
		{
			characterCounter --;
			word[characterCounter] = 0;
			uart_byte_buff[0] = 0;
		}
		else
		{
			word[characterCounter] = uart_byte_buff[0];
			uart_byte_buff[0] = 0;
			characterCounter++;
		}
	 }
}
