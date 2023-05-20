#pragma once
#ifndef SONOVOLT_TIME_H
#define SONOVOLT_TIME_H

#include <stdint.h>

namespace sonovolt {
namespace time {
float bpm_to_hz(uint8_t bpm);
}
} // namespace sonovolt

#endif // SONOVOLT_TIME_H
