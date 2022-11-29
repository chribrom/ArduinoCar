#pragma once

#include <avr/io.h>

#include "../Uart/Uart.h"

class Timer
{
	public:
		
		void setup();
		void dependencyInject(Uart* uart);
		uint16_t getTime() { return secondsSinceStart; }
		static void incrementTime(){secondsSinceStart++;} 
		static void debug(); 
		
	protected:
	private:
		 static uint16_t secondsSinceStart;
		 static Uart* uart;
};

