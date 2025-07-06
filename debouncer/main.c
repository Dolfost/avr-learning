#include "pins.h"
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

#define NOTE_DURATION 0xF000

void transmit_byte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}
uint8_t receive_byte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}
void print_string(const char str[]) {
  uint8_t i = 0;
  while (str[i]) {
    transmit_byte(str[i]);
    i++;
  }
}
void play_note(uint16_t period, uint16_t duration) {
  uint16_t elapsed;
  uint16_t i;
  for (elapsed = 0; elapsed < duration; elapsed += period) {
                     /* For loop with variable delay selects the pitch */
    for (i = 0; i < period; i++) {
      _delay_us(1);
    }
    SPEAKER_PORT ^= (1 << SPEAKER);
  }
}

void send(char byte) { 
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = byte;
}

uint8_t debounce(uint8_t byte, uint8_t bit) { 
	if (!(byte & (1 << bit))) { 
		_delay_us(1000);
		if (!(byte & (1 << bit))) 
			return 1;
	}
	return 0;
}
#define DEBOUNCE(WHAT) debounce(WHAT##_PIN, WHAT)

int main(void) {
#ifdef DEBUG
	// USART init
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A |= (1 << U2X0);
	// Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
#endif

  SPEAKER_DDR |= (1 << SPEAKER);

	LED_DDR = 0xff;
	LED_PORT = 0b11000011;

  BUTTON_DDR &= ~(1 << BUTTON);
  BUTTON_PORT |= (1 << BUTTON);
	uint8_t button_was_pressed = 0;

  while (1) {
		if (DEBOUNCE(BUTTON)) { 
#ifdef DEBUG 
			print_string("debounced\r\n");
#endif
			if (button_was_pressed == 0) {
				LED_PORT = ~LED_PORT;
				play_note(100, 10000);
				button_was_pressed = 1;
#ifdef DEBUG 
				print_string("press\r\n");
#endif
			}
		} else { 
			button_was_pressed = 0;
		}
	}
	return 0;
}
