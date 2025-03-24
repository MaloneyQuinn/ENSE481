/**
 * @file constants.h
 * @brief Has constants used through out the program.
 * @author Quinn Maloney
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "stm32f10x.h"

/**
 * @brief enum used for CLI interface.
 * @details Used for CLI return values to determine what action
 * should be taken in main().
 */
enum cli_return
{
	REMOVE_CHARACTER = -1,
	DO_NOTHING = 0,
	ADD_CHARACTER = 1,
	GET_VERSION = 2,
	GET_HELP = 3,
	CLI_ERROR = 4,
	DECREASE_DUTY = 5,
	INCREASE_DUTY = 6
};

/**
 * @var char[] PROGRAM_VERSION
 * Contains version and build date info.
 */
const static char PROGRAM_VERSION[] = "Version 1.0.0, March 25, 2024, Milestone build";

/**
 * @var uint16_t MAX_DUTY
 * Contains the maximum value duty cycle allowed
 */
const static uint16_t MAX_DUTY = 2400;

/**
 * @var uint16_t MIN_DUTY
 * Contains the minimum value duty cycle allowed
 */
const static uint16_t MIN_DUTY = 600;
#endif
