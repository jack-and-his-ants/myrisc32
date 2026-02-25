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
    Memory memory;
    reg_t registers[16];
    Flags flags;
    reg_t constantValue;
    Instruction currentInstruction;
    
    ALU arithmeticLogicUnit;
public:
    CPU(reg_t memory_size);

    
    void fetchAndDecodeInstruction();
    void decodeInstruction(instruction_core_t raw);
    void decodeInstruction();
    void executePush(Reg reg, OpSize size = OpSize::WORD);
    void executePop(Reg dest);
    void executeLoad(Reg dest,Reg sourceAddress);
    void executeLoad(Reg dest,address_t sourceAddress);
    void executeStore(Reg destAddress,Reg source);
    void executeStore(Reg destAddress,reg_t);

    ~CPU();
};