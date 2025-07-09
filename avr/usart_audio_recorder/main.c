#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

#include <avrtools/button.h>
#include <avrtools/usart.h>


static inline void init_ADC0(void) {
	ADMUX |= (1 << REFS0); // reference voltage on AVCC
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // ADC clock prescaler 8
	ADMUX |= (1 << ADLAR); // left-adjust result
	ADMUX |= MIC; // select input
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // auto-trigger enable
	ADCSRA |= (1 << ADSC); // start first conversion
}

int main(void) {
  init_ADC0();
	usart_init();

	uint8_t sample = 0;

  while (1) {
    ADCSRA |= (1 << ADSC);
    sample = ADCH;
		usart_print_byte(sample);
		usart_print_string("\r\n");
		//  NOTE: needs clock to wait so we could do it 44100 times a second
  }
  return 0;
}
