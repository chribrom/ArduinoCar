#pragma once

#include <avr/io.h>

namespace test
{
	enum Motors{frontLeft, frontRight, backLeft, backRight};
}




class MotorPWM
{
public:
	void setup(); 
	void setPWM(int motor, uint16_t value); 
protected:
private:
};

