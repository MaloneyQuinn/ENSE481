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
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	GPIOA->CRL = 0x44444B44;
	
	USART2->BRR = 0xEA6;
	USART2->CR1 |= (1<<3) | (1<<2);
	USART2->CR1 |= (1<<13);
}

int usart_get()
{
	while(!(USART2->SR & (1<<5)));
	return ((int) (USART2->DR & 0xFF));
}

void usart_put(int val)
{
	while(!(USART2->SR & (1<<7)));
	USART2->DR = (val & 0x00FF);
}
