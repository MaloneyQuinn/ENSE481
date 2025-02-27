/*
 * timer.c
 *
 *  Created on: Feb 25, 2025
 *      Author: Quinn Maloney
 */

#include "timer.h"

//starts the timer and returns the initial value
int16_t timer_start()
{
	HAL_TIM_Base_Start(&htim4);
	return __HAL_TIM_GET_COUNTER(&htim4);
}

//stops the timer and returns the time elapsed.
uint16_t timer_stop(uint16_t initial)
{
	volatile uint16_t end = __HAL_TIM_GET_COUNTER(&htim4);
	HAL_TIM_Base_Stop(&htim4);
	volatile uint16_t result = initial - end;
	return result;
}

//returns the factorial of the input
uint32_t factorial(uint32_t input)
{
	volatile uint32_t result = 1;
	for(int i = 1; i <= input; i++)
		result *= i;
	return result;
}

//returns the input to the exponent of power
float exponent(float input, uint32_t power)
{
	volatile float result = input;
	for (int i = 1; i < power; i++)
		result *= input;
	return result;
}

//calculates the taylor series to the 4th degree with an input for sin
float taylor_sin(float input)
{
	volatile float result = input;
	for (int i = 1; i <= 4; i++)
		result += (((exponent(-1, i))*(exponent(input, 2*i + 1)))/(factorial(2*i+1)));
	return result;
}

//calculates the taylor series to the 4th degree with an input for cos
float taylor_cos(float input)
{
	volatile float result = 1;
	for (int i = 1; i <= 4; i++)
		result += (((exponent(-1, i))*(exponent(input, 2*i)))/(factorial(2*i)));
	return result;
}

//runs the tests
void run_test()
{
	//display messages
	char taylorSinMessage[] = "sin using Taylor Series: ";
	char taylorCosMessage[] = "cos using Taylor Series: ";
	char cmathSinMessage[] = "sin using cmath library: ";
	char cmathCosMessage[] = "cos using cmath library: ";
	char inputMessage[] = "For input ";
	char sinEqualsMessage[] = ": sin = ";
	char cosEqualsMessage[] = ": cos = ";
	char completedMessage[] = " Completed in: ";
	char newLine = '\n';
	char cr = '\r';
	char ticks[] = " clock ticks.";

	volatile uint16_t timerInitial = 0;
	volatile uint16_t timerFinal = 0;
	char charTimeResult[5];
	volatile float valueResult = 0;
	char charValueResult[9];

	// Taylor sin test
	for(int x = 0; x < sizeof taylorSinMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&taylorSinMessage[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
	float testInput = 0;
	for (int i = 0; i < 9; i++)
	{
		timerInitial = timer_start();
		valueResult = taylor_sin(testInput);
		timerFinal = timer_stop(timerInitial);
		for(int x = 0; x < sizeof inputMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&inputMessage[x], 1, 100);
		sprintf (charValueResult, "%f", testInput);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof sinEqualsMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&sinEqualsMessage[x], 1, 100);
		sprintf (charValueResult, "%f", valueResult);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof completedMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&completedMessage[x], 1, 100);
		sprintf (charTimeResult, "%d", timerFinal);
		for(int x = 0; x < sizeof charTimeResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charTimeResult[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		testInput += M_PI_4;
	}
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//cmath sin test
	for(int x = 0; x < sizeof cmathSinMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&cmathSinMessage[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
	testInput = 0;
	for (int i = 0; i < 9; i++)
	{
		timerInitial = timer_start();
		valueResult = sin(testInput);
		timerFinal = timer_stop(timerInitial);
		for(int x = 0; x < sizeof inputMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&inputMessage[x], 1, 100);
		sprintf (charValueResult, "%f", testInput);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof sinEqualsMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&sinEqualsMessage[x], 1, 100);
		sprintf (charValueResult, "%f", valueResult);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof completedMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&completedMessage[x], 1, 100);
		sprintf (charTimeResult, "%d", timerFinal);
		for(int x = 0; x < sizeof charTimeResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charTimeResult[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		testInput += M_PI_4;
	}
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	// Taylor cos test
	for(int x = 0; x < sizeof taylorCosMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&taylorCosMessage[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
	testInput = M_PI_2 * -1;
	for (int i = 0; i < 9; i++)
	{
		timerInitial = timer_start();
		valueResult = taylor_cos(testInput);
		timerFinal = timer_stop(timerInitial);
		for(int x = 0; x < sizeof inputMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&inputMessage[x], 1, 100);
		sprintf (charValueResult, "%f", testInput);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof cosEqualsMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&cosEqualsMessage[x], 1, 100);
		sprintf (charValueResult, "%f", valueResult);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof completedMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&completedMessage[x], 1, 100);
		sprintf (charTimeResult, "%d", timerFinal);
		for(int x = 0; x < sizeof charTimeResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charTimeResult[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		testInput += M_PI_4;
	}

	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);

	//cmath cos test
	for(int x = 0; x < sizeof cmathCosMessage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&cmathCosMessage[x], 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
	testInput = M_PI_2 * -1;
	for (int i = 0; i < 9; i++)
	{
		timerInitial = timer_start();
		valueResult = cos(testInput);
		timerFinal = timer_stop(timerInitial);
		for(int x = 0; x < sizeof inputMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&inputMessage[x], 1, 100);
		sprintf (charValueResult, "%f", testInput);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof cosEqualsMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&cosEqualsMessage[x], 1, 100);
		sprintf (charValueResult, "%f", valueResult);
		for(int x = 0; x < sizeof charValueResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charValueResult[x], 1, 100);
		for(int x = 0; x < sizeof completedMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&completedMessage[x], 1, 100);
		sprintf (charTimeResult, "%d", timerFinal);
		for(int x = 0; x < sizeof charTimeResult; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&charTimeResult[x], 1, 100);
		for(int x = 0; x < sizeof ticks; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&ticks[x], 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		testInput += M_PI_4;
	}
	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
}
