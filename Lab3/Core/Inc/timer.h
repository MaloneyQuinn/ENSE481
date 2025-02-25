/*
 * timer.c
 *
 *  Created on: Feb 25, 2025
 *      Author: Quinn Maloney
 */
#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Global Variables
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;

//Functions
int16_t timer_start();
uint16_t timer_stop(uint16_t);
uint32_t factorial(uint32_t);
float exponent(float, uint32_t);
float taylor_sin(float);
float taylor_cos(float);
void run_test();

#endif /* INC_CLI_H_ */
