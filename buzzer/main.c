#include <avr/io.h>
#include <util/delay.h>

#define BUZZ_DDR DDRD
#define BUZZ_PORT PORTD
#define BUZZ_PIN_L PD0
#define BUZZ_PIN_R PD1
#define LED_DDR DDRB
#define LED_PORT PORTB

void delay_us(uint16_t us) {
  while (--us)
    _delay_us(1);
}

void tone(uint32_t len_ms, uint32_t freq_hz) {
  uint32_t period_us = 1000000 / freq_hz;
  for (uint8_t byte = 0; byte < sizeof(uint32_t); byte++) {
  	LED_PORT = period_us >> byte*8;
		_delay_ms(1);
  }
  for (uint32_t elapsed = 0; elapsed <= 100 * len_ms; elapsed += period_us) {
    BUZZ_PORT ^= _BV(BUZZ_PIN_L) | _BV(BUZZ_PIN_R);
    // this crap wont reproduce correct frequencies even with the _delay_us
    // hardcoded. damn it
    delay_us(period_us);
  }
}

int main(void) {
  BUZZ_DDR |= _BV(BUZZ_PIN_L) | _BV(BUZZ_PIN_R);
  LED_DDR = 0xff;

	// nyan cat
  while (1) {
    _delay_ms(2000);
    tone(200, 4199);
    tone(200, 4345);
    tone(100, 4008);
    tone(100, 4008);
    _delay_ms(100);
    tone(100, 3800);
    tone(100, 3951);
    tone(100, 3898);
    tone(100, 3800);
    _delay_ms(100);
    tone(200, 3800);
    tone(200, 3898);
    tone(200, 3951);
    tone(100, 3951);
    tone(100, 3898);
    tone(100, 3800);
    tone(100, 3898);
    tone(100, 4008);
    tone(100, 4199);
    tone(100, 4345);
    tone(100, 4008);
    tone(100, 4199);
    tone(100, 3898);
    tone(100, 4008);
    tone(100, 3800);
    tone(100, 3898);
    tone(100, 3800);
    tone(200, 4008);
    tone(200, 4199);
    tone(100, 4345);
    tone(100, 4008);
    tone(100, 4199);
    tone(100, 3898);
    tone(100, 4008);
    tone(100, 3800);
    tone(100, 3951);
    tone(100, 4008);
    tone(100, 3951);
    tone(100, 3898);
    tone(100, 3800);
    tone(100, 3898);
    tone(200, 3951);
    tone(100, 3800);
    tone(100, 3898);
    tone(100, 4008);
    tone(100, 4199);
    tone(100, 3898);
    tone(100, 4008);
    tone(100, 3898);
    tone(100, 3800);
    tone(200, 3898);
    tone(200, 3800);
    tone(200, 3898);
    tone(200, 3800);
  }

  return 0;
}
