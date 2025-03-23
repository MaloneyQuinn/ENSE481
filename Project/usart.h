/**
 * @file usart.h
 * @brief Header for usart related functions.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"

void usart_setup(void);
int usart_get(void);
void usart_put(int val);
