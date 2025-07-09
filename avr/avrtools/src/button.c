#include <avrtools/button.h>

#include <util/delay.h>

uint8_t button_debounce(uint8_t byte, uint8_t bit) { 
	if (!(byte & (1 << bit))) { 
		_delay_us(1000);
		if (!(byte & (1 << bit))) 
			return 1;
	}
	return 0;
}
