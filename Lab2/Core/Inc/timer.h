/*
 * timer.h
 *
 *  Created on: Nov 6, 2024
 *      Author: qkmal
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdlib.h>

//Global Variables
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;

struct smallBytes
{
	char data[8];
};

struct mediumBytes
{
	char data[124];
};

struct largeBytes
{
	char data[1024];
};


//Functions
int16_t timer_start();
uint16_t timer_stop(uint16_t);
int32_t random_32bit();
int64_t random_64bit();
char random_byte();
void clock_info();
void run_test();



#endif /* INC_CLI_H_ */
