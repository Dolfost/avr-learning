
// ------------- Function prototypes -------------- //

// Plays a note for the given duration.  None of these times are
//  calibrated to actual notes or tempi.  It's all relative to TIMEBASE.
#include <stdint.h>

void play_note(uint16_t period, uint16_t duration);

// Does nothing for a time equal to the passed duration.
void rest(uint16_t duration);
