#pragma once
#ifndef SONOVOLT_TRANSPORT_H
#define SONOVOLT_TRANSPORT_H

#include <cstdint>

namespace sonovolt {

class Transport {
  private:
    uint64_t ticker = 0;
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