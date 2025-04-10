/**@addtogroup CLI_Control
 * @{
 * @file systick.c
 * @brief Contains SysTick startup configuration.
 * @author Quinn Maloney
 */

#include "systick.h"
#include "constants.h"

/**
 * @brief Initializes SysTick for interrupt use.
 * @details enables SysTick in interrupt mode currently
 * causing an interrupt about 1 time per second.
 */
void systick_setup(void)
{
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->LOAD = 0x895440;
	SysTick-> CTRL = 0x3;
	NVIC_EnableIRQ(SysTick_IRQn);
}
/** @} */
