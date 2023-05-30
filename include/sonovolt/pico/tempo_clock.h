#pragma once
#ifndef __SONOVOLT_PICO_TEMPO_CLOCK_H__
#define __SONOVOLT_PICO_TEMPO_CLOCK_H__

#include "../types.h"
#include "pico/time.h"
#include "pw_function/function.h"

namespace sonovolt::pico {

class TempoClock {
  private:
    u8 pin_;
    u8 slice_num_;
    u8 slice_channel_;
    u16 pwm_wrap_;
    u16 pin_level_;

    u8 bpm_ = 120;
    u16 PPQN_ = 960;
    u64 ticker_ = 0;
    u64 ticks_next_ = PPQN_;

    absolute_time_t start_time_ = nil_time;
    absolute_time_t previous_tick_us_ = nil_time;
    u32 us_per_tick_ = 0u;
    int64_t jitter_ = 0;

    bool is_running_ = false;
    bool has_on_tick_cb = false;
    pw::Function<void(u64)> on_tick_cb;

  public:
    TempoClock(u8 pin) : pin_(pin) {}
    TempoClock(u8 pin, u8 bpm) : pin_(pin), bpm_(bpm) {}
    ~TempoClock();

    void init();

    u64 getTicks();
    u8 getBPM();
    bool isRunning();

    void tick();
    void setBPM(u8 tempo);

    void onTick(pw::Function<void(u64)> &&callback);

    static void dirtyTick();
};
} // namespace sonovolt::pico

extern sonovolt::pico::TempoClock *globalTempoClock;

#endif // __SONOVOLT_PICO_TEMPO_CLOCK_H__
