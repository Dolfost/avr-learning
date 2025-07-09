#ifndef _AVRTOOLS_SPEAKER_H_
#define _AVRTOOLS_SPEAKER_H_

#include <stdint.h>
#include <util/delay.h>

#ifndef SPEAKER
#include <avr/io.h>
#define SPEAKER_DDR DDRD
#define SPEAKER_PORT PORTD
#define SPEAKER 2
#endif

/**
 * @brief Play a tone iwht a square wave
 *
 * @param period tone period 
 * @param duration tone duration
 */
void play_note(uint16_t period, uint16_t duration);

#endif // !_AVRTOOLS_SPEAKER_H_
