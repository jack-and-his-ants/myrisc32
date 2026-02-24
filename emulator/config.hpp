#pragma once
#include <cstdint>

using byte_t = uint8_t;
using half_t = uint16_t;
using word_t = uint32_t;

using address_t = uint32_t;
using reg_t = uint32_t;
using instruction_core_t = uint32_t;

enum class OpSize : uint8_t
{
    BYTE = 0,
    HALF = 1,
    WORD = 2
};

enum class Reg : uint8_t
{
    // Rejestry ogólne
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4,
    R5 = 5,
    R6 = 6,
    R7 = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,

    // Rejestry specjalne z nazwami funkcyjnymi
    SP = 13, // Stack Pointer
    LR = 14, // Link Register
    PC = 15, // Program Counter

    // Aliasy dla czytelności
    ZERO = 0, // R0 – zawsze zero
    RA = 1,   // Return Address (często w R1)
    A0 = 2,   // Argument 0 / wynik
    A1 = 3,   // Argument 1
    A2 = 4,   // Argument 2
    A3 = 5,   // Argument 3
    T0 = 6,   // Temporary 0 (caller-saved)
    T1 = 7,   // Temporary 1
    T2 = 8,   // Temporary 2
    T3 = 9,   // Temporary 3
    S0 = 10,  // Saved 0 (callee-saved)
    S1 = 11,  // Saved 1
    S2 = 12   // Saved 2
};

enum class OpCode : uint8_t
{
    // Memory and moving data
    MOV = 1,
    STORE = 2,
    LOAD = 3,
    XCHG = 4,
    // Stack operations
    PUSH = 5,
    POP = 6,
    // Arithmetics
    ADD = 7,
    SUB = 8,
    MUL = 9,
    MULU = 10,
    DIV = 11,
    DIVU = 12,
    REM = 13,
    REMU = 14,
    NEG = 15,
    // Logic
    AND = 16,
    OR = 17,
    XOR = 18,
    NOT = 19,
    // Shifts
    SHL = 20,
    SHR = 21,
    SAL = 22,
    SAR = 23,
    ROL = 24,
    ROR = 25,
    // Comparisons
    CMP = 26,
    SLT = 27,
    SLTU = 28,
    // Inconditional Jumps
    JMP = 29,
    CALL = 30,
    RET = 31,
    // Conditional Jumps
    JZ = 32,  // JE
    JNZ = 33, // JNE
    JC = 34,  // JB
    JNC = 35,
    JN = 36, // JL
    JO = 37,

    JA = 38,
    JBE = 39,
    JAE = 40,
    JG = 41,
    JLE = 42,
    JGE = 43,
};


