#include "sonovolt/common/time.h"

namespace sonovolt {
namespace time {

/**
 * @brief Converts beats per minute (BPM) to Hertz (Hz).
 *
 * @param bpm The value in BPM to convert to Hz.
 * @return The converted value in Hz.
 */
float bpm_to_hz(uint8_t bpm) { return ((float)bpm / 60.f); }

} // namespace time
} // namespace sonovolt