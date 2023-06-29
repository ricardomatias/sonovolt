#pragma once
#ifndef SONOVOLT_PICO_TIME_H
#define SONOVOLT_PICO_TIME_H

#include "pico/time.h"

namespace sonovolt::rp2040
{
static uint32_t time_ms_32()
{
    return time_us_32() / 1000u;
}

} // namespace sonovolt::rp2040

#endif