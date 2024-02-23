#include "sonovolt/common/time.h"

namespace sonovolt::time
{

float bpm_to_hz(uint8_t bpm)
{
    return (static_cast<float>(bpm) / 60.f);
}

float hz_to_us(float hz)
{
    return (1.f / hz) * 1000000.f;
}

float bpm_to_us(uint8_t bpm)
{
    return 60000000.f / static_cast<float>(bpm);
}

// 1041,6666666667

} // namespace sonovolt::time
