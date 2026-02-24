#pragma once
#include <iostream>
#include <cstdint>
#include "config.hpp"

class Memory {
    reg_t memory_size;
    byte_t * memory;

    Memory(reg_t size);

    byte_t readByte(address_t address) const;
    half_t readHalfWord(address_t address) const;
    word_t readWord(address_t address) const;

    void writeByte(address_t address, byte_t value);
    void writeHalfWord(address_t address, half_t value);
    void writeWord(address_t address, word_t value);


    ~Memory();
};