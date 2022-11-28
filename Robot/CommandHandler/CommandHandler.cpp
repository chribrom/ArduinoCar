#include "CommandHandler.h"

void CommandHandler::dependencyInject(Uart * uart)
{
	m_Uart = uart; 
}

void CommandHandler::handleUartCommand(unsigned char* uartCommand)
{
	auto commandId = static_cast<uint8_t>(uartCommand[0]); 
	switch (commandId)
	{
	case setSpeed:
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

