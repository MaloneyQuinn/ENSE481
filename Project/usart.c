/**
 * @file usart.c
 * @brief Handles usart related functions.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"
#include "usart.h"

/**
 * @brief Doesn't do much right now.
 */
void usart_setup(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
}
