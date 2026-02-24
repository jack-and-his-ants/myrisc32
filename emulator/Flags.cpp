#pragma once
#include "Flags.hpp"
#include <iostream>

Flags::Flags(){
    this->clearFlags();
}



// Getters

bool Flags::isZero() const{
    return ((this->flagsRegister & MASK_Z)!=0);
};
bool Flags::isNegative() const{
    return ((this->flagsRegister & MASK_N)!=0);
};
bool Flags::isCarry() const{
    return ((this->flagsRegister & MASK_C)!=0);
};
bool Flags::isOverflow() const{
    return ((this->flagsRegister & MASK_O)!=0);
};
bool Flags::interruptEnabled() const{
    return ((this->flagsRegister & MASK_I)!=0);
};
bool Flags::isTrapMode() const{
    return ((this->flagsRegister & MASK_T)!=0);
};

// Comparisons

// Signed

// Unsigned

// Setters

void Flags::setZero(bool value){
    if (value) flagsRegister |= MASK_Z;
    else flagsRegister &= ~MASK_Z;
}

void Flags::setNegative(bool value){
    if (value) flagsRegister |= MASK_N;
    else flagsRegister &= ~MASK_N;
}

void Flags::setCarry(bool value){
    if (value) flagsRegister |= MASK_C;
    else flagsRegister &= ~MASK_C;
}

void Flags::setOverflow(bool value){
    if (value) flagsRegister |= MASK_O;
    else flagsRegister &= ~MASK_O;
}

void Flags::enableInterrupts(){
    flagsRegister |= MASK_I;
}

void Flags::disableInterrupts(){
    flagsRegister &= ~MASK_I;
}

void Flags::setTrapMode(bool value){
    if (value) flagsRegister |= MASK_T;
    else flagsRegister &= ~MASK_T;
}


// Multiple flags operations

void Flags::clearFlags(){
    this->flagsRegister = 0;
}

void Flags::setFlags(){
    this->flagsRegister = -1;
}

// Destructor

Flags::~Flags(){

};