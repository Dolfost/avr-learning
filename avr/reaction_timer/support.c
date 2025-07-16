
#include "support.h"

void printMilliseconds(uint16_t value) {
  /* Given a value in milliseconds, prints out how many seconds
     you took over the serial port.  Does ascii conversion, prints
     decimal point, and drops extra leading zeros.
   */
  uint8_t digit;

  usart_print_string("\r\nYou took ");
                                               /* add up ten-thousands */
  digit = 0;
  while (value >= 10000) {
    digit++;
    value -= 10000;
  }
  if (digit) {
    usart_transmit_byte('0' + digit);
  }
                                                   /* add up thousands */
  digit = 0;
  while (value >= 1000) {
    digit++;
    value -= 1000;
  }
  usart_transmit_byte('0' + digit);

                            /* decimal point here b/c dividing by 1000 */
  usart_transmit_byte('.');

                                                    /* add up hundreds */
  digit = 0;
  while (value >= 100) {
    digit++;
    value -= 100;
  }
  usart_transmit_byte('0' + digit);
                                                        /* add up tens */
  digit = 0;
  while (value >= 10) {
    digit++;
    value -= 10;
  }
  usart_transmit_byte('0' + digit);

  // Ones digit is easy.
  usart_transmit_byte('0' + value);

  usart_print_string(" seconds.\r\n");
}

void printComments(uint16_t value) {
            /* Given a value in milliseconds, rates your reaction time */
  if (value > 2000) {
    usart_print_string("---->  Ummm...this is a reaction timer...\r\n");
  }
  else if (value > 1000) {
    usart_print_string("---->  Hello?\r\n");
  }
  else if (value > 500) {
    usart_print_string("---->  Slow.\r\n");
  }
  else if (value > 250) {
    usart_print_string("---->  Have another cup of coffee.\r\n");
  }
  else if (value > 200) {
    usart_print_string("---->  Respectable.\r\n");
  }
  else if (value >= 150) {
    usart_print_string("---->  Fast.\r\n");
  }
  else if (value < 150) {
    usart_print_string("---->  Amazing!\r\n");
  }
}

void randomDelay(void) {
                        /* Waits for a "random" delay from 1 - 3.5 sec */
                           /* Requires timer 1 initialized and running */
  /* It's not really random, but very hard to control --
     like coin-flipping. */
  uint8_t randomTime;

  _delay_ms(1000);                              /* wait at least 1 sec */
  randomTime = (uint8_t) TCNT1;
  /* type-casting the 16-bit TCNT1 as an 8-bit number keeps
     only the 8 least-significant (fastest-changing) bits  */
  while (--randomTime) {
    _delay_ms(10);                      /* max value is 255 ~= 2.5 sec */
  }
}
