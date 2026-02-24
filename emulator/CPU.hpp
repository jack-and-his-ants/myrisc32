#pragma once
#include <iostream>
#include <cstdint>
#include "Flags.hpp"
#include "Memory.hpp"
#include "config.hpp"
#include "ALU.hpp"

struct Instruction{
    OpCode opcode;
    OpSize size;
    Reg dest;
    Reg source;
    bool hasImmediate;
    int32_t immediate;
};

class CPU
{
private:
    Memory RAM;
    reg_t registers[16];
    Flags flags;
    reg_t constantValue;
    Instruction currentInstruction;
    
    ALU arithmeticLogicUnit;
    CPU(reg_t memory_size);

    
    void fetchInstruction();
    void executePush(Reg reg, OpSize size = OpSize::WORD);
    void executePop(Reg dest);
    void executeLoad(Reg dest,Reg sourceAddress);
    void executeLoad(Reg dest,address_t sourceAddress);
    void executeStore(Reg destAddress,Reg source);
    void executeStore(Reg destAddress,reg_t);

    ~CPU();
};