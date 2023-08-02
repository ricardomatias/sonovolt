#include "sonovolt/rp2040/gate_in.h"

namespace sonovolt::rp2040
{

void GateIn::init()
{
    gpio_init(pin_);
    gpio_set_dir(pin_, GPIO_IN);
    gpio_pull_down(pin_);

    gpio_set_irq_enabled(pin_, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
}

bool GateIn::trig()
{
    // Inverted because of typical BJT input circuit.
    prev_state_ = state_;
    state_ = invert_ ? !gpio_get(pin_) : gpio_get(pin_);
    return state_ && !prev_state_;
}
} // namespace sonovolt::rp2040
