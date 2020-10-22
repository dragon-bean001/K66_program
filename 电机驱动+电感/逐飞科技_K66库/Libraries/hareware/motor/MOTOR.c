#include "motor.h"
void Motor34_speed(uint16 motor3,uint16 motor4)
{
	   ftm_pwm_duty(ftm3,ftm_ch1,0); //motor3
		 ftm_pwm_duty(ftm3,ftm_ch2,1000);//motor4
		 ftm_pwm_duty(ftm3,ftm_ch3,0);//motor1
		 ftm_pwm_duty(ftm3,ftm_ch4,1000);//motor2
}