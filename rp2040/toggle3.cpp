#include "sonovolt/rp2040/toggle3.h"

namespace sonovolt::rp2040
{
void Toggle3::init()
{
    button_a_.init();
    button_b_.init();
}


void Toggle3::debounce()
{
    button_a_.debounce();
    button_b_.debounce();
}
} // namespace sonovolt::rp2040