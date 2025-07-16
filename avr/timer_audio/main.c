#include <avr/io.h>
#include <util/delay.h>
#include "pins.h"
#include <avrtools/scale8.h>

static inline void initTimer(void) {
  TCCR0A |= (1 << WGM01);
  TCCR0A |= (1 << COM0A0);
  TCCR0B |= (1 << CS00) | (1 << CS01);
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT0 = 0;                     /* reset the counter */
  OCR0A = period;                /* set pitch */
  SPEAKER_DDR |= (1 << SPEAKER); /* enable output on speaker */

  while (duration) { /* Variable delay */
    _delay_ms(1);
    duration--;
  }
  SPEAKER_DDR &= ~(1 << SPEAKER); /* turn speaker off */
}

int main(void) {
  // -------- Inits --------- //
  initTimer();
  // ------ Event loop ------ //
  while (1) {
                                                    /* Play some notes */
    playNote(C2, 200);
    playNote(E2, 200);
    playNote(G2, 200);
    playNote(C3, 200);
		playNote(F3, 400);

    // _delay_ms(1000);
    // _delay_ms(1000);
    _delay_ms(1000);

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
