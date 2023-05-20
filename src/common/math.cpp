#include "sonovolt/common/math.h"

namespace sonovolt {
namespace math {

int map(int s, int a1, int a2, int b1, int b2) { return b1 + (s - a1) * (b2 - b1) / (a2 - a1); }

} // namespace math
} // namespace sonovolt