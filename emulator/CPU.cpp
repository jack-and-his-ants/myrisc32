#pragma once
#include <iostream>
#include <cstdint>
#include "CPU.hpp"
#include "Memory.hpp"

void CPU::decodeInstruction(instruction_core_t raw){
    this->currentInstruction.opcode=static_cast<OpCode>((raw>>10)&0x3F);
    this->currentInstruction.hasImmediate=(((raw>>8)&0x03)==0x03);
    if(this->currentInstruction.hasImmediate){
        this->currentInstruction.size=static_cast<OpSize>((raw)&0x03);
    }
    else{
        this->currentInstruction.size=static_cast<OpSize>((raw>>8)&0x03);
        this->currentInstruction.source=static_cast<Reg>((raw)&0x0F);
    }
    this->currentInstruction.dest=static_cast<Reg>((raw>>4)&0x0F);
}

void CPU::fetchAndDecodeInstruction(){
    reg_t pc = (registers[static_cast<size_t>(Reg::PC)]);
    if (pc + 1 >= memory.getSize()) {
        throw std::runtime_error("Program counter out of bounds");
    }
    uint16_t instructionCore = this->memory.readHalfWord(pc);
    this->decodeInstruction(instructionCore);

    if(this->currentInstruction.hasImmediate){
        switch(this->currentInstruction.size){
            case(OpSize::BYTE):
                this->currentInstruction.immediate=static_cast<word_t>(this->memory.readByte(pc+2));
                registers[static_cast<size_t>(Reg::PC)]+=1;
                break;
            case(OpSize::HALF):
                this->currentInstruction.immediate=static_cast<word_t>(this->memory.readHalfWord(pc+2));
                registers[static_cast<size_t>(Reg::PC)]+=2;
                break;
            case(OpSize::WORD):
                this->currentInstruction.immediate=static_cast<word_t>(this->memory.readWord(pc+2));
                registers[static_cast<size_t>(Reg::PC)]+=4;
                break;
                
        }
    }
    registers[static_cast<size_t>(Reg::PC)]+=2;
    
}

