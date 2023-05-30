#include "sonovolt/time/transport.h"

namespace sonovolt::pico {

void Transport::init() {
    uint32_t ticks_per_sec = (bpm * PPQN) / 60u;
    us_per_tick = 1000000u / ticks_per_sec;
}
  
void Transport::tick() { 
  if (ticker == 0) {
    start_time = get_absolute_time();
  } else {
    jitter = absolute_time_diff_us(previous_tick_us, get_absolute_time()) - us_per_tick;
  }

  ticker++;
  previous_tick_us = get_absolute_time();
}

uint64_t Transport::getTicks() { 
  return ticker; 
}

} // namespace sonovolt
