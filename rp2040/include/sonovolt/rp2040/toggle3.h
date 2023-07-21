#pragma once

#include "hardware/gpio.h"
#include "sonovolt/rp2040/switch.h"
#include "sonovolt/rp2040/debounce.h"
#include "sonovolt/rp2040/time.h"
#include "sonovolt/types.h"

namespace sonovolt::rp2040
{

class Toggle3
{
private:
    u8 id_ = 0x0;

    Switch button_a_;
    Switch button_b_;

public:
    Toggle3() = default;
    ~Toggle3() = default;
    Toggle3(const Toggle3 &) = delete;
    Toggle3 &operator=(const Toggle3 &) = delete;
    Toggle3(Toggle3 &&) = default;
    Toggle3 &operator=(Toggle3 &&) = default;

    Toggle3(u8 id, u8 pinA, u8 pinB, bool pullUp = false)
    : id_(id), button_a_(0u, pinA, pullUp), button_b_(1u, pinB, pullUp)
    {
    }

    enum class Toggle3State
    {
        Top,
        Middle,
        Bottom,
        RisingEdge,
        FallingEdge
    };

    void init();
    void debounce();

    inline u8 id() const { return id_; }

    inline Toggle3State read() const
    {
        auto sw1 = button_a_.pressed();
        auto sw2 = button_b_.pressed();

        // printf("sw1: %d, sw2: %d\n", sw1, sw2);

        if(!sw1 && !sw2)
        {
            return Toggle3State::Middle;
        }
        else if(sw1 && !sw2)
        {
            return Toggle3State::Top;
        }
        else if(!sw1 && sw2)
        {
            return Toggle3State::Bottom;
        }
    }

    bool onTop() const { return button_a_.risingEdge(); }
    bool onMiddle() const { return button_a_.fallingEdge() || button_b_.fallingEdge(); }
    bool onBottom() const { return button_b_.risingEdge(); }
};

} // namespace sonovolt::rp2040

// bool onTop() const
// {
//     if(button_a_.risingEdge())
//     {
//         return read() == Toggle3State::Top;
//     }
//     return false;
// }
// bool onMiddle() const
// {
//     if(button_a_.fallingEdge() || button_b_.fallingEdge())
//     {
//         return read() == Toggle3State::Middle;
//     }
//     return false;
// }
// bool onBottom() const
// {
//     if(button_b_.risingEdge())
//     {
//         return read() == Toggle3State::Bottom;
//     }
//     return false;
// }