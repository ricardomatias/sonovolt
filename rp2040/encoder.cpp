#include "sonovolt/rp2040/encoder.h"

namespace sonovolt::rp2040
{
void Encoder::init()
{
    pio_add_program(pio_, &encoder_program);
    encoder_program_init(pio_, sm, pin_, 2);
}

int8_t Encoder::read()
{
    // note: thanks to two's complement arithmetic delta will always
    // be correct even when new_value wraps around MAXINT / MININT
    new_value = encoder_get_count(pio_, sm);
    delta = new_value - old_value;

    if(abs(delta) >= 4)
    {
        old_value = new_value;
    } else {
        delta = 0;
    }

    return math::sign(delta);
}
} // namespace sonovolt::rp2040
