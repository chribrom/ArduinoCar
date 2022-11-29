#include "CommandHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CommandHandler::dependencyInject(Uart * uart, MotorControl* motorControl)
{
	m_Uart = uart;
	m_MotorControl = motorControl; 
}



void CommandHandler::handleUartCommand(char uartCommand[] )
{
	auto commandId = static_cast<uint8_t>(uartCommand[0]);  
	int16_t commandValue = charToInt(uartCommand); 

	switch (commandId)
	{
	case setSpeed:
		m_Uart->sendData("setSpeed"); 

		m_MotorControl->setSpeed(commandValue, Motors::frontLeft);
		m_MotorControl->setSpeed(commandValue, Motors::frontRight);
		m_MotorControl->setSpeed(commandValue, Motors::backLeft);
		m_MotorControl->setSpeed(commandValue, Motors::backRight);
		break;

	case setLeftSideSpeed:
		break; 

	case setRightSideSpeed:
		break; 

	case setFrontLeftSpeed:
		break;

	case setFrontRightSpeed:
		break;

	case setBackLeftSpeed: 
		break; 

	case setBackRightSpeed:
		break;
	default:
		break;
	}
}

void CommandHandler::execute()
{
	if(m_Uart != nullptr)
	{
		if(m_Uart->getLatestMessage(m_message))
		{
			handleUartCommand(m_message);
		}
	}
}

int16_t CommandHandler::charToInt(char string[])
{
	int16_t value = 0; 
	//Do some errot checking and check for negative numbers
	for (int8_t i = 1; string[i] != '\0'; i++) //start at 1 cause the first bit is the header. Find a better solution for this. Dirty as fuck
	{
		value = value * 10 + string[i] - '0';
	}
	
	return value; 
}

