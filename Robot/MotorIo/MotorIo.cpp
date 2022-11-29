#include "MotorIo.h"


void MotorIo::setupDigitalIo()
{
	DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3); 
	DDRL = (1 << DDL0) | (1 << DDL1) | (1 << DDL2) | (1 << DDL3); 
}

void MotorIo::setMotorDirecton(Motors motor, bool forward)
{	

	if (forward)
	{
		switch (motor)
		{
			case Motors::frontLeft:
			PORTA &= ~(1 << DDA1);
			PORTA |= (1 << DDA0);
			break;
			case Motors::frontRight:
			PORTA &= ~(1 << DDA3);
			PORTA |= (1 << DDA2);
			break;
			case Motors::backLeft:
			PORTL &= ~(1 << DDL1);
			PORTL |= (1 << DDL0);
			break;
			case Motors::backRight:
			PORTL &= ~(1 << DDL3);
			PORTL |= (1 << DDL2);
			break;
			default:
			break;
		}
	}
	else{
		switch (motor)
		{
			case Motors::frontLeft:
				PORTA &= ~(1 << DDA0); 
				PORTA |= (1 << DDA1); 
				break;
			case Motors::frontRight:
				PORTA &= ~(1 << DDA2);
				PORTA |= (1 << DDA3);  
				break;
			case Motors::backLeft:
				PORTL &= ~(1 << DDL0);
				PORTL |= (1 << DDL1);
				break;
			case Motors::backRight:
				PORTL &= ~(1 << DDL2);
				PORTL |= (1 << DDL3);
				break;
			default:
				break;
		}
	}
}