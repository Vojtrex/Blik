/*
 * main.c
 *
 * Created: 1/9/2024 12:43:45 PM
 *  Author: vn
 */ 

#include <xc.h>

#include <avr/interrupt.h>

#define LEDPIN1 PB0

ISR(TIM0_OVF_vect) {
	// Toggle port B pin 4 output state
	PORTB ^= _BV(LEDPIN1);
}

int main(void) {
	// Set port B output 0 as output
	DDRB = _BV(LEDPIN1);

	// Prescale timer to 1/1024th the clock rate
	TCCR0B |= _BV(CS02) | _BV(CS00);

	// Enable timer overflow interrupt
	TIMSK0 |=_BV(TOIE0);

	// Enable interrupts
	sei();

	// Loop forever
	while(1) {}
}