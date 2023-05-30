#include "sonovolt/common/time.h"

namespace sonovolt::time {

float bpm_to_hz(uint8_t bpm) { return ((float)bpm / 60.f); }

} // namespace sonovolt