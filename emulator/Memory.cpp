#pragma once
#include <iostream>
#include <cstdint>
#include "config.hpp"
#include "Memory.hpp"

reg_t Memory::getSize(){
    return this->memory_size;
}