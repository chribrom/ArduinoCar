/*
 * Robot.cpp
 *
 * Created: 10/31/2022 2:05:14 PM
 * Author : chrib
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "Pwm/MotorPWM.h"
#include "MotorIo/MotorIo.h"
#include "MotorControl/MotorControl.h"
#include "Uart/Uart.h"
#include "CommandHandler/CommandHandler.h"
#include "Timer/Timer.h"

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
	Timer timer;
	timer.setup();
	MotorPWM motorPwm; 
	MotorIo motorDirectionControl; //Consider putting these under the same class Motor
	MotorControl motorControl; 
	CommandHandler commandHandler; 
	Uart uart; 
	uart.setup();
	commandHandler.dependencyInject(&uart, &motorControl); 
	 
	char a[] = "Hello"; 
	uart.sendData(a);
	
	motorDirectionControl.setupDigitalIo(); 
	motorDirectionControl.setMotorDirecton(Motors::frontRight, true); 
	motorDirectionControl.setMotorDirecton(Motors::frontLeft, true); 
	motorDirectionControl.setMotorDirecton(Motors::backRight, true); 
	motorDirectionControl.setMotorDirecton(Motors::backLeft, true); 
	
	
	motorPwm.setup(); 
	timer.dependencyInject(&uart);
	uint16_t time = 0; 
	while(true)
	{
		commandHandler.execute();
		if(timer.getTime() != time)
		{
			time = timer.getTime();
			char timeAscii[10];
			sprintf(timeAscii, "%d", time);
			uart.sendData("One second \n");
			uart.sendData(timeAscii);
		}
		
		//uart.sendData("One second \n");
		//uart.sendData(timeAscii);

		//uart.sendData(103);
		//uart.sendData(10);
		//uart.sendData(10);


	}
    while (1) 
    {
 
		for (uint8_t i = 0; i < 1000; i++)
		{
		}
		//OCR4AH = 0xFF; 
		//OCR4AL = 0xFF; 
    }
}

