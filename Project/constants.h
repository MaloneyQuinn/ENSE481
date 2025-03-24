#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "stm32f10x.h"

enum cli_return
{
	REMOVE_CHARACTER = -1,
	DO_NOTHING = 0,
	ADD_CHARACTER = 1,
	GET_VERSION = 2,
	GET_HELP = 3,
	CLI_ERROR = 4
};

const static char PROGRAM_VERSION[] = "Version 1.0.0";

const static uint16_t MAX_DUTY = 2400;
const static uint16_t MIN_DUTY = 600;
#endif
