#pragma once
#ifndef SONOVOLT_TYPES_H
#define SONOVOLT_TYPES_H

#include <cstdint>
#include <cstddef>

typedef __uint8_t u8;
typedef __uint16_t u16;
typedef __uint32_t u32;
typedef __uint64_t u64;

typedef __int8_t i8;
typedef __int16_t i16;
typedef __int32_t i32;
typedef __int64_t i64;

inline uint8_t operator"" _u8(unsigned long long int value)
{
    return static_cast<uint8_t>(value);
}
inline uint16_t operator"" _u16(unsigned long long int value)
{
    return static_cast<uint16_t>(value);
}
inline uint32_t operator"" _u32(unsigned long long int value)
{
    return static_cast<uint32_t>(value);
}
inline uint64_t operator"" _u64(unsigned long long int value)
{
    return static_cast<uint64_t>(value);
}

inline int8_t operator"" _i8(unsigned long long int value)
{
    return static_cast<int8_t>(value);
}
inline int16_t operator"" _i16(unsigned long long int value)
{
    return static_cast<int16_t>(value);
}
inline int32_t operator"" _i32(unsigned long long int value)
{
    return static_cast<int32_t>(value);
}
inline int64_t operator"" _i64(unsigned long long int value)
{
    return static_cast<int64_t>(value);
}


#endif