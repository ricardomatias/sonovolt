/**
* MIT License
* 
* Copyright (c) 2021 GitJer
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "debounce.pio.h"

namespace sonovolt::rp2040
{

/* 
 * class that debounces gpio using the PIO state machines.
 * up to 8 gpios can be debounced at any one time.
 * the debounce time for each gpio can be set individually, default it is set a 10ms.
 */
class Debounce
{
  public:
    /* 
     * constructor to debounce gpios
     */
    Debounce(void);

    /* 
     * Request to debounce the gpio
     * @param gpio: the gpio that needs to be debounced
     *              the value must be [0, 28] excluding 23, 24 and 25. 
     */
    int debounce_gpio(uint gpio);

    /* 
     * set the debounce time for a gpio
     * @param gpio: the gpio for which the debounce time will be set
     *              the gpio must have previously been debounced using debounce_gpio()
     * @param debounce_time: the float debounce_time in milliseconds in the range [0.5, 30.]
     */
    int set_debounce_time(uint gpio, float debounce_time);

    /* 
     * Read the current value of the debounced the gpio
     * @param gpio: the gpio whose value (low, high) is read
     *              the gpio must have previously been debounced using debounce_gpio()
     */
    int read(uint gpio);

    /* 
     * undebounce (rebounce?) a previously debounced gpio
     * @param gpio: the gpio that is no longer going to be debounced
     *              the gpio must have previously been debounced using debounce_gpio()
     */
    int undebounce_gpio(uint gpio);

  private:
    // the number of instantiated buttons to debounce
    uint num_of_debounced = 0;

    // Note: yes, the below way of doing things is somewhat wastefull, but handy
    // for each gpio indicate if it is debounced
    int gpio_debounced[32];
    // for each gpio the PIO used to debounce
    PIO pio_debounced[32];
    // for each gpio the sm used to debounce
    int sm_debounced[32];
    // for each gpio the location of the pio program in the memory
    int offset[32];
    // for each gpio the configurations of the pio sm
    pio_sm_config conf[32];
    // flags to indicate the pio has already been set (and by which gpio)
    int pio0_already_set, pio1_already_set;
};

} // namespace sonovolt::rp2040