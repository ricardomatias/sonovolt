#include "sonovolt/rp2040/clock_alarm.h"

bool tick_repeating_alarm(struct repeating_timer *t)
{
    auto clockAlarm = static_cast<sonovolt::rp2040::ClockAlarm *>(t->user_data);

    t->delay_us = clockAlarm->tick();

    return clockAlarm->isRunning();
}

namespace sonovolt::rp2040
{

ClockAlarm::~ClockAlarm()
{
#ifdef DEBUG
    printf("ClockAlarm destructor\n");
#endif
}

void ClockAlarm::update(bool run = true)
{
    f_per_tick_ = time::bpm_to_us(bpm_) / static_cast<float>(PPQN_);
    us_per_tick_ = static_cast<int64_t>(f_per_tick_);
    diff_per_tick_ = f_per_tick_ - floorf(f_per_tick_);

#ifdef DEBUG
    printf("ClockAlarm::update() slice_num_=%d, freq=%u\n", slice_num_, freq);
#endif
}

void ClockAlarm::init()
{
    update(false);
}

void ClockAlarm::start()
{
    is_running_ = true;

    add_repeating_timer_us(-us_per_tick_, tick_repeating_alarm, this, &timer_);
}

void ClockAlarm::stop()
{
    cancel_repeating_timer(&timer_);
    is_running_ = false;
}

void ClockAlarm::reset()
{
    ticker_ = 0;
    diff_ticker_f = 0.f;
}

void ClockAlarm::onTick(ClockAlarm::Callback &&callback)
{
    on_tick_cb_ = std::move(callback);
    has_on_tick_cb_ = true;
};

int64_t ClockAlarm::tick()
{
    if(!is_running_)
        return 0;

    if(ticker_ == 0)
    {
        start_time_ = get_absolute_time();
    }
  
    if(has_on_tick_cb_)
        on_tick_cb_(ticker_);

    ticker_++;
    // this adds jitter to the clock
    // to account for the fractional part missing from the repeating timer
    diff_ticker_f += diff_per_tick_ - floorf(diff_ticker_f);

    return -(us_per_tick_ + static_cast<int64_t>((diff_ticker_f)));
}

void ClockAlarm::setBPM(u8 tempo)
{
    if(tempo == bpm_)
        return;

    stop();

    uint32_t ticks_per_sec = (bpm_ * PPQN_) / 60u;
    us_per_tick_ = 1000000u / ticks_per_sec;

    bpm_ = tempo;

    update(false);

    start();
}

uint64_t ClockAlarm::getTicks() const
{
    return ticker_;
}

u8 ClockAlarm::getBPM() const
{
    return bpm_;
}

int64_t ClockAlarm::getUsPerTick() const {
    return us_per_tick_;
}

bool ClockAlarm::isRunning() const
{
    return is_running_;
}

u32 ClockAlarm::msTimeSinceStart() {
    return to_ms_since_boot(get_absolute_time()) - to_ms_since_boot(start_time_);
}

u32 ClockAlarm::usTimeSinceStart() {
    return to_us_since_boot(get_absolute_time()) - to_us_since_boot(start_time_);
}

} // namespace sonovolt::rp2040
