#include <avrtools/speaker.h>

void play_note(uint16_t period, uint16_t duration) {
  uint16_t i;
  for (uint16_t elapsed = 0; elapsed < duration; elapsed += period) {
    for (i = 0; i < period; i++)
      _delay_us(1);
    SPEAKER_PORT ^= (1 << SPEAKER);
  }
}
