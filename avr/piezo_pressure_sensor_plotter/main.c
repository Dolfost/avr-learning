#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

#include <avrtools/usart.h>
#include <avrtools/speaker.h>

static inline void init_ADC0(void) {
	ADMUX = (ADMUX &0x0f) | PIEZO;
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS2);
  ADCSRA |= (1 << ADEN);
	ADMUX |= (1 << ADLAR);
}

int main(void) {
	uint8_t piezo_voltage;

  init_ADC0();
	usart_init();
  LED_DDR = 0xff;

	ADCSRA |= (1 << ADSC);
  while (1) {
    loop_until_bit_is_clear(ADCSRA, ADSC);
		piezo_voltage = ADCH;
    ADCSRA |= (1 << ADSC);
		usart_transmit_byte(piezo_voltage);
  }
  return 0;
}
