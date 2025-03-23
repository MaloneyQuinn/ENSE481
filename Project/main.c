/**
 * @file main.c
 * @brief Handles main logic and control loop for the project.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"
#include "usart.h"

int main(void)
{
	usart_setup();
	int temp = 0;
	usart_put('h');
	usart_put('i');
	while(1)
	{
		temp = usart_get();
		usart_put(temp);
	}
}
