/**@addtogroup CLI_Control
 * @{
 * @file usart.h
 * @brief Header for usart related functions.
 * @author Quinn Maloney
 */
 
#include "stm32f10x.h"
#include "constants.h"
#include <stdio.h>

void usart_setup(void);
uint16_t usart_get(void);
void usart_put(uint16_t val);
int get_size(char word[]);
void clear_array(char word[]);
void usart_print(char word[]);
void cli_setup(void);
void cli_update(uint32_t duty_cycle, uint32_t adc_reading);
int cli_receive(void);
void USART2_IRQHandler(void) ;
/** @} */
