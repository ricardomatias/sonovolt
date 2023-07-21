#include "sonovolt/rp2040/switch.h"

namespace sonovolt::rp2040
{
void Switch::init()
{
    gpio_init(gpio_);

    if(pull_up_)
    {
        printf("pulling up gpio %d\n", gpio_);
        gpio_pull_up(gpio_);
    }
}

/**
 * Debounces the input signal to remove noise and ensure stable readings.
 * Based on theory from http://www.ganssle.com/debouncing-pt2.htm
 * Implementation from https://github.com/electro-smith/libDaisy/blob/master/src/hid/switch.cpp
 */
void Switch::debounce(uint32_t debounceTimeMs)
{
    uint32_t now = time_ms_32();
    updated_ = false;

    if(now - last_update_ >= debounceTimeMs)
    {
        last_update_ = now;
        updated_ = true;

        // if pulled up: pressed means read is false
        // if pulled down: pressed means read is true

        // shift over, and introduce new state.
        state_ = (state_ << 1) | (!pull_up_ == readGpio());

        if(state_ == 0x7f)
            rising_edge_time_ = now;
    }
}
} // namespace sonovolt::rp2040