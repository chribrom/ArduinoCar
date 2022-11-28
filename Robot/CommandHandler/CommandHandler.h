#pragma once

#include <avr/io.h>

#include "../Uart/Uart.h"
//All set commands consist of a header, first byte in message, followed by the value to be set. 

enum UartCommands
{	
	setSpeed, 
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
		void dependencyInject(Uart * uart); 
		void handleUartCommand(char[]); 
		void execute();
	protected:
	private:
		Uart * m_Uart = nullptr; //Used for the send calll
		char m_message[20];
};

