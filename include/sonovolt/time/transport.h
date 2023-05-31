#pragma once
#ifndef SONOVOLT_TRANSPORT_H
#define SONOVOLT_TRANSPORT_H

#include "pico/time.h"
#include <cstdint>

namespace sonovolt::pico {

class Transport {
  private:
    uint64_t ticker = 0;
    absolute_time_t start_time = nil_time;
    absolute_time_t previous_tick_us = nil_time;
    uint32_t us_per_tick = 0u;

    void init();

  public:
    int64_t jitter = 0;

    Transport(){};
    ~Transport() {}

    void tick();
    uint64_t getTicks();

    void play();
    void pause();
    void resume();
};

} // namespace sonovolt::pico

#endif