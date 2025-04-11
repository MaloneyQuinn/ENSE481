/**@addtogroup PID_Control
 * @{
 * @file pid.h
 * @brief Contains pid related functions.
 * @author Quinn Maloney
 */

#include "pid.h"

/**
 * @brief Initializes values of pid struct for use.
 * @details sets pid constants (kp, ki, kd, time interval) to their values
 * as well as setting all other info to 0. kp, ki, and kd all tuned through
 * testing.
 * @param controller (*pid) pid struct that is getting initialized gets passed in.
 */
void pid_init(pid *controller) {
	/* Clear controller variables */
	controller->kp = 2.0;
	controller->ki = 2.5;
	controller->kd = 3.0;
	controller->previous_error = 0;
	controller->integral = 0;
	controller->time = 0.1;
}

/**
 * @brief Takes current value and adjust duty cycle to balance ping pong ball.
 * @details uses a PID control system/ algorithm to determine how to adjust servo to balance
 * ping pong ball in correct spot.
 * @param controller (*pid) pid struct that is used to adjust duty values.
 * @param setpoint (int) the target location in IR-sensor reading values.
 * @param measurement (int) the current locatio in IR-sensor readings.
 * @return result (int) new calculated duty cycle.
 */
int pid_update(pid *controller, int setpoint, int measurement)
{
	int error = -(setpoint - measurement);
	
	double proportional = controller->kp * error;
	
	controller->integral += 0.5 * controller->ki * controller->time * (error + controller->previous_error);
	
	if(controller->integral > MAX_INTEGRAL)
		controller->integral = MAX_INTEGRAL;
	else if(controller->integral < MIN_INTEGRAL)
		controller->integral = MIN_INTEGRAL;
	
	double change = error - controller->previous_error;
	
	double derivative = controller->kd * change;
	
	int result = (int)(proportional + controller->integral + derivative);
	
	if(result > MAX_DUTY)
		result = MAX_DUTY;
	else if(result < MIN_DUTY)
		result = MIN_DUTY;
	
	return result;
}
/** @} */
