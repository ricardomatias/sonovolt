#include "sonovolt/rp2040/pwm.h"
#include "hardware/pwm.h"
#include "pico/printf.h"

namespace sonovolt::rp2040 {

[[nodiscard]] uint32_t pwm_init_freq(uint8_t slice_num, uint8_t chan, uint32_t hz, bool run) {
    // 125mhz
    auto clock = 125000000u;
    auto divider16 = clock / hz / 4096 + (clock % (hz * 4096) != 0);

    if (divider16 / 16 == 0) divider16 = 16;
    
    uint32_t wrap = clock * 16 / divider16 / hz - 1;

    auto integer = divider16 / 16;
    auto fraction = divider16 & 0xF;

    pwm_config config = pwm_get_default_config();

    printf("pwm_init_freq: slice_num=%d, chan=%d, hz=%d, divider16=%d, wrap=%d, integer=%d, fraction=%d\n", slice_num, chan, hz,
           divider16, wrap, integer, fraction);
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv_int_frac(&config, integer, fraction);
    pwm_config_set_wrap(&config, wrap);
    // pwm starts running when configured
    pwm_init(slice_num, &config, run);

    return wrap;
}
} // namespace sonovolt::rp2040