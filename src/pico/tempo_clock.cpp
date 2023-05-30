#include "sonovolt/pico/tempo_clock.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/printf.h"
#include "pw_function/function.h"
#include "pw_function/pointer.h"
#include "sonovolt/common/time.h"
#include "sonovolt/pico/pwm.h"
#include <utility>

void irq_handler() { sonovolt::pico::TempoClock::dirtyTick(); }

namespace sonovolt::pico {

TempoClock::~TempoClock() {
    pwm_set_enabled(slice_num_, false);
    pwm_set_irq_enabled(slice_num_, false);

    irq_clear(PWM_IRQ_WRAP);
    irq_remove_handler(PWM_IRQ_WRAP, irq_handler);

    gpio_deinit(pin_);

#ifdef DEBUG
    printf("TempoClock destructor\n");
#endif
}

void TempoClock::init() {
    globalTempoClock = static_cast<TempoClock *>(this);

    gpio_set_function(pin_, GPIO_FUNC_PWM);

    slice_num_ = pwm_gpio_to_slice_num(pin_);
    slice_channel_ = pwm_gpio_to_channel(pin_);

    pwm_set_irq_enabled(slice_num_, true);

    irq_set_exclusive_handler(PWM_IRQ_WRAP, irq_handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pin_level_ = pwm_init_freq(slice_num_, slice_channel_, static_cast<u32>(time::bpm_to_hz(bpm_) * static_cast<float>(PPQN_)));

    is_running_ = true;

#ifdef DEBUG
    printf("TempoClock::init() slice_num_=%d\n", slice_num_);
#endif
}

extern "C" void TempoClock::dirtyTick() {
    TempoClock *mySelf = static_cast<TempoClock *>(globalTempoClock);

    if (mySelf == nullptr) return;

    // call member
    mySelf->tick();
}

void TempoClock::onTick(pw::Function<void(u64)> &&callback) {
    on_tick_cb = std::move(callback);
    has_on_tick_cb = true;
};

void TempoClock::tick() {
    if (!is_running_) return;

    if (ticker_ == 0) {
        start_time_ = get_absolute_time();
    } else {
        jitter_ = absolute_time_diff_us(previous_tick_us_, get_absolute_time()) - us_per_tick_;
    }

    pwm_clear_irq(slice_num_);

    if (ticker_ >= ticks_next_) {
        ticks_next_ += PPQN_;
    }

    if (ticker_ < ticks_next_ - ((PPQN_ / 2) - 1)) {
        pwm_set_gpio_level(pin_, pin_level_);
    } else {
        pwm_set_gpio_level(pin_, 0);
    }

    if (has_on_tick_cb) on_tick_cb(ticker_);

    ticker_++;
    previous_tick_us_ = get_absolute_time();
}

void TempoClock::setBPM(u8 tempo) {
    uint32_t ticks_per_sec = (bpm_ * PPQN_) / 60u;
    us_per_tick_ = 1000000u / ticks_per_sec;

    bpm_ = tempo;
}

uint64_t TempoClock::getTicks() { return ticker_; }

bool TempoClock::isRunning() { return is_running_; }

} // namespace sonovolt::pico