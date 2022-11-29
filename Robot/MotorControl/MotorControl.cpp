#include "MotorControl.h"

void MotorControl::setSpeed(uint16_t speed, Motors motor, bool forward)
{
	m_MotorIo->setMotorDirecton(motor, forward);
	m_MotorPwm->setPWM(motor, speed); 
}

void MotorControl::dependencyInject(MotorIo* motorIo, MotorPWM* motorPwm)
{
	m_MotorIo = motorIo; 
	m_MotorPwm = motorPwm; 
}

