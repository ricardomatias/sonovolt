#pragma once
#ifndef SONOVOLT_MATH_H
#define SONOVOLT_MATH_H
#include <cstdint>
#include <type_traits>

namespace sonovolt::math
{
/**
 * Maps a value from one range to another.
 *
 * @param v The value to map.
 * @param a1 The lower bound of the input range.
 * @param a2 The upper bound of the input range.
 * @param b1 The lower bound of the output range.
 * @param b2 The upper bound of the output range.
 * @return The mapped value.
 */
template <typename T>
T map(T s, T a1, T a2, T b1, T b2)
{
    static_assert(std::is_integral<T>::value, "Must be a number.");
    return b1 + (b2 - b1) * ((s - a1) / (a2 - a1));
}

/**
 * Calculates the number of leading zeros in a binary representation of a number.
 *
 * @param number The number to calculate the leading zeros for.
 * @return The number of leading zeros in the binary representation of the number.
 */
uint8_t zero_count(uint8_t number);

/**
 * Wraps a value within a range of 0 to max.
 *
 * @param v The value to wrap.
 * @param max The maximum value of the range.
 * @return The wrapped value.
 */
template <typename T>
T wrap(T v, T max)
{
    static_assert(std::is_integral<T>::value, "Must be a number.");
    return ((v % max) + max) % max;
}

/**
 * Returns the maximum value between two values.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @return The maximum value between a and b.
 */
template <typename T>
T max(T a, T b)
{
    static_assert(std::is_integral<T>::value, "Must be a number.");
    return a > b ? a : b;
}

/**
 * Returns the minimum value between two values.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @return The minimum value between a and b.
 */
template <typename T>
T min(T a, T b)
{
    static_assert(std::is_integral<T>::value, "Must be a number.");
    return a < b ? a : b;
}

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}


} // namespace sonovolt::math

#endif // SONOVOLT_MATH_H