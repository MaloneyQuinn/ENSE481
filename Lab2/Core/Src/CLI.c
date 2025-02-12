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
	int isLED = 0;
	char newLineMessage[] = "Enter a command: ";
	char error[] = "Error: not a valid command. Type 'help' to see commands";
	char help[] = "'test' runs a series of speed tests and prints the results.";
	char status[] = "The LED is: ";
	char isOn[] = "on";
	char isOff[] = "off";
	int counter = 0;
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
				isLED = 1;
				uart_byte_buff[0] = 0;
				counter = 0;
			}

			else if (word[0] == 'o' && word[1] == 'f' && word[2] == 'f')
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				isLED = 0;
				uart_byte_buff[0] = 0;
				counter = 0;
			}
			else if (word[0] == 's' && word[1] == 't' && word[2] == 'a' && word[3] == 't' && word[4] == 'u' && word[5] == 's')
			{

				uart_byte_buff[0] = 0;
				counter = 0;
				for(int x = 0; x < sizeof status; x++)
						HAL_UART_Transmit(&huart2, (unsigned char *)&status[x], 1, 100);
				if (isLED == 1)
				{
					for(int x = 0; x < sizeof isOn; x++)
						HAL_UART_Transmit(&huart2, (unsigned char *)&isOn[x], 1, 100);
				}
				else
				{
					for(int x = 0; x < sizeof isOff; x++)
						HAL_UART_Transmit(&huart2, (unsigned char *)&isOff[x], 1, 100);
				}
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			}
			else if (word[0] == 'h' && word[1] == 'e' && word[2] == 'l' && word[3] == 'p')
			{

				uart_byte_buff[0] = 0;
				counter = 0;
				for(int x = 0; x < sizeof help; x++)
					HAL_UART_Transmit(&huart2, (unsigned char *)&help[x], 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
				HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			}
			else
			{
				uart_byte_buff[0] = 0;
				counter = 0;
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
			counter --;
			word[counter] = 0;
			uart_byte_buff[0] = 0;
		}
		else
		{
			word[counter] = uart_byte_buff[0];
			uart_byte_buff[0] = 0;
			counter++;
		}
	 }
}
