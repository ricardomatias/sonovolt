#pragma once

#include "encoder.pio.h"
#include "hardware/pio.h"
#include "pico/printf.h"
#include "sonovolt/common/math.h"
#include "sonovolt/types.h"
#include <cmath>

namespace sonovolt::rp2040
{
class Encoder
{
private:
    PIO pio_ = pio0;
    u8 pin_;
    const u8 sm = 0;
    int32_t new_value = 0;
    int32_t delta = 0;
    int32_t old_value = 0;
    /* data */
public:
    Encoder(u8 pin) : pin_(pin){};
    Encoder() = delete;
    ~Encoder() = default;

    Encoder(const Encoder&) = delete;
    Encoder& operator=(const Encoder&) = delete;
    Encoder(Encoder&&) = default;
    Encoder& operator=(Encoder&&) = delete;

    void init();
    int8_t read();
};
} // namespace sonovolt::rp2040
