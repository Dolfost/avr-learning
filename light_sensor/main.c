#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

#include <avrtools/button.h>
#include <avrtools/usart.h>
#include <avrtools/speaker.h>


static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS2);
  ADCSRA |= (1 << ADEN);
}

int main(void) {
  uint8_t ledValue;
  uint16_t adcValue;
  uint8_t i;


  initADC0();
#ifdef DEBUG 
	usart_init();
#endif
  LED_DDR = 0xff;
	SPEAKER_DDR |= 1 << SPEAKER;

  while (1) {
    ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
		play_note(1024 - adcValue - 50, 5000);
    loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
    adcValue = ADC;                                     /* read ADC in */
    ledValue = (adcValue >> 7);
    LED_PORT = 0;
    for (i = 0; i <= ledValue; i++)
      LED_PORT |= (1 << i);

#ifdef DEBUG 
		usart_print_int(adcValue);
		usart_print_string("\t");
    for (i = ledValue+1; i < 8; i++)
			usart_print_string("-");
		for (i = 0; i <= ledValue; i++)
			usart_print_string("O");
		usart_print_string("\n\r");
#endif

    _delay_ms(50);
  }
  return 0;
}
