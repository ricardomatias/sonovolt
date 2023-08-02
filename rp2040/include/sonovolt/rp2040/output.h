#pragma once
#ifndef SONOVOLT_OUTPUT_H
#define SONOVOLT_OUTPUT_H

#include "pico/printf.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "sonovolt/types.h"
#include "sonovolt/common/math.h"
#include "sonovolt/rp2040/pwm.h"
#include <cstdint>
#include <algorithm>

namespace sonovolt::rp2040
{
class Output
{
private:
    u8 id_ = 0x0;
    uint8_t slice_num_;
    uint8_t slice_channel_;
    uint pin_;
    uint32_t wrap_count_;
public:
    Output(uint id, uint pin) : id_(id), pin_(pin) {}
    ~Output();

    Output(const Output &) = delete;
    Output(Output &&) = default;
    Output &operator=(const Output &) = delete;
    Output &operator=(Output &&) = delete;

    void init();
    void voltage(uint8_t voltage);
};
} // namespace sonovolt::rp2040

#endif