#pragma once
#ifndef SONOVOLT_GATE_IN_H
#define SONOVOLT_GATE_IN_H

#include <cstdint>
#include <utility>
#include "pico/stdlib.h"
#include "pico/printf.h"
#include "etl/delegate.h"
#include "etl/delegate_service.h"

namespace sonovolt::rp2040
{
/// @brief A class for gate inputs
class GateIn
{
private:
    uint pin_;
    bool prev_state_ = false;
    bool state_ = false;
    bool invert_ = false;
    bool has_trigger_callback_ = false;
public:
    GateIn(uint pin, bool invert = false) : pin_(pin), invert_(invert) {}
    ~GateIn() = default;

    GateIn(const GateIn&) = delete;
    GateIn& operator=(const GateIn&) = delete;
    GateIn(GateIn&&) = delete;
    GateIn& operator=(GateIn&&) = delete;

    void init();
    bool trig();
};
} // namespace sonovolt::rp2040

#endif