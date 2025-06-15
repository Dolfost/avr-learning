#include <avr/io.h>
#include <util/delay.h>

#include <lib.h>

#define SLEEP 250

int main(void) {

  DDRB |= 0b11111111;    

	uint8_t port;

	while (1) {
		_delay_ms(SLEEP);
		do_nothing();
	}

  return 0;
}
