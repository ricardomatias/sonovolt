#pragma once
#ifndef SONOVOLT_MATH_H
#define SONOVOLT_MATH_H
#include <cstdint>

namespace sonovolt::math {
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
template <typename T> T map(T v, T a1, T a2, T b1, T b2);

/**
 * Clamps the given value between the minimum and maximum values.
 *
 * @param v The value to clamp.
 * @param min The minimum value to clamp to.
 * @param max The maximum value to clamp to.
 * @return The clamped value.
 */
template <typename T> T clamp(T v, T min, T max);
} // namespace sonovolt

#endif // SONOVOLT_MATH_H