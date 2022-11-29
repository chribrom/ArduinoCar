#pragma once

#include <avr/io.h>

#include "../Common/MotorEnum.h"

//namespace test
//{
//	enum Motors{frontLeft, frontRight, backLeft, backRight};
//}




class MotorPWM
{
public:
	void setup(); 
	void setPWM(Motors motor, uint16_t value); 
protected:
private:
};

