#include <iostream>
#include <cstdint>
#include "config.hpp"
#include "Memory.hpp"

Memory::Memory(reg_t size)
{
    this->memorySize = size;
    this->memory = new byte_t[this->memorySize];

    std::cout << "Memory of size " << size << " bytes initialized." << std::endl;
}

reg_t Memory::getSize()
{
    return this->memorySize;
}

byte_t Memory::readByte(address_t address) const
{
    if (address >= memorySize)
    {
        throw std::out_of_range("Memory read out of bounds");
    }
    return this->memory[address];
}

half_t Memory::readHalfWord(address_t address) const
{
    if (address + 1 >= memorySize)
    {
        throw std::out_of_range("Memory read out of bounds");
    }
    half_t value = static_cast<half_t>(this->memory[address]) |
                   (static_cast<half_t>(this->memory[address + 1]) << 8);
    return value;
}

word_t Memory::readWord(address_t address) const
{
    if (address + 3 >= memorySize)
    {
        throw std::out_of_range("Memory read out of bounds");
    }
    word_t value = static_cast<word_t>(this->memory[address]) |
                   (static_cast<word_t>(this->memory[address + 1]) << 8) |
                   (static_cast<word_t>(this->memory[address + 2]) << 16) |
                   (static_cast<word_t>(this->memory[address + 3]) << 24);
    return value;
}

void Memory::writeByte(address_t address, byte_t value)
{
    if (address >= memorySize)
    {
        throw std::out_of_range("Memory write out of bounds");
    }
    this->memory[address] = value;
}

void Memory::writeHalfWord(address_t address, half_t value){
    if (address + 1 >= memorySize) {
        throw std::out_of_range("Memory write out of bounds");
    }
    memory[address]     = static_cast<uint8_t>(value);      
    memory[address + 1] = static_cast<uint8_t>(value >> 8);
}

void Memory::writeWord(address_t address, word_t value)
{
    if (address + 3 >= memorySize) {
        throw std::out_of_range("Memory write out of bounds");
    }
    memory[address]     = static_cast<uint8_t>(value);      
    memory[address + 1] = static_cast<uint8_t>(value >> 8);
    memory[address + 2] = static_cast<uint8_t>(value >> 16);
    memory[address + 3] = static_cast<uint8_t>(value >> 24);  
}

Memory::~Memory()
{
    delete[] this->memory;
    std::cout << "Memory deleted :)" << std::endl;
}
