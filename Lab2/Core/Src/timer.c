/*
 * timer.c
 *
 *  Created on: Nov 6, 2024
 *      Author: qkmal
 */

#include "timer.h"

int16_t timer_start()
{
	HAL_TIM_Base_Start(&htim4);
	return __HAL_TIM_GET_COUNTER(&htim4);
}

uint16_t timer_stop(uint16_t initial)
{
	volatile uint16_t end = __HAL_TIM_GET_COUNTER(&htim4);
	HAL_TIM_Base_Stop(&htim4);
	volatile uint16_t result = initial - end;
	return result;
}

int32_t random_32bit()
{
	int32_t value;
	do
	{
		value = rand();
	} while(value == 0);
	return value;
}

int64_t random_64bit()
{
	int64_t value;
	do
	{
		value = rand();
	} while(value == 0);
	return value;
}

char random_byte()
{
	char value;
	value = rand;
	return value;
}

void clock_info()
{
	char newLine = '\n';
	char cr = '\r';
	char clockPrescalerText[] = "Prescaler Higher number indicates lower clock speed: ";
	char clockCounterText[] = "CounterMode Indicates either counting up or down: ";
	char clockPeriodText[] = "Period Shows the period of the counter (value it will count to/from): ";
	char clockArray[5] = "";

	for(int x = 0; x < sizeof clockPrescalerText; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockPrescalerText[x], 1, 100);
	sprintf (clockArray, "%d", htim4.Init.Prescaler);
	for(int x = 0; x < sizeof clockArray; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockArray[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	for(int x = 0; x < sizeof clockCounterText; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockCounterText[x], 1, 100);
	sprintf (clockArray, "%d", htim4.Init.CounterMode);
	for(int x = 0; x < sizeof clockArray; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockArray[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	for(int x = 0; x < sizeof clockPeriodText; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockPeriodText[x], 1, 100);
	sprintf (clockArray, "%d", htim4.Init.Period);
	for(int x = 0; x < sizeof clockArray; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&clockArray[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

}

void run_test()
{
	//display messages
	srand(4345);
	char int32bit[] = "two random 32-bit integers: ";
	char int64bit[] = "two random 64-bit integers: ";
	char struct8byte[] = "8-byte struct using the assignment operator: ";
	char struct128byte[] = "128-byte struct using the assignment operator: ";
	char struct1024byte[] = "1024-byte struct using the assignment operator: ";
	char addMessage[] = "Add ";
	char multMessage[] = "Multiply ";
	char divMessage[] = "Divide ";
	char assignMessage[] = "copy a ";
	char newLine = '\n';
	char cr = '\r';
	char ticks[] = " clock ticks.";

	// add 2 32 bit ints
	volatile uint32_t value1;
	volatile uint32_t value2;
	volatile uint16_t timerInitial = 0;
	volatile uint16_t timerFinal = 0;
	uint16_t results[100];
	uint32_t average = 0;
	char charAverage[3];
	char structCharAverage[4];

	for(int i = 0; i < 100; i++)
	{
		value1 = random_32bit();
		value2 = random_32bit();
		timerInitial = timer_start();
		value1 = value1 + value2;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof addMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&addMessage[x], 1, 100);
	for(int x = 0; x < sizeof int32bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int32bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	volatile uint64_t value3;
	volatile uint64_t value4;
	timerInitial = 0;
	timerFinal = 0;
	average = 0;

	for(int i = 0; i < 100; i++)
	{
		value3 = random_64bit();
		value4 = random_64bit();
		timerInitial = timer_start();
		value3 = value3 + value4;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof addMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&addMessage[x], 1, 100);
	for(int x = 0; x < sizeof int64bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int64bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//multiply 2 int 32

	timerInitial = 0;
	timerFinal = 0;
	average = 0;

	for(int i = 0; i < 100; i++)
	{
		value1 = random_32bit();
		value2 = random_32bit();
		timerInitial = timer_start();
		value1 = value1 * value2;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof multMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&multMessage[x], 1, 100);
	for(int x = 0; x < sizeof int32bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int32bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);


	//mult 2 64 bit
	timerInitial = 0;
	timerFinal = 0;
	average = 0;

	for(int i = 0; i < 100; i++)
	{
		value3 = random_64bit();
		value4 = random_64bit();
		timerInitial = timer_start();
		value3 = value3 * value4;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof multMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&multMessage[x], 1, 100);
	for(int x = 0; x < sizeof int64bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int64bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//divide 2 int 32

	timerInitial = 0;
	timerFinal = 0;
	average = 0;

	for(int i = 0; i < 100; i++)
	{
		value1 = random_32bit();
		value2 = random_32bit();
		timerInitial = timer_start();
		value1 = value1 / value2;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof divMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&divMessage[x], 1, 100);
	for(int x = 0; x < sizeof int32bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int32bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//div 2 64 bit
	timerInitial = 0;
	timerFinal = 0;
	average = 0;

	for(int i = 0; i < 100; i++)
	{
		value3 = random_64bit();
		value4 = random_64bit();
		timerInitial = timer_start();
		value3 = value3 / value4;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof divMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&divMessage[x], 1, 100);
	for(int x = 0; x < sizeof int64bit; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&int64bit[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//assign 8byte struct

	timerInitial = 0;
	timerFinal = 0;
	average = 0;
	volatile struct smallBytes value5;
	volatile struct smallBytes value6;

	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 8; j++)
			value5.data[j] = random_byte();

		timerInitial = timer_start();
		value6 = value5;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	for(int x = 0; x < sizeof assignMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&assignMessage[x], 1, 100);
	for(int x = 0; x < sizeof struct8byte; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&struct8byte[x], 1, 100);
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
	for(int x = 0; x < sizeof ticks; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//assign 124 byte struct

		timerInitial = 0;
		timerFinal = 0;
		average = 0;
		volatile struct mediumBytes value7;
		volatile struct mediumBytes value8;

		for(int i = 0; i < 100; i++)
		{
			for(int j = 0; j < 124; j++)
				value7.data[j] = random_byte();

			timerInitial = timer_start();
			value8 = value7;
			timerFinal = timer_stop(timerInitial);
			results[i] = timerFinal;
		}
		for(int i = 0; i < 100; i++)
		{
			average += results[i];
		}
		average = average / 100;
		for(int x = 0; x < sizeof assignMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&assignMessage[x], 1, 100);
		for(int x = 0; x < sizeof struct128byte; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&struct128byte[x], 1, 100);
		sprintf (structCharAverage, "%d", average);
		for(int x = 0; x < sizeof structCharAverage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&structCharAverage[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

		//assign 1024 byte struct

		timerInitial = 0;
		timerFinal = 0;
		average = 0;
		volatile struct largeBytes value9;
		volatile struct largeBytes value10;

		for(int i = 0; i < 100; i++)
		{
			for(int j = 0; j < 1024; j++)
				value9.data[j] = random_byte();

			timerInitial = timer_start();
			value10 = value9;
			timerFinal = timer_stop(timerInitial);
			results[i] = timerFinal;
		}
		for(int i = 0; i < 100; i++)
		{
			average += results[i];
		}
		average = average / 100;
		for(int x = 0; x < sizeof assignMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&assignMessage[x], 1, 100);
		for(int x = 0; x < sizeof struct1024byte; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&struct1024byte[x], 1, 100);
		sprintf (structCharAverage, "%d", average);
		for(int x = 0; x < sizeof structCharAverage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&structCharAverage[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);


}
