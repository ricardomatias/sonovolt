#pragma once

#include "pico/rand.h"

namespace sonovolt::rp2040
{


/**
 * @brief Generates a random value between [minimum, maximum]
 *
 * @tparam T The type of the values to generate.
 * @param min The minimum value to generate.
 * @param max The maximum value to generate.
 * @return A random value between the given minimum and maximum values.
 */
template <typename T>
T random(T min, T max)
{
    return min + (static_cast<T>(get_rand_32()) % static_cast<T>(max - min + 1));
}

} // namespace sonovolt::rp2040