/*=========================================================================
 
  Pico7219

  pico7219.c

  A low-level driver for chained display modules based on the MAX7219.
  See the corresponding header file for a description of how the 
  functions are used. If this library is built in "host" mode, the 
  actual GPIO operations are replaced by printouts of the pins of the
  operations that would be carried out.

  Copyright (c)2021 Kevin Boone, GPL v3.0

  =========================================================================*/
#include <stdlib.h>
#include <string.h>

#include "hardware/spi.h"
#include "hardware/gpio.h"

#include "sonovolt/rp2040/pico7219.h"
#include "sonovolt/rp2040/font_8.h"
#include "sonovolt/common/bit.h"

namespace sonovolt::rp2040
{

#define PICO7219_INTENSITY_REG 0x0A
#define PICO7219_SHUTDOWN_REG 0x0C

void Max7219::setChipSelect(uint8_t select)
{
    // This is likely done to add a small delay to the function,
    // which can help ensure that the chip select pin is set correctly.
    asm volatile("nop \n nop \n nop");
    gpio_put(cs_, select);
    asm volatile("nop \n nop \n nop");
}

void Max7219::writeWordToChain(uint8_t hi, uint8_t lo)
{
    setChipSelect(0);
    uint8_t buf[] = {hi, lo};

    for(int i = 0; i < chain_len_; i++)
        spi_write_blocking(spi_, buf, 2);

    setChipSelect(1);
}

void Max7219::setVirtualChainLength(int chain_len)
{
    if(vdata_)
        free(vdata_);
    vdata_ = static_cast<uint8_t *>(malloc(PICO7219_ROWS * chain_len));
    memset(vdata_, 0, PICO7219_ROWS * chain_len);
    vchain_len_ = chain_len;
}

void Max7219::init(uint8_t mosi, uint8_t sck, int32_t baud)
{
    // Start with the virtual chain length the same as the maximum
    //  physical chain length
    setVirtualChainLength(chain_len_);
    // Set data buffer to all "off", as that's how the LEDs power up
    memset(data_, 0, sizeof(data_));
    // Set all data clean
    memset(row_dirty_, 0, sizeof(row_dirty_));

    switch(spi_num_)
    {
        case PICO_SPI_0: spi_ = spi0; break;
        case PICO_SPI_1: spi_ = spi1; break;
    }

    // Initialize the SPI and GPIO
    spi_init(spi_, baud);

    gpio_set_function(mosi, GPIO_FUNC_SPI);
    gpio_set_function(sck, GPIO_FUNC_SPI);

    gpio_init(cs_);
    gpio_set_dir(cs_, GPIO_OUT);
    gpio_put(cs_, 1);

    // Initialize the hardware
    initHardware();
}

/* init() sends the same set of initialization values to all modules
   in the chain. We write zero to all the row buffers, and set
   reasonable values for the control registers. */
void Max7219::initHardware()
{
    // Rows
    writeWordToChain(0x00, 0x00);
    writeWordToChain(0x01, 0x00);
    writeWordToChain(0x02, 0x00);
    writeWordToChain(0x03, 0x00);
    writeWordToChain(0x04, 0x00);
    writeWordToChain(0x05, 0x00);
    writeWordToChain(0x06, 0x00);
    writeWordToChain(0x07, 0x00);
    writeWordToChain(0x08, 0x00);
    // Control registers
    writeWordToChain(0x09, 0x00); // Decode mode
    writeWordToChain(PICO7219_INTENSITY_REG, 0x01);
    writeWordToChain(0x0b, 0x07);                  // scan limit = full
    writeWordToChain(PICO7219_SHUTDOWN_REG, 0x01); // Run
    writeWordToChain(0x0f, 0x00);                  // Display test = off
}

/** pico7219_destroy() */
void Max7219::destroy(bool deinit)
{
    if(vdata_)
        free(vdata_);
    writeWordToChain(PICO7219_SHUTDOWN_REG, 0x00); // off
    if(deinit)
    {
        spi_deinit(spi_);
    }
}

/** pico7219_set_row_bits(). */
void Max7219::setRowBits(uint8_t row, const uint8_t bits[PICO7219_MAX_CHAIN])
{
    setChipSelect(0);
    int chain_len = chain_len_;
    for(int i = 0; i < chain_len; i++)
    {
        uint8_t v = bits[chain_len - i - 1];
        if(reverse_bits_)
            v = sonovolt::bit::reverseBits(v);
        uint8_t buf[] = {(int)row + 1, v};
        spi_write_blocking(spi_, buf, 2);
    }
    setChipSelect(1);
}

/** pico7219_switch_off_row() */
void Max7219::switchOffRow(uint8_t row, bool shouldFlush)
{
    row_dirty_[row] = 1u;
    //fprintf (stderr, "row = %d len=%d\n", row, vchain_len_);
    memset(vdata_ + row * vchain_len_, 0x0, vchain_len_);

    if(shouldFlush)
        flush();
}

/** pico7219_switch_off_all() */
void Max7219::switchOffAll(bool shouldFlush)
{
    for(int i = 0; i < PICO7219_ROWS; i++)
        switchOffRow(i, 0u);
    if(shouldFlush)
        flush();
}

/** pico7219_switch_on_row() */
void Max7219::switchOnRow(uint8_t row, bool shouldFlush)
{
    row_dirty_[row] = 1u;
    memset(vdata_ + row * vchain_len_, 0xFF, vchain_len_);
    if(shouldFlush)
        flush();
}

/** pico7219_switch_on_all() */
void Max7219::switchOnAll(bool shouldFlush)
{
    for(int i = 0; i < PICO7219_ROWS; i++)
        switchOnRow(i, 0u);
    if(shouldFlush)
        flush();
}

/** pico7219_switch_on() */
void Max7219::switchOn(uint8_t row, uint8_t col, bool shouldFlush)
{
    if(row < PICO7219_ROWS && col < PICO7219_COLS * vchain_len_)
    {
        int block = col / 8;
        int pos = col - 8 * block;
        uint8_t v = 1 << pos;
        vdata_[row * vchain_len_ + block] |= v;
        row_dirty_[row] = 1u;
        if(shouldFlush)
            flush();
    }
}

/** pico7219_switch_off() */
void Max7219::switchOff(uint8_t row, uint8_t col, bool shouldFlush)
{
    if(row < PICO7219_ROWS && col < PICO7219_COLS * vchain_len_)
    {
        int block = col / 8;
        int pos = col - 8 * block;
        uint8_t v = 1 << pos;
        vdata_[row * vchain_len_ + block] &= ~v;
        row_dirty_[row] = 1u;

        if(shouldFlush)
            flush();
    }
}

void Max7219::vrowToVrow(size_t row)
{
    int target_mods = chain_len_;
    if(target_mods > vchain_len_)
        target_mods = vchain_len_;
    int row_start = row * vchain_len_;
    for(int i = 0; i < target_mods; i++)
    {
        data_[row][i] = vdata_[row_start + i];
    }
}

/** Scroll one pixel left. */
void Max7219::scroll(bool wrap)
{
    int target_mods = chain_len_;
    if(target_mods > vchain_len_)
        target_mods = vchain_len_;

    // Shift bits in vdata
    // This logic is twisted because the bits are in MSB-LSB order in the
    //   opposite order from the modules. So when we shift a bit rightwards
    //   off the end of one module, it appears as the MSB in the next, not
    //   the LSB.
    for(int row = 0; row < PICO7219_ROWS; row++)
    {
        int row_start = row * vchain_len_;
        uint8_t carry = 0;
        int l = vchain_len_ - 1;
        for(int i = l; i >= 0; i--)
        {
            int row_offset = row_start + i;
            bool carry_next = 0u;

            if(vdata_[row_offset] & 0x01)
                carry_next = 1u;
            vdata_[row_offset] >>= 1;

            // If we're at position 0, and the shift would carry, we have to
            //   carry to position "-1" which, of course, does not exist. So,
            //   instead, we carry to position l, that is, to the far end of
            //   the chain.
            if(wrap)
            {
                if(i == 0 && carry_next)
                    vdata_[row_start + l] |= 0x80;
            }

            vdata_[row_offset] |= carry;
            carry = 0;

            if(carry_next)
                carry = 0x80;
        }

        setRowBits(row, vdata_ + row * vchain_len_);
    }
}

void Max7219::drawCharacter(uint8_t chr, int x_offset, bool shouldFlush)
{
    for(int i = 0; i < 8; i++) // row
    {
        // The font elements are one byte wide even though, as its an 8x5 font,
        //   only the top five bits of each byte are used.
        uint8_t v = rp2040::font8::kTable[8 * chr + i];
        
        for(int j = 0; j < 8; j++) // column
        {
            int sel = 1 << j;
            
            if(sel & v)
                switchOn(7 - i, 7 - j + x_offset, false);
        }
    }

    if(shouldFlush)
        flush();
}


void Max7219::drawString(const char *s, int index, bool shouldFlush)
{
    int x = index;
    while(*s)
    {
        drawCharacter(*s - ' ', x, false);
        s++;
        x += 7;
    }
    if(shouldFlush)
        flush();
}

size_t Max7219::getStringLengthPixels(const char *s)
{
    return strlen(s) * 7;
}

uint8_t Max7219::getStringLengthModules(const char *s)
{
    return getStringLengthPixels(s) / 8 + 1;
}


void Max7219::flush()
{
    for(size_t i = 0; i < PICO7219_ROWS; i++)
    {
        vrowToVrow(i);
        if(row_dirty_[i])
            setRowBits(i, data_[i]);
        row_dirty_[i] = 0u;
    }
}

/** pico7219_set_intensity() */
void Max7219::setIntensity(uint8_t intensity)
{
    writeWordToChain(PICO7219_INTENSITY_REG, intensity);
}

} // namespace sonovolt::rp2040
