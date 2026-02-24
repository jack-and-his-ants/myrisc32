#pragma once
#include <iostream>
#include <cstdint>
#include "config.hpp"

class Flags
{
private:
    reg_t flagsRegister;

public:
    static constexpr reg_t MASK_Z = 1 << 0; // Zero flag
    static constexpr reg_t MASK_N = 1 << 1; // Negative flag
    static constexpr reg_t MASK_C = 1 << 2; // Carry flag
    static constexpr reg_t MASK_O = 1 << 3; // Overflow flag
    static constexpr reg_t MASK_I = 1 << 4; // Interrupt flag
    static constexpr reg_t MASK_T = 1 << 5; // Trap flag

    // Constructors
    Flags();

    // Getters
    bool isZero() const;
    bool isNegative() const;
    bool isCarry() const;
    bool isOverflow() const;
    bool interruptEnabled() const;
    bool isTrapMode() const;

    // Comparisons //

    bool isEqual() const;
    bool isNotEqual() const;

    // Signed
    bool isLower() const;
    bool isGreater() const;
    bool isLowerEqual() const;
    bool isGreaterEqual() const;

    // Unsigned
    bool isBelow() const;
    bool isAbove() const;
    bool isBelowEqual() const;
    bool isAboveEqual() const;

    // Setters
    void setZero(bool value);
    void setNegative(bool value);
    void setCarry(bool value);
    void setOverflow(bool value);
    void enableInterrupts();
    void disableInterrupts();
    void setTrapMode(bool value);

    // Multiple Flags Operations
    void setFlags();
    void clearFlags();
    void visualize() const;
    // Destructors
    ~Flags();
};