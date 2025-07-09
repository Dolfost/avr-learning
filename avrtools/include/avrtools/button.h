#ifndef _AVRTOOLS_BUTTON_H_
#define _AVRTOOLS_BUTTON_H_

#include <stdint.h>

/**
 * @brief Debounce a button 
 *
 * @param byte byte that contains button bit
 * @param bit button bit number
 * @return 0 if not pressed, 1 if pressed
 */
uint8_t button_debounce(uint8_t byte, uint8_t bit);

#define BUTTON_DEBOUNCE(WHAT) button_debounce(WHAT##_PIN, WHAT)

#endif // !_AVRTOOLS_BUTTON_H_
