#pragma once

#include <avr/io.h>
#include <string.h>

#include "../Common/MotorEnum.h"

class MotorIo
{
	public:
	void setupDigitalIo();
	void setMotorDirecton(Motors motor, bool forward);
	protected:
	private:
};




