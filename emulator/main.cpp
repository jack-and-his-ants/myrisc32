#include "Memory.hpp"
#include "CPU.hpp"
#include "config.hpp"
#include <iostream>

int main(){
    reg_t size = 10;
    Memory * memory = new Memory(size);
    memory->writeWord(0,0x44434241); // DCBA in little endian will be ABCD

    for(reg_t i = 0;i<4;i++){
        std::cout << (char)memory->readByte(i)<< std::endl;
    }
    memory->writeHalfWord(0,0x4443);

    for(reg_t i = 0;i<4;i++){
        std::cout << (char)memory->readByte(i)<< std::endl;
    }

    CPU * cpu = new CPU(10);
    std::cout << *cpu;
    delete memory;
    return 0;
}