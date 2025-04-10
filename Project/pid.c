

#include "pid.h"

void pid_init(pid *controller) {
	/* Clear controller variables */
	controller->kp = 0.5;
	controller->ki = 0.0;
	controller->kd = 0.0;
	controller->previous_error = 0;
	controller->integral = 0;
	controller->time = 0.25;
}

int pid_update(pid *controller, int setpoint, int measurement)
{
	int error = setpoint - measurement;
	
	double proportional = controller->kp * error;
	
	controller->integral += 0.5 * controller->ki * controller->time * (error + controller->previous_error);
	
	double change = error - controller->previous_error;
	
	double derivative = controller->kd * change;
	
	int result = (int)(proportional + controller->integral + derivative);
	
	if(result > MAX_DUTY)
		result = MAX_DUTY;
	else if(result < MIN_DUTY)
		result = MIN_DUTY;
	
	return result;
}
