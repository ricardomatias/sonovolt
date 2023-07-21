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
    uint32_t wrap_count_;
    uint pin_;
    uint8_t slice_num_;
    uint8_t slice_channel_;

  public:
    Output(uint pin);
    ~Output();

    void init();
    void voltage(uint8_t voltage);
};
} // namespace sonovolt::rp2040

#endif