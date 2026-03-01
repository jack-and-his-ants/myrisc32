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
    Instruction currentInstruction;
    
    ALU arithmeticLogicUnit;
public:
    CPU(reg_t memory_size);

    friend std::ostream& operator<<(std::ostream& os, const CPU& cpu);
    void fetchAndDecodeInstruction();
    void decodeInstruction(instruction_core_t raw);
    void executePush();
    void executePop();
    void executeLoad();
    void executeStore();
    void executeMove();
    word_t getSource();
    void writeToDest(reg_t value);

    ~CPU();
};