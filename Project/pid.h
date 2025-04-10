
#include "stm32f10x.h"
#include "constants.h"

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
/*
A rule-of-thumb process:

Set I and D to 0. Increase P until you get oscillation off the system. Then cut P in half

increase I until you are returning to the set-point quick enough for your application. Too much integral gain can cause a lot of overshoot.

increase D until you’ve started to dampen your response as you approach the set point.
*/
