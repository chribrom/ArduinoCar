﻿#include "Uart.h"

#include <avr/interrupt.h>


#define FOSC 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/(16UL*BAUD)-1)


unsigned char Uart::buffer[20]; 
unsigned char Uart::lastReceivedMessage[20]; 
unsigned char* Uart::messageToSend = nullptr;
uint8_t Uart::messageToSendIndex = 0; 
uint8_t Uart::messageReceiveIndex = 0; 
bool Uart::receivedMessage = false; 

bool received = false; 
void Uart::setup()
{
	sei();
	Uart::buffer[9] = '\0'; //Why?
	UBRR0H = (unsigned char) (MYUBRR >> 8);
	UBRR0L = (unsigned char) MYUBRR;
	UCSR0B = (1<<RXCIE0) | (1<<TXCIE0) | (1<<RXEN0) | (1<<TXEN0); //Enable receive and transmit interrupt as well as receiver and transmitter
	UCSR0C &= ~((1 << UMSEL00 ) | ( 1 << UMSEL01)); // Set both to zero, async
	UCSR0C &= ~(1 << USBS0); // 1 Stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits
	
}

void Uart::sendData(unsigned char data[])
{
	while(!(UCSR0A & (1 << UDRE0)))
	{
		//Block, wait until read to send
	}
	Uart::messageToSend = data;
	Uart::messageToSendIndex = 0; 
	UDR0 = Uart::messageToSend[messageToSendIndex]; 
}

void Uart::sendReceivedData()
{
	if(Uart::receivedMessage)
	{
		sendData(buffer);
		Uart::receivedMessage = false; 
	}
	
}

ISR(USART0_RX_vect)
{	
	Uart::buffer[Uart::messageReceiveIndex] = UDR0;
	if(Uart::buffer[Uart::messageReceiveIndex] == '\n') //When connecting to nano, use null 
	{//End of message from arduino serial	
		Uart::buffer[Uart::messageReceiveIndex] = '\0'; //Change newline with null
		Uart::messageReceiveIndex = 0;
		Uart::receivedMessage = true;
	}
	else
	{
		Uart::messageReceiveIndex++;
	}
}

ISR(USART0_TX_vect)
{
	if(Uart::messageToSend[Uart::messageToSendIndex] == '\0')
	{//Check if last char sent was nul
		UCSR0A |= (1 << TXC0); // Stop sending
	}
	else
	{
		UDR0 = Uart::messageToSend[++Uart::messageToSendIndex];
	}
}