/*
 * Robot.cpp
 *
 * Created: 10/31/2022 2:05:14 PM
 * Author : chrib
 */ 

#include <avr/io.h>
#include "Pwm/MotorPWM.h"
#include "MotorIo/MotorIo.h"
#include "Uart/Uart.h"
#include "CommandHandler/CommandHandler.h"

void setup()
{
	DDRA = (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3); 
	
}

void setupPwm()
{
	//Using timer 4 for pwm (Digital 7 and Digital 6) 
	DDRH = (1 << DDH4) | (1 << DDH3); //Set pins as output
	TCCR4A = 0b10101010; 
	TCCR4B = 0b00011001; 
	ICR4 = 0xFFFF; 
	//Using timer 1 for pwm	(Digital 12 and Digital 11) 
	DDRB = (1 << DDB5) | (1 << DDB6); 
	TCCR1A = 0b10101010; 
	TCCR2B = 0b00011001; 
	ICR1 = 0xFFFF; 
}


int main(void)
{
	//setupPwm();
	MotorPWM motorControll; 
	MotorIo motorDirectionControl;
	CommandHandler commandHandler; 
	Uart uart; 
	uart.setup();
	commandHandler.dependencyInject(&uart); 
	 
	char a[] = "Hello"; 
	uart.sendData(a);
	while(true)
	{
		//uart.sendReceivedData();
		commandHandler.execute(); 
		//uart.sendData(103);
		//uart.sendData(10);
		//uart.sendData(10);


	}
	motorDirectionControl.setupDigitalIo(); 
	motorDirectionControl.setMotorDirecton(Motors::frontRight); 
	motorDirectionControl.setMotorDirecton(Motors::frontLeft); 
	motorDirectionControl.setMotorDirecton(Motors::backRight); 
	motorDirectionControl.setMotorDirecton(Motors::backLeft); 
	
	
	motorControll.setup(); 
	motorControll.setPWM(Motors::frontLeft,50000);
	motorControll.setPWM(Motors::frontRight, 50000);
	motorControll.setPWM(Motors::backLeft, 50000);
	motorControll.setPWM(Motors::backRight, 50000); 

	
    while (1) 
    {
 
		for (uint8_t i = 0; i < 1000; i++)
		{
		}
		//OCR4AH = 0xFF; 
		//OCR4AL = 0xFF; 
    }
}

