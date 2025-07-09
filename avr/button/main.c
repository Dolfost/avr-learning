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

int main(void) {
	// USART init
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A |= (1 << U2X0);
	// Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit

  SPEAKER_DDR |= (1 << SPEAKER);

  BUTTON_R_DDR &= ~(1 << BUTTON_R);
  BUTTON_R_PORT |= (1 << BUTTON_R);

  BUTTON_L_DDR &= ~(1 << BUTTON_L);
  BUTTON_L_PORT |= (1 << BUTTON_L);

  while (1) {
		if (!(BUTTON_L_PIN & (1 << BUTTON_L)) && !(BUTTON_R_PIN & (1 << BUTTON_R))) {
			send('H');
		}else if (!(BUTTON_L_PIN & (1 << BUTTON_L))) {
			play_note(120, 3000);
			LED_PORT = LED_PORT << 1;
			if (LED_PORT == 0)
				LED_PORT = 1;
			send('L');
		} else if (!(BUTTON_R_PIN & (1 << BUTTON_R))) {
			play_note(80, 3000);
			LED_PORT = LED_PORT >> 1;
			if (LED_PORT == 0)
				LED_PORT = 1 << 7;
			send('R');
		}
		_delay_ms(50);
  }
  return 0;
}
