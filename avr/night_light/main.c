#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

#include <avrtools/button.h>
#include <avrtools/usart.h>
#include <avrtools/speaker.h>

static inline void init_ADC0(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS2);
  ADCSRA |= (1 << ADEN);
	ADMUX |= (1 << ADLAR);
}

int main(void) {
	uint8_t pot_voltage, ldr_voltage;

  init_ADC0();

#ifdef DEBUG 
	usart_init();
#endif
  LED_DDR = 0xff;
	SPEAKER_DDR |= 1 << SPEAKER;

  while (1) {
		ADMUX = (0xf0 & ADMUX) | POT;
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
		pot_voltage = ADCH;
		ADMUX = (0xf0 & ADMUX) | LDR;
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
		ldr_voltage = ADCH;

		if (ldr_voltage <= pot_voltage)
			LED_PORT = 0xff;
		else 
			LED_PORT = 0;

#ifdef DEBUG 
		usart_print_byte(ldr_voltage); 
		usart_print_string("\t <= \t");
		usart_print_byte(pot_voltage); 
		usart_print_string("\r\n");
#endif

  }
  return 0;
}
