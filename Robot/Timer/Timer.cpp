#include "Timer.h"

#include <avr/interrupt.h>

uint16_t Timer::secondsSinceStart = 0; 
Uart* Timer::uart = nullptr; 
void Timer::setup() //timer set to interrupt each second
{
	sei();
	TCCR3A = 0;// set entire TCCR1A register to 0
	TCCR3B = 0;// same for TCCR1B
	TCNT3  = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR3A = 7811*2;// = (16*10^6) / (1*1024) - 1 (must be <65536)15624
	OCR3B = 7811;  //Freq 2 Hz
	OCR3C = 1562; //Freq 10 Hz Use these 
	// turn on CTC mode
	TCCR3B |= (1 << WGM12);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR3B |= (1 << CS32) | (1 << CS30);
	// enable timer compare interrupt
	TIMSK3 |= (1 << OCIE3A) | (1 << OCIE3B) | (1 << OCIE3C);


}


void Timer::dependencyInject(Uart* uart)
{
	uart = uart;
}

void Timer::debug()
{
	uart->sendData("Sending stuff");
}

ISR(TIMER3_COMPA_vect)
{
	Timer::incrementTime();
}

ISR(TIMER3_COMPB_vect)
{

}

ISR(TIMER3_COMPC_vect)
{
	
}
}