#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#define DELAYTIME 85 
#define LED_PORT PORTB
#define LED_DDR DDRB

int main(void) {
  // clock_prescale_set(clock_div_8);
  uint8_t i;
  uint8_t repetitions;
  uint8_t whichLED;
  uint16_t randomNumber = 0x1234;
  LED_DDR = 0xff;

  while (1) {
    /* Go Left */
    for (i = 0; i < 8; i++) {
      LED_PORT |= (1 << i); /* turn on the i'th pin */
      _delay_ms(DELAYTIME); /* wait */
    }
    for (i = 0; i < 8; i++) {
      LED_PORT &= ~(1 << i); /* turn off the i'th pin */
      _delay_ms(DELAYTIME);  /* wait */
    }
    _delay_ms(5 * DELAYTIME); /* pause */
    /* Go Right */
    for (i = 7; i < 255; i--) {
      LED_PORT |= (1 << i); /* turn on the i'th pin */
      _delay_ms(DELAYTIME); /* wait */
    }
    for (i = 7; i < 255; i--) {
      LED_PORT &= ~(1 << i); /* turn off the i'th pin */
      _delay_ms(DELAYTIME);  /* wait */
    }
    _delay_ms(5 * DELAYTIME); /* pause */
    /* Toggle "random" bits for a while */
    for (repetitions = 0; repetitions < 75; repetitions++) {
      /* "random" number generator */
      randomNumber = 2053 * randomNumber + 13849;
      /* low three bits from high byte */
      whichLED = (randomNumber >> 8) & 0b00000111;
      LED_PORT ^= (1 << whichLED);
      _delay_ms(DELAYTIME);
    }
    LED_PORT = 0;
    _delay_ms(5 * DELAYTIME); /* toggle our LED */
    /* all LEDs off */
    /* pause */
  } /* End event loop */
  return (0); /* This line is never reached */
}
