#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pins.h"
#include "support.h"

static inline void initTimer1(void) {
  /* Normal mode (default), just counting */
  TCCR1B |= (1 << CS11) | (1 << CS10);
	/* Clock speed: 1 MHz / 64,
		 each tick is 64 microseconds ~= 15.6 per ms No special output modes */
}

int main(void) {
  uint16_t timerValue;

	usart_init();
  initTimer1();
  LED_DDR = 0xff; /* all LEDs for output */
  BUTTON_PORT |= (1 << BUTTON); /* enable internal pull-up */

  usart_print_string("\r\nReaction Timer:\r\n");
  usart_print_string("---------------\r\n");
  usart_print_string("Press any key to start.\r\n");

  while (1) {
    usart_receive_byte();
    usart_print_string("\r\nGet ready...");
    randomDelay();

    usart_print_string("\r\nGo!\r\n");
    LED_PORT = 0xff;
    TCNT1 = 0; /* reset counter */

    if (bit_is_clear(BUTTON_PIN, BUTTON)) {
      /* Button pressed _exactly_ as LEDs light up.  Suspicious. */
      usart_print_string("You're only cheating yourself.\r\n");
    } else {
      // Wait until button pressed, save timer value.
      loop_until_bit_is_clear(BUTTON_PIN, BUTTON);
      timerValue = TCNT1 >> 4;
      /* each tick is approx 1/16 milliseconds, so we bit-shift divide */

      printMilliseconds(timerValue);
      printComments(timerValue);
    }

    // Clear LEDs and start again.
    LED_PORT = 0x00;
    usart_print_string("Press any key to try again.\r\n");

  }
  return 0;
}
