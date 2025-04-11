/**@addtogroup PID_Control
 * @{
 * @file pid.h
 * @brief Header for pid related functions.
 * @author Quinn Maloney
 */
#include "stm32f10x.h"
#include "constants.h"

/**
 * @brief Structure to keep PID values in
 * @details stores all necessary values for PID calculations in a 
 * structure for convenient use and variable passing.
 */
typedef struct {
	double kp;
	double ki;
	double kd;
	int previous_error;
	double integral;
	double time;
} pid;

void  pid_init(pid *controller);
int pid_update(pid *controller, int setpoint, int measurement);
/** @} */
