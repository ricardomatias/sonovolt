#include "sonovolt/common/math.h"

namespace sonovolt::math
{
uint8_t zero_count(uint8_t number)
{
    uint8_t res = 0, count = 0;
    while(res < number)
        res = (1 << ++count);
    return count;
}
} // namespace sonovolt::math