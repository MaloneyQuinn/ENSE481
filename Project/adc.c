

#include "adc.h"

void adc_setup()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_ADC1EN;
	ADC1->SQR3 |= 10;
	ADC1->CR2 = 0x1;
}
