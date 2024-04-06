#pragma once
#ifndef __SONOVOLT_PICO_CLOCK_ALARM_H__
#define __SONOVOLT_PICO_CLOCK_ALARM_H__

#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/printf.h"
#include "pico/time.h"
#include "sonovolt/common/time.h"
#include "sonovolt/rp2040/pwm.h"
#include "sonovolt/types.h"
#include <utility>
#include <cmath>
#include <cstdint>

namespace sonovolt::rp2040 {

class ClockAlarm {
private:
  typedef void (*Callback)(u64);

  u64 ticker_ = 0;

  absolute_time_t start_time_ = nil_time;
  int64_t us_per_tick_ = 0u;

  float f_per_tick_ = 0.f;
  float diff_per_tick_ = 0.f;
  float diff_ticker_f = 0.f;

  struct repeating_timer timer_;

  u8 bpm_ = 120;

  u16 PPQN_ = 960;
  u16 PPQN_32_ = PPQN_ / 8_u16;

  bool is_running_ = false;
  bool has_on_tick_cb_ = false;

  Callback on_tick_cb_ = nullptr;

  void update();
public:
  ClockAlarm(u8 bpm) : bpm_(bpm) {}
  ClockAlarm(u8 bpm, u16 ppqn) : bpm_(bpm), PPQN_(ppqn) {}
  ~ClockAlarm();

  void init();

  void start();
  void stop();
  void reset();

  u64 getTicks() const;
  u8 getBPM() const;
  bool isRunning() const;
  int64_t getUsPerTick() const;

  int64_t tick();
  void setBPM(u8 tempo);

  void onTick(Callback &&callback);

  u32 msTimeSinceStart();
  u32 usTimeSinceStart();
};
} // namespace sonovolt::rp2040

#endif // __SONOVOLT_PICO_CLOCK_ALARM_H__
