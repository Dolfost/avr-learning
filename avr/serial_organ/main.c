#include "organ.h"
#include "scale16.h"
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

int main(void) {
	// USART init
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A |= (1 << U2X0);
	// Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit

  SPEAKER_DDR |= (1 << SPEAKER_PIN);
  print_string("----- Serial Organ ------\r\n");

  char fromCompy; /* used to store serial input */
  uint16_t currentNoteLength = NOTE_DURATION / 2;
  const uint8_t keys[] = {'a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y',
                          'h', 'j', 'i', 'k', 'o', 'l', 'p', ';', '\'', 'x'};
  const uint16_t notes[] = {G4, Gx4, A4,  Ax4, B4,  C5, Cx5, D5, Dx5,
                            E5, F5,  Fx5, G5,  Gx5, A5, Ax5, B5, C6, 125 /* x = 8kHz */};
  uint8_t isNote;
  uint8_t i;

  while (1) {
    fromCompy = receive_byte();
		LED_PORT = fromCompy;
    transmit_byte('N');

    isNote = 0;
    for (i = 0; i < sizeof(keys); i++) {
      if (fromCompy == keys[i]) {
        play_note(notes[i], currentNoteLength);
        isNote = 1;
        break;
      }
    }

    if (!isNote) {
      if (fromCompy == '[') {
        currentNoteLength = NOTE_DURATION / 2;
      } else if (fromCompy == ']') {
        currentNoteLength = NOTE_DURATION;
      } else {
        rest(currentNoteLength);
      }
    }
  }
  return 0;
}
