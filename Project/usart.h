/**
 * @file usart.h
 * @brief Header for usart related functions.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"

void usart_setup(void);
int usart_getch(void);
void usart_putch(int val);
