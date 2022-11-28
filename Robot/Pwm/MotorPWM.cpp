#include "MotorPWM.h"



void MotorPWM::setup()
{
	//Using timer 4 for pwm (Digital 7 and Digital 6)
	DDRH = (1 << DDH4) | (1 << DDH3); //Set pins as output
	TCCR4A = 0b10101010;
	TCCR4B = 0b00011001;
	ICR4 = 0xFFFF;
	//Using timer 1 for pwm	(Digital 12 and Digital 11)
	DDRB = (1 << DDB5) | (1 << DDB6);
	TCCR1A = 0b10101010;
	TCCR1B = 0b00011001;
	ICR1 = 0xFFFF;
}


void MotorPWM::setPWM(int motor, uint16_t value)
{
	switch (motor)
	{
		case test::frontLeft:
			OCR4B = value; 
			break;
		case test::frontRight:
			OCR4A = value; 
			break;
		case test::backLeft:
			OCR1A = value; 
			break;
		case test::backRight:
			OCR1B = value; 
			break;
		default:
			break; 
	}
	
}