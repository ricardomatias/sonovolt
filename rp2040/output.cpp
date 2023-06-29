#include "sonovolt/rp2040/output.h"

const uint8_t MAX_VOLTAGE = 10;
const uint8_t MIN_VOLTAGE = 0;
const uint32_t PWM_FREQ = 100000;

namespace sonovolt::rp2040
{

Output::Output(uint pin) : pin_(pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);

    slice_num_ = pwm_gpio_to_slice_num(pin);
    slice_channel_ = pwm_gpio_to_channel(pin);

    wrap_count_ = sonovolt::rp2040::pwm_init_freq(slice_num_, pwm_gpio_to_channel(pin), PWM_FREQ);
}
Output::~Output()
{
    gpio_deinit(pin_);
}

void Output::voltage(uint8_t voltage)
{
    uint8_t v = math::clamp(voltage, MIN_VOLTAGE, MAX_VOLTAGE);
    uint16_t duty = static_cast<uint16_t>(wrap_count_ * static_cast<uint32_t>(v) / static_cast<uint32_t>(MAX_VOLTAGE));
    pwm_set_chan_level(slice_num_, slice_channel_, duty);
}

} // namespace sonovolt::rp2040