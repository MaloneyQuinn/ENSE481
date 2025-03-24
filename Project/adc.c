/**@addtogroup Ball_Control
 * @{
 * @file adc.c
 * @brief Handles adc related functions.
 * @author Quinn Maloney
 */

#include "adc.h"

/**
 * @brief Initializes ADC1 for conversion usage.
 * @details Enables APB2ENR on GPIOB and ADC1. sets the channel to
 * channel 10 which is attached to the IR sensor. Readies the conversion
 * bit for the next conversion.
 */
void adc_setup()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_ADC1EN;
	ADC1->SQR3 |= 10;
	ADC1->CR2 = 0x1;
}
/** @} */
