/**@addtogroup CLI_Control
 * this group is responsible for CLI related ouput as well as USART 
 * initialization
 * @{
 * @file usart.c
 * @brief Handles usart related functions.
 * @author Quinn Maloney
 */
 
#include "usart.h"

/**
 * @brief Initializes USART2 to be used for CLI.
 * @details Sets PA2 to floating input and PA3 to alternate drain output,
 * enables clock for both GPIOA and USART2. Used for setup/initialization.
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

/**
 * @brief Receives a single character from COM.
 * @details Gets the data from the USART2->DR and returns it. used for getting
 * the user's input from a command terminal.
 * @return (uint16_t) The ascii value of the received character.
 */
uint16_t usart_get()
{
	while(!(USART2->SR & (1<<5)));
	return ((uint16_t) (USART2->DR & 0xFF));
}

/**
 * @brief Sends a single character from COM.
 * @details places the data intro USART2->DR so it will be sent. Used for sending
 * data to the user via command terminal.
 * @param val (uint16_t) is the character sent to the terminal.
 */
void usart_put(uint16_t val)
{
	while(!(USART2->SR & (1<<7)));
	USART2->DR = (val);
}

/**
 * @brief Returns size of a char array.
 * @details iterates through a char array to find its true size as sizof()
 * returns the size of the pointer. Used for transmitting all characters in a
 * char array as size is a required value.
 * @param word[] (char array) is the array we want the size of.
 * @return count (int) the count iterates as it steps through the array. The
 * final value is that of the length of the array.
 */
int get_size(char word[])
{
    int count = 0;
    while (*(word + count) != '\0')
        ++count;
    return count;
}

/**
 * @brief Clears all values in the passed char array.
 * @details iterates through a char array and clears all values. Used to clear 
 * the input buffer from the command terminal.
 * @param word (char array) is the array we want to clear.
 */
void clear_array(char word[])
{
	for(int i = 0; i < get_size(word); i++)
		word[i] = 0;
}

/**
 * @brief Prints the values of a char array to the command terminal.
 * @details Gets the size of the array with get_size() and iterates
 * through the array and prints to the terminal using usart_put() for
 * each character.
 * @param word (char array) is the array we want to print.
 */
void usart_print(char word[])
{
	int size = get_size(word);
	for(uint16_t i= 0; i < size; i++)
		usart_put(word[i]);
}

/**
 * @brief Sets up the terminal output for the first time.
 * @details Uses usart_print() to move the cursor and create a scroll
 * box for the users input. Called once at the beginning of the main().
 */
void cli_setup()
{
	char move_cursor[] = "\x1b[5;0H";
	char scroll_box[] = "\x1b[5;r";
	
	usart_print(scroll_box);
	usart_print(move_cursor);
	
	char command_message[] = ">> ";
	usart_print(command_message);
}

/**
 * @brief Updates the data section of the CLI interface.
 * @details Uses usart_print() to move the cursor and print updated values
 * for the duty cyle of the servo as well as the analog reading of the IR
 * sensor. It then restores the cursor to where the user last had it.
 * @param duty_cycle (int) the value of the duty cycle from Timer4 Ch2 used 
 * for the servo. Measured in micro-seconds.
 * @param adc_reading (int) the value of the adc1 data register attached to
 * the IR sensor. Takes the voltage and converts to a binary number.
 */
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

/**
 * @brief Logic for user input.
 * @details uses usart_get() to get user input and compares what was entered.
 * Special cases are: Enter-> submits the buffer[] object and determines
 * what was entered, Backspace-> removes last input from buffer, [ and ]->
 * [ decreases pwm duty cycle and ] increaes it.
 * @param buffer (char array) keeps track of what the user has currently entered
 * in the terminal.
 * @param counter (int) keeps track of how many characters are in the buffer. if there
 * are 0 nothing should be erased on a backspace.
 * @return cli_return (enum) defined in constants.h an enum is used for the variable 
 * options that can be returned.
 */
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
/** @} */
