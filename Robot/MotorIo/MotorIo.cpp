#include "MotorIo.h"

using namespace Motors; 

void MotorIo::setupDigitalIo()
{
	DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3); 
	DDRL = (1 << DDL0) | (1 << DDL1) | (1 << DDL2) | (1 << DDL3); 
}

void MotorIo::setMotorDirecton(int motor)
{	
	switch (motor)
	{
		case frontLeft:
			PORTA &= ~(1 << DDA0); 
			PORTA |= (1 << DDA1); 
			break;
		case frontRight:
			PORTA &= ~(1 << DDA2);
			PORTA |= (1 << DDA3);  
			break;
		case backLeft:
			PORTL &= ~(1 << DDL0);
			PORTL |= (1 << DDL1);
			break;
		case backRight:
			PORTL &= ~(1 << DDL2);
			PORTL |= (1 << DDL3);
			break;
		default:
			break;
	}
}