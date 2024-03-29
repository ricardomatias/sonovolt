#pragma once
#ifndef __SONOVOLT_PICO_TEMPO_CLOCK_H__
#define __SONOVOLT_PICO_TEMPO_CLOCK_H__

#include "pico/time.h"
#include "sonovolt/types.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/printf.h"
#include "sonovolt/common/time.h"
#include "sonovolt/rp2040/pwm.h"
#include <utility>

namespace sonovolt::rp2040
{

class TempoClock
{
private:
    typedef void (*Callback)(u64);

    u64 ticker_ = 0;
    u64 ticks_next_ = PPQN_;

    absolute_time_t start_time_ = nil_time;
    absolute_time_t previous_tick_us_ = nil_time;
    u32 us_per_tick_ = 0u;
    int32_t jitter_ = 0;

    u8 pin_;
    u8 slice_num_;
    u8 slice_channel_;
    u8 bpm_ = 120;

    u16 pwm_wrap_;
    u16 pin_level_;
    u16 PPQN_ = 960;
    u16 tick_off_period_ = ((PPQN_ * 3_u16) / 4_u16);

    bool is_running_ = false;
    bool has_on_tick_cb_ = false;

    Callback on_tick_cb_;

    void update(bool run);

public:
    TempoClock(u8 pin) : pin_(pin) {}
    TempoClock(u8 pin, u8 bpm) : pin_(pin), bpm_(bpm) {}
    TempoClock(u8 pin, u8 bpm, u16 ppqn) : pin_(pin), bpm_(bpm), PPQN_(ppqn)
    {
        tick_off_period_ = ((ppqn * 3_u16) / 4_u16);
    }
    ~TempoClock();

    void init();

    void start();
    void stop();

    u64 getTicks() const;
    u8 getBPM() const;
    bool isRunning() const;

    void tick();
    void setBPM(u8 tempo);

    void onTick(Callback &&callback);

    static void dirtyTick();
};
} // namespace sonovolt::rp2040

// A global variable to allow having a callback called from an PWM IRQ which has access to the TempoClock instance
static sonovolt::rp2040::TempoClock *globalTempoClock = nullptr;

#endif // __SONOVOLT_PICO_TEMPO_CLOCK_H__
