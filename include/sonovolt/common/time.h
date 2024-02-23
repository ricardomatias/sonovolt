#pragma once
#ifndef SONOVOLT_TIME_H
#define SONOVOLT_TIME_H

#include <cstdint>

namespace sonovolt::time {

/**
 * @brief Converts beats per minute (BPM) to Hertz (Hz).
 *
 * @param bpm The value in BPM to convert to Hz.
 * @return The converted value in Hz.
 */
float bpm_to_hz(uint8_t bpm);
float bpm_to_us(uint8_t bpm);
float hz_to_us(float hz);
} // namespace sonovolt::time

#endif // SONOVOLT_TIME_H
