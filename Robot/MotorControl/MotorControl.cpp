#include "MotorControl.h"

void MotorControl::setSpeed(int16_t speed, Motors motor)
{
	if(speed >= 0)
	{
		m_MotorIo->setMotorDirecton(motor, true); 
		m_MotorPwm->setPWM(motor, speed);
	}
	else
	{
		m_MotorIo->setMotorDirecton(motor, false);
		m_MotorPwm->setPWM(motor, -1*speed); //Need positive numbers
	}
}

void MotorControl::dependencyInject(MotorIo* motorIo, MotorPWM* motorPwm)
{
	m_MotorIo = motorIo; 
	m_MotorPwm = motorPwm; 
}

