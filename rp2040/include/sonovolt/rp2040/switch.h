#pragma once

#include "hardware/gpio.h"
#include "sonovolt/rp2040/debounce.h"
#include "sonovolt/rp2040/time.h"
#include "sonovolt/types.h"

namespace sonovolt::rp2040
{

class Switch
{
private:
    uint32_t last_update_ = 0u;
    uint32_t rising_edge_time_ = 0u;
    u8 id_ = 0x0;
    u8 gpio_ = 0x0;
    u8 state_ = 0x0;
    bool updated_ = false;
    bool pull_up_ = false;
    bool prev_state_ = false;

    inline bool readGpio() { return gpio_get(gpio_); }

public:
    Switch() = default;
    ~Switch() = default;
    Switch(const Switch &) = delete;
    Switch &operator=(const Switch &) = delete;
    Switch(Switch &&) = default;
    Switch &operator=(Switch &&) = default;

    Switch(u8 id, u8 gpio, bool pullUp = false) : id_(id), gpio_(gpio), pull_up_(pullUp) {}

    inline u8 id() const { return id_; }
    inline u8 gpio() const { return gpio_; }

    void init();
    void debounce(uint32_t debounceTimeMs = 1);

    inline bool readRaw() { return readGpio() && !pull_up_; }

    inline bool pressed() const { return state_ == 0xff; }

    inline bool risingEdge() const { return updated_ ? state_ == 0x7f : false; }

    inline bool fallingEdge() const { return updated_ ? state_ == 0x80 : false; }
};

} // namespace sonovolt::rp2040
