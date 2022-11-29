#pragma once

#include <avr/io.h>

#include "../MotorIo/MotorIo.h"
#include "../Pwm/MotorPWM.h"

class MotorControl
{
public:
	void setSpeed(int16_t speed, Motors motor);
	void dependencyInject(MotorIo* motorIo, MotorPWM* motorPwm); 
protected:
private:
	MotorIo* m_MotorIo = nullptr; 
	MotorPWM* m_MotorPwm = nullptr; 
};

