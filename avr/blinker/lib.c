#include <lib.h>

void do_nothing() {
	PORTB ^= (1 << PB0);    
}
