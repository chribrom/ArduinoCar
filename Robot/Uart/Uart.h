#pragma once

#include <avr/io.h>



class Uart
{
	public:
		static char buffer[20]; 
		static char lastReceivedMessage[20]; 
		static char messageToSend[20]; 
		static uint8_t messageToSendIndex;
		static uint8_t messageReceiveIndex; 
		static bool busySending;
		static bool receivedNewMessage;  

		void setup();
		void sendData(char data[]);
		void sendReceivedData();
		bool getLatestMessage(char[]); 

		void enableInterrupt(); 
		void disableInterrupt();
	protected:
	private:
		char m_latestReceived;
};

