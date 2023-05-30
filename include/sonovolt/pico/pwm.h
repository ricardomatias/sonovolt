#pragma once
#ifndef SONOVOLT_PICO_H
#define SONOVOLT_PICO_H

#include <stdint.h>

namespace sonovolt::pico {
/**
 * @brief Initializes a PWM channel with a given frequency.
 *
 * @param slice_num The PWM slice number to initialize.
 * @param chan The PWM channel number to initialize.
 * @param hz The desired frequency in Hz.
 * @param run Whether to start the PWM running immediately after initialization.
 * @return The wrap value used for the PWM channel.
 */
[[nodiscard]] uint32_t pwm_init_freq(uint8_t slice_num, uint8_t chan, uint32_t hz, bool run = true);
} // namespace sonovolt::pico
#endif