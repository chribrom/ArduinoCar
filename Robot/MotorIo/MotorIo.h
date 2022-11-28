#pragma once

#include <avr/io.h>
#include <string.h>


namespace Motors
{
	enum Motors{frontLeft, frontRight, backLeft, backRight};
}
class MotorIo
{
	public:
	void setupDigitalIo();
	void setMotorDirecton(int motor);
	protected:
	private:
};




