#include <avr/io.h>
#include <util/delay.h>


void delay_ms(uint16_t del) {
  for (uint16_t i = 0; i < del; i++)
    _delay_ms(1);
}

void put(uint32_t r) { 
	PORTB = r;
	PORTD = r >> 8;
}
#define P 150
#define M 50
#define S 113
uint16_t d(uint8_t i) { 
	return P - P*pow(M_E, - pow(i - 7.5, 2)/S) + M;
}

int main(void) {
  DDRB = 0xff;
  DDRD = 0xff;

  uint32_t r = 1;
  uint16_t delay = 200;
  bool left = true;

  while (true) {
    for (uint8_t bit = 0; bit < 15; bit++) {
			r = left ? r << 1 : r >> 1;
			put(r);
      delay_ms(d(bit));
    }
		left = not left;
  }

  return (0);
}
