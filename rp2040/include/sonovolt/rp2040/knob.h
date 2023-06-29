#pragma once

#include "hardware/adc.h"
#include "pico/printf.h"

// Add pickup value functionality, so that it only changes once it crosses over the previous value
class Knob
{
private:
    /* data */
    uint8_t pin_;
    float prev_ = 0.f;
    float current_ = 0.f;

public:
    const float voltage_factor = 3.3f / (1 << 12);

    Knob() = default;
    ~Knob() = default;
    Knob(const Knob &) = delete;
    Knob &operator=(const Knob &) = delete;
    Knob(Knob &&) = default;
    Knob &operator=(Knob &&) = default;
    Knob(uint8_t adc_pin) : pin_(adc_pin) {}

    void init()
    {
        adc_gpio_init(pin_);
        // capture first value
        prepare();
        read();
    }

    float read()
    {
        prev_ = current_;
        current_ = readRaw();
        return current_;
    }

    bool changed() { return abs(current_ - prev_) > 1e-2f; }

    void prepare()
    {
        // ADC is numbered between 0 - 3 for pins 26 - 29
        adc_select_input(pin_ % 26u);
    }

    inline uint16_t readRaw() const { return adc_read(); }
};
