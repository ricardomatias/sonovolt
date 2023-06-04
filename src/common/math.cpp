#include "sonovolt/common/math.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

namespace sonovolt::math {

template <typename T> T map(T s, T a1, T a2, T b1, T b2) { return b1 + (s - a1) * (b2 - b1) / (a2 - a1); }
template <typename T> T clamp(T v, T min, T max) { return MAX(MIN(max, v), v); }
template uint8_t clamp(uint8_t v, uint8_t min, uint8_t max);

} // namespace sonovolt