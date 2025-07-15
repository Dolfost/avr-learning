
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pins.h"

ISR(INT0_vect) {
	if (bit_is_set(BUTTON_PIN, BUTTON)) 
		LED_PORT |= (1 << 1);
	else
		LED_PORT &= ~(1 << 1);
}

int main(void) {
	LED_DDR = 0xff;
	BUTTON_PORT |= (1 << BUTTON);

	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC00);
	sei();

	while (1) {
		_delay_ms(200);
		LED_PORT ^= (1 << 0);
	}

	return 0;
}
