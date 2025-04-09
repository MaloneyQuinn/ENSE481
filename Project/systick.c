

#include "systick.h"
#include "constants.h"

void systick_setup(void)
{
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->LOAD = 0x895440;
	SysTick-> CTRL = 0x3;
	NVIC_EnableIRQ(SysTick_IRQn);
}
