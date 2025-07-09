#include "pins.h"
#include "scale16.h"

#include <avr/io.h>
#include <stdlib.h>
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

#define SONG_LENGTH  (sizeof(song) / sizeof(uint16_t))

int main(void) {
  const uint16_t song[] = {
    E6, E6, E6, C6, E6, G6, G5,
    C6, G5, E5, A5, B5, Ax5, A5,
    G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
    C6, G5, E5, A5, B5, Ax5, A5,
    G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
                                                                /* etc */
  };
  /* starting at end b/c routine starts by incrementing and then playing
     this makes the song start at the beginning after reboot */
  uint8_t whichNote = SONG_LENGTH - 1;
  uint8_t wasButtonPressed = 0;

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
#ifdef DEBUG 
	char str[6 + 5 + 1] = "note: ";
	char num[5 + 1];
	uint8_t shown = 0;
#endif

  while (1) {
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {
      if (!wasButtonPressed) {
        whichNote++;
        if (whichNote == SONG_LENGTH)
          whichNote = 0;
        wasButtonPressed = 1;
				LED_PORT = ~LED_PORT;
#ifdef DEBUG 
				shown = 0;
#endif
      }
      play_note(song[whichNote], 1600);
#ifdef DEBUG 
			if (shown == 0) {
				itoa(song[whichNote], str + 6, 10);
				itoa(whichNote, num, 10);
				print_string(num);
				print_string("th :");
				print_string(str);
				print_string("1/1e6Hz\r\n");
				shown = 1;
			}
#endif
    }
    else {
      wasButtonPressed = 0;
    }
  }                                                  /* End event loop */
  return 0;
}
