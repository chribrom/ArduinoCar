#pragma once

#include <avr/io.h>

#include "../Uart/Uart.h"
#include "../MotorControl/MotorControl.h"
#include "../Common/MotorEnum.h"
//All set commands consist of a header, first byte in message, followed by the value to be set. 

enum UartCommands
{	
	setSpeed = (int)'a', 
	setLeftSideSpeed,
	setRightSideSpeed,
	setFrontLeftSpeed, 
	setFrontRightSpeed, 
	setBackLeftSpeed,
	setBackRightSpeed
};

class CommandHandler
{
	public:
		CommandHandler() = default; 
		~CommandHandler() = default;
		void dependencyInject(Uart * uart, MotorControl * motorControl); 
		void handleUartCommand(char[]); 
		void execute();
	protected:
	private:
		int16_t charToInt(char[]); 
		Uart* m_Uart = nullptr; //Used for the send call
		MotorControl* m_MotorControl = nullptr; 
		char m_message[20];
};

