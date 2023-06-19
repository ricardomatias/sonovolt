// MIT License

// Copyright (c) 2022 Infrasonic Audio, LLC

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#ifndef INFS_SDRAM_ALLOC_H
#define INFS_SDRAM_ALLOC_H

#include <atomic>
#include <new>

namespace sonovolt::daisy
{
/**
     * @brief 
     * Provides an interface for monotonic, pseudo-dynamic allocation of memory
     * into Daisy SDRAM.
     * 
     * @details
     * By default statically reserves 32MB of storage in SDRAM for runtime allocation.
     * Due to Daisy's STM32 lacking an MMU, please note that "dynamic" allocations
     * made this way will never actually be reclaimed during program lifetime.
     * 
     * @warning 
     * This only works when built on Daisy platform and does not (yet?)
     * handle allocations beyond the max available memory with anything more
     * than a breakpoint.
     * 
     */
class SDRAM
{
  public:
    template <typename T, class... Args>
    static T* allocate(Args&&... args)
    {
        auto ptr = instance().allocate_raw(sizeof(T), alignof(T));
        return new(ptr) T(std::forward<Args>(args)...);
    }

  private:
    SDRAM() = default;
    ~SDRAM() = default;

    static SDRAM& instance()
    {
        static SDRAM sdram;
        return sdram;
    }

    void* allocate_raw(size_t size, size_t alignment);

    std::atomic_size_t pool_pos_ = {0};
};

} // namespace infrasonic

#endif