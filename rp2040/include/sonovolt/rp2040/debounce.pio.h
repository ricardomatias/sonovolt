// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --------------- //
// button_debounce //
// --------------- //

#define button_debounce_wrap_target 0
#define button_debounce_wrap 10

#define button_debounce_border 6

static const uint16_t button_debounce_program_instructions[] = {
    //     .wrap_target
    0x00c6, //  0: jmp    pin, 6
    0x20a0, //  1: wait   1 pin, 0
    0xe03f, //  2: set    x, 31
    0x00c5, //  3: jmp    pin, 5
    0x0001, //  4: jmp    1
    0x0043, //  5: jmp    x--, 3
    0x2020, //  6: wait   0 pin, 0
    0xe03f, //  7: set    x, 31
    0x00c6, //  8: jmp    pin, 6
    0x0048, //  9: jmp    x--, 8
    0x0001, // 10: jmp    1
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program button_debounce_program = {
    .instructions = button_debounce_program_instructions,
    .length = 11,
    .origin = -1,
};

static inline pio_sm_config
button_debounce_program_get_default_config(uint offset) {
  pio_sm_config c = pio_get_default_sm_config();
  sm_config_set_wrap(&c, offset + button_debounce_wrap_target,
                     offset + button_debounce_wrap);
  return c;
}
#endif
