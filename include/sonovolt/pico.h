#ifndef SONOVOLT_PICO_H
#define SONOVOLT_PICO_H

#include <stdint.h>

uint32_t pwm_set_freq_duty(uint8_t slice_num, uint8_t chan, uint32_t hz, uint8_t duty);

#endif