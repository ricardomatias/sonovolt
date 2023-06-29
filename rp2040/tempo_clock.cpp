#include "sonovolt/rp2040/tempo_clock.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/printf.h"
#include "sonovolt/common/time.h"
#include "sonovolt/rp2040/pwm.h"
#include <utility>

void tick_irq_handler()
{
    sonovolt::rp2040::TempoClock::dirtyTick();
}

namespace sonovolt::rp2040
{

TempoClock::~TempoClock()
{
    pwm_set_enabled(slice_num_, false);
    pwm_set_irq_enabled(slice_num_, false);

    irq_clear(PWM_IRQ_WRAP);
    irq_remove_handler(PWM_IRQ_WRAP, tick_irq_handler);

    gpio_deinit(pin_);

#ifdef DEBUG
    printf("TempoClock destructor\n");
#endif
}

void TempoClock::update(bool run = true) {
    auto freq = static_cast<u32>(time::bpm_to_hz(bpm_) * static_cast<float>(PPQN_));
    pin_level_ = pwm_init_freq(slice_num_, slice_channel_, freq, run);

#ifdef DEBUG
    printf("TempoClock::update() slice_num_=%d, freq=%u\n", slice_num_, freq);
#endif
}

void TempoClock::init()
{
    globalTempoClock = static_cast<TempoClock *>(this);

    gpio_set_function(pin_, GPIO_FUNC_PWM);

    slice_num_ = pwm_gpio_to_slice_num(pin_);
    slice_channel_ = pwm_gpio_to_channel(pin_);

    pwm_set_irq_enabled(slice_num_, true);

    irq_set_exclusive_handler(PWM_IRQ_WRAP, tick_irq_handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    update(false);
}

void TempoClock::start()
{
    pwm_set_enabled(slice_num_, true);

    is_running_ = true;
}

void TempoClock::stop()
{
    pwm_set_enabled(slice_num_, false);

    is_running_ = false;
}

extern "C" void TempoClock::dirtyTick()
{
    TempoClock *mySelf = static_cast<TempoClock *>(globalTempoClock);

    if(mySelf == nullptr)
        return;

    // call member
    if(mySelf->isRunning())
        mySelf->tick();
}

void TempoClock::onTick(TempoClock::Callback &&callback)
{
    on_tick_cb_ = std::move(callback);
    has_on_tick_cb_ = true;
};

void TempoClock::tick()
{
    if(!is_running_)
        return;

    if(ticker_ == 0)
    {
        start_time_ = get_absolute_time();
    }
    // else
    // {
    //     jitter_ = absolute_time_diff_us(previous_tick_us_, get_absolute_time()) - us_per_tick_;
    // }

    pwm_clear_irq(slice_num_);

    if(ticker_ >= ticks_next_)
    {
        ticks_next_ += PPQN_;
    }

    if(ticker_ < ticks_next_ - (tick_off_period_ - 1))
    {
        pwm_set_gpio_level(pin_, pin_level_);
    }
    else
    {
        pwm_set_gpio_level(pin_, 0);
    }

    if(has_on_tick_cb_)
        on_tick_cb_(ticker_);

    ticker_++;
    // previous_tick_us_ = get_absolute_time();
}

void TempoClock::setBPM(u8 tempo)
{
    if (tempo == bpm_)
        return;

    stop();

    uint32_t ticks_per_sec = (bpm_ * PPQN_) / 60u;
    us_per_tick_ = 1000000u / ticks_per_sec;

    bpm_ = tempo;

    update();

    start();
}

uint64_t TempoClock::getTicks()
{
    return ticker_;
}

bool TempoClock::isRunning()
{
    return is_running_;
}

} // namespace sonovolt::rp2040