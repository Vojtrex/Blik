/*
* main.c
*
* Created: 1/9/2024 12:43:45 PM
*  Author: vn
*/

#define F_CPU 1000000UL

#include <xc.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <util/delay.h>

#define LEDPIN1 PINB1
#define LEDPIN2 PINB0
#define BUTTONPIN PINB2

volatile bool button_pressed = false;

ISR(TIM0_OVF_vect) {
	// Toggle buton pressed boolean
	button_pressed = true;
}

ISR(PCINT0_vect) {
	if (PINB & _BV(BUTTONPIN))
	// Toggle buton pressed boolean
	button_pressed = true;
}

void init (){
	// Set B ports as outputs
	DDRB |= _BV(LEDPIN1);
	DDRB |= _BV(LEDPIN2);
	
	// Prescale timer to 1/1024th the clock rate
	TCCR0B |= _BV(CS02) | _BV(CS00);

	// Enable timer overflow interrupt
	//TIMSK |=_BV(TOIE0);
	
	PCMSK |= _BV(BUTTONPIN);   // Set pin change interrupt mask to listen to port b3
	
	MCUCR = _BV(ISC01);    // Set interrupt on INT0 pin falling edge (high pulled to low)
	
	//Set sleep mode to power down
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	// Enable interrupts
	GIMSK |= _BV(PCIE);     // Enable PCINT interrupt
	sei();
	
}

int main(void) {
	//Initialize
	init();

	for (;;) {
		
		if (button_pressed)
		{
			
			for (uint8_t i = 0; i < 30; i++)
			{
				PORTB ^= _BV(LEDPIN1);
				_delay_ms(500UL);
				PORTB ^= _BV(LEDPIN1) | _BV(LEDPIN2);
				_delay_ms(500UL);
				PORTB ^= _BV(LEDPIN2);
			}
			button_pressed = false;
		}
		sleep_mode();
	}
}