#include "sonovolt/pico/pwm.h"
#include "hardware/pwm.h"

namespace sonovolt::pico {

[[nodiscard]] uint32_t pwm_init_freq(uint8_t slice_num, uint8_t chan, uint32_t hz, bool run) {
    // 125mhz
    uint32_t clock = 125000000;
    uint32_t divider16 = (clock + hz * 2048) / (hz * 4096);

    if (divider16 / 16 == 0) divider16 = 16;

    uint32_t wrap = clock * 16 / divider16 / hz - 1;

    pwm_config config = pwm_get_default_config();

    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv_int_frac(&config, divider16 / 16, divider16 & 0xF);
    pwm_config_set_wrap(&config, wrap);
    // pwm starts running when configured
    pwm_init(slice_num, &config, run);

    return wrap;
}
} // namespace sonovolt::pico