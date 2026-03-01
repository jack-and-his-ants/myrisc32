#include <iostream>
#include <cstdint>
#include "CPU.hpp"
#include "Memory.hpp"
#include "Flags.hpp"
#include <iomanip>

//  MEGA KONSTRUKTOR MUAHAHAHAHAHA

CPU::CPU(reg_t memory_size)
    : memory((memory_size/4)*4),
      registers{},             
      flags(),
      currentInstruction{},
      arithmeticLogicUnit()     
{
   
    registers[static_cast<reg_t>(Reg::SP)] = (memory_size/4)*4;
    registers[static_cast<reg_t>(Reg::PC)] = 0;
    std::cout << "CPU initialized. Memory size: "
              << (memory_size/4)*4 << std::endl;
}



std::ostream& operator<<(std::ostream& os, const CPU& cpu)
{
    os << "=========== CPU STATE ===========\n\n";

    // ---- Rejestry ----
    os << "Registers:\n";
    for (int i = 0; i < 16; ++i)
    {
        os << "R" << std::dec << i << " : 0x"
           << std::hex
           << std::setw(sizeof(reg_t) * 2)
           << std::setfill('0')
           << cpu.registers[i]
           << "\n";
    }

    // ---- Flagi ----
    os << "\nFlags:\n";
    os << "Z: " << cpu.flags.isZero()
       << "  C: " << cpu.flags.isCarry()
       << "  S: " << cpu.flags.isNegative()
       << "  O: " << cpu.flags.isOverflow()
       << "\n";

    // ---- Instrukcja ----
    os << "\nCurrent Instruction:\n";
    os << "Opcode  : " << static_cast<int>(cpu.currentInstruction.opcode) << "\n";
    os << "Size    : " << static_cast<int>(cpu.currentInstruction.size) << "\n";
    os << "Dest    : " << static_cast<int>(cpu.currentInstruction.dest) << "\n";
    os << "Source  : " << static_cast<int>(cpu.currentInstruction.source) << "\n";

    if (cpu.currentInstruction.hasImmediate)
    {
        os << "Immediate : " << cpu.currentInstruction.immediate << "\n";
    }

    os << "\n=================================\n";

    return os;
}
word_t CPU::getSource()
{
    word_t source = 0;
    if (this->currentInstruction.hasImmediate)
    {
        source = this->currentInstruction.immediate;
    }
    else
    {
        reg_t src = this->registers[static_cast<reg_t>(this->currentInstruction.source)];
        source = src;
    }
    std::cout << "Value: " << source << " read from " << (this->currentInstruction.hasImmediate ? "Constant" : "Register") << std::endl;
    return source;
}

void CPU::writeToDest(reg_t value)
{
    reg_t destIdx = static_cast<reg_t>(this->currentInstruction.dest);
    reg_t val = 0;
    switch (this->currentInstruction.size)
    {
    case (OpSize::BYTE):
        val = (this->registers[destIdx] & 0xFFFFFF00) | value;
        this->registers[destIdx] = val;
        break;
    case (OpSize::HALF):
        val = (this->registers[destIdx] & 0xFFFF0000) | value;
        this->registers[destIdx] = val;
        break;
    case (OpSize::WORD):
        this->registers[destIdx] = value;
        val = value;
        break;
    }
    std::cout << "Value " << val << " written to " << "R" << "destIdx" << std::endl;
}

void CPU::decodeInstruction(instruction_core_t raw)
{
    this->currentInstruction.opcode = static_cast<OpCode>((raw >> 10) & 0x3F);
    this->currentInstruction.hasImmediate = (((raw >> 8) & 0x03) == 0x03);
    if (this->currentInstruction.hasImmediate)
    {
        this->currentInstruction.size = static_cast<OpSize>((raw) & 0x03);
    }
    else
    {
        this->currentInstruction.size = static_cast<OpSize>((raw >> 8) & 0x03);
        this->currentInstruction.source = static_cast<Reg>((raw) & 0x0F);
    }
    this->currentInstruction.dest = static_cast<Reg>((raw >> 4) & 0x0F);
}

void CPU::fetchAndDecodeInstruction()
{
    reg_t pc = (registers[static_cast<reg_t>(Reg::PC)]);
    if (pc + 1 >= memory.getSize())
    {
        throw std::runtime_error("Program counter out of bounds");
    }
    uint16_t instructionCore = this->memory.readHalfWord(pc);
    this->decodeInstruction(instructionCore);

    if (this->currentInstruction.hasImmediate)
    {
        switch (this->currentInstruction.size)
        {
        case (OpSize::BYTE):
            this->currentInstruction.immediate = static_cast<word_t>(this->memory.readByte(pc + 2));
            registers[static_cast<size_t>(Reg::PC)] += 1;
            break;
        case (OpSize::HALF):
            this->currentInstruction.immediate = static_cast<word_t>(this->memory.readHalfWord(pc + 2));
            registers[static_cast<reg_t>(Reg::PC)] += 2;
            break;
        case (OpSize::WORD):
            this->currentInstruction.immediate = static_cast<word_t>(this->memory.readWord(pc + 2));
            registers[static_cast<reg_t>(Reg::PC)] += 4;
            break;
        }
    }
    registers[static_cast<reg_t>(Reg::PC)] += 2;
}

void CPU::executeMove()
{
    word_t val = this->getSource();
    this->writeToDest(val);
}

void CPU::executePush()
{
    reg_t mask = 0;
    this->registers[static_cast<reg_t>(Reg::SP)] -= 4;

    if (this->currentInstruction.size == OpSize::WORD)
    {
        mask = -0xFFFFFFFF;
    }
    else if (this->currentInstruction.size == OpSize::HALF)
    {
        mask = 0xFFFF;
    }
    else if (this->currentInstruction.size == OpSize::BYTE)
    {
        mask = 0xFF;
    }

    reg_t valueToWrite = getSource() & mask;

    this->memory.writeWord(this->registers[static_cast<reg_t>(Reg::SP)], valueToWrite);
}
void CPU::executeLoad()
{
    address_t addr = this->getSource();
    word_t val = this->memory.readWord(addr);
    this->writeToDest(val);
}

void CPU::executePop()
{
    address_t addr = this->registers[static_cast<reg_t>(Reg::SP)];
    word_t popped = this->memory.readWord(addr);
    this->writeToDest(popped);
    this->registers[static_cast<reg_t>(Reg::SP)] += 4;
    std::cout << "POP executed succesfully: " << std::endl;

    return;
}
