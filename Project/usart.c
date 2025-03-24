/**
 * @file usart.c
 * @brief Handles usart related functions.
 * @author Quinn Maloney
 */
 
#include "usart.h"

/**
 * @brief Doesn't do much right now.
 */
void usart_setup(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	GPIOA->CRL = 0x44444B44;
	
	USART2->BRR = 0xEA6;
	USART2->CR1 |= (1<<3) | (1<<2);
	USART2->CR1 |= (1<<13);
}

uint16_t usart_get()
{
	while(!(USART2->SR & (1<<5)));
	return ((uint16_t) (USART2->DR & 0xFF));
}

void usart_put(uint16_t val)
{
	while(!(USART2->SR & (1<<7)));
	USART2->DR = (val);
}

int get_size(char word[])
{
    int count = 0;
    while (*(word + count) != '\0')
        ++count;
    return count;
}

void clear_array(char word[])
{
	for(int i = 0; i < get_size(word); i++)
		word[i] = 0;
}

void usart_print(char word[])
{
	int size = get_size(word);
	for(uint16_t i= 0; i < size; i++)
		usart_put(word[i]);
}

void cli_setup()
{
	char move_cursor[] = "\x1b[5;0H";
	char scroll_box[] = "\x1b[5;r";
	
	usart_print(scroll_box);
	usart_print(move_cursor);
	
	char command_message[] = ">> ";
	usart_print(command_message);
}

void cli_update(int duty_cycle, int adc_reading)
{
	char newline[] = "\n";
	char cr[] = "\r";
	char move_cursor_top[] = "\x1b[H";
	char save_cursor[] = "\x1b[s";
	char restore_cursor[] = "\x1b[u";
	char erase_line[] = "\x1b[2K";
	char duty_message[] = "Duty Cycle: ";
	char char_duty_cycle[3];
	
	usart_print(save_cursor);
	usart_print(move_cursor_top);
	usart_print(erase_line);
	
	usart_print(duty_message);
	sprintf(char_duty_cycle, "%d", duty_cycle);
	usart_print(char_duty_cycle);
	usart_print(newline);
	usart_print(cr);
	usart_print(erase_line);
	
	char analog_message[] = "IR sensor: ";
	usart_print(analog_message);
	char char_adc_reading[4];
	sprintf(char_adc_reading, "%d", adc_reading);
	usart_print(char_adc_reading);
	
	usart_print(restore_cursor);
}

int cli_receive(char buffer[], int counter)
{
	uint16_t input = usart_get();
	
	if (input == 0x0D)
	{
		if (buffer[0] == '-' && buffer[1] == 'v')
		{
			clear_array(buffer);
			usart_print("\n");
			usart_print("\r");
			return GET_VERSION;
		}
		
		else if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l' && buffer[3] == 'p')
		{
			clear_array(buffer);
			usart_print("\n");
			usart_print("\r");
			return GET_HELP;
		}
		else
		{
			clear_array(buffer);
			usart_print("\n");
			usart_print("\r");
			return CLI_ERROR;
		}
	}
	else if (input == 0x7F)
	{
		if (counter > 0)
		{
			buffer[counter] = 0;
			usart_put(input);
			return REMOVE_CHARACTER;
		}
		else
			return DO_NOTHING;
	}
	else if (input == 0x5B)
			return DECREASE_DUTY;
	
	else if (input == 0x5D)
		return INCREASE_DUTY;
	
	else
	{
		usart_put(input);
		buffer[counter] = input;
		return ADD_CHARACTER;
	}
}
