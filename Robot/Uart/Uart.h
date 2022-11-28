#pragma once

#include <avr/io.h>



class Uart
{
	public:
		static unsigned char buffer[20]; 
		static unsigned char lastReceivedMessage[20]; 
		static unsigned char* messageToSend; 
		static uint8_t messageToSendIndex;
		static uint8_t messageReceiveIndex; 
		static bool busySending;
		static bool receivedMessage;  

		void setup();
		void sendData(unsigned char data[]);
		void sendReceivedData();
	protected:
	private:
		unsigned char m_latestReceived;
};

