#include "Uart.h"

#include <avr/interrupt.h>
#include <string.h>

#define FOSC 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC/(16UL*BAUD)-1)

//make struct
char Uart::buffer[20]; 
char Uart::lastReceivedMessage[20]; 
char Uart::messageToSend[20];
uint8_t Uart::messageToSendIndex = 0; 
uint8_t Uart::messageReceiveIndex = 0; 
bool Uart::receivedNewMessage = false; 
bool Uart::available = true; 

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

void Uart::sendData(char data[]) //Need a poll on whether its busy with an overall message or not
{
	while(!(UCSR0A & (1 << UDRE0)) || !Uart::available)
	{
		//Block, wait until read to send
	}
	strncpy(Uart::messageToSend, data, 20); 
	Uart::messageToSendIndex = 0; 
	Uart::available = false; //Make sure full message is sent before being able to take in another
	UDR0 = Uart::messageToSend[messageToSendIndex]; 
}

void Uart::sendReceivedData() //This should be deleted
{
	if(Uart::receivedNewMessage)
	{
		sendData(buffer);
		Uart::receivedNewMessage = false; 
	}
	
}

bool Uart::getLatestMessage(char message[] )
{
	
	if(Uart::receivedNewMessage)
	{
		disableInterrupt();
		Uart::receivedNewMessage = false; 
		strncpy(message, Uart::lastReceivedMessage, 20); 
		enableInterrupt();
		return true; 
	}
	
	return false; 
}

void Uart::enableInterrupt()
{
	UCSR0B |= (1<<RXCIE0);
}

void Uart::disableInterrupt()
{
	UCSR0B &= ~(1<<RXCIE0);
}

ISR(USART0_RX_vect)
{	
	Uart::buffer[Uart::messageReceiveIndex] = UDR0;
	if(Uart::buffer[Uart::messageReceiveIndex] == '\n') //When connecting to nano, use null 
	{//End of message from arduino serial	
		Uart::buffer[Uart::messageReceiveIndex] = '\0'; //Change newline with null
		strncpy(Uart::lastReceivedMessage, Uart::buffer, Uart::messageReceiveIndex+1);
		Uart::messageReceiveIndex = 0;
		Uart::receivedNewMessage = true;
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
		Uart::available = true; 
	}
	else
	{
		
		UDR0 = Uart::messageToSend[++Uart::messageToSendIndex];
	}
}