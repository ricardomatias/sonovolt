#pragma once

#include "hardware/gpio.h"
#include "sonovolt/rp2040/debounce.h"
#include "sonovolt/rp2040/time.h"
#include "sonovolt/types.h"

namespace sonovolt::rp2040
{

using rp2040::Debounce;

class Button
{
private:
    uint32_t last_update_ = 0u;
    uint32_t rising_edge_time_ = 0u;
    u8 id_ = 0x0;
    u8 gpio_ = 0x0;
    u8 state_ = 0x00;
    bool updated_ = false;
    bool pull_up_ = false;
    bool prev_state_ = false;

    inline bool readGpio() { return gpio_get(gpio_); }

public:
    Button() = default;
    ~Button() = default;
    Button(const Button &) = delete;
    Button &operator=(const Button &) = delete;
    Button(Button &&) = default;
    Button &operator=(Button &&) = default;

    Button(u8 id, u8 gpio, bool pullUp = false) : id_(id), gpio_(gpio), pull_up_(pullUp) {}

    inline u8 id() const { return id_; }
    inline u8 gpio() const { return gpio_; }

    void init()
    {
        gpio_init(gpio_);

        if(pull_up_)
        {
            printf("pulling up gpio %d\n", gpio_);
            gpio_pull_up(gpio_);
        }
    }


    /**
     * Debounces the input signal to remove noise and ensure stable readings.
     * Based on theory from http://www.ganssle.com/debouncing-pt2.htm
     * Implementation from https://github.com/electro-smith/libDaisy/blob/master/src/hid/switch.cpp
     */
    void debounce()
    {
        uint32_t now = time_ms_32();
        updated_ = false;

        if(now - last_update_ >= 1)
        {
            last_update_ = now;
            updated_ = true;

            // if pulled up: pressed means read is false
            // if pulled down: pressed means read is true

            // shift over, and introduce new state.
            state_ = (state_ << 1) | (!pull_up_ == readGpio());

            if(state_ == 0x7f)
                rising_edge_time_ = now;
        }
    }

    inline bool pressed() const { return state_ == 0xff; }

    inline bool risingEdge() const { return updated_ ? state_ == 0x7f : false; }

    inline bool fallingEdge() const { return updated_ ? state_ == 0x80 : false; }
};

} // namespace sonovolt::rp2040