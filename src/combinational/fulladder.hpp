#pragma once
#include "../chip.hpp"

struct fullAdderResult
{
    uint32_t sum;
    uint32_t carryOut;
};

inline fullAdderResult fullAdder(
    Chip& chip,
    uint32_t inputWireA,
    uint32_t inputWireB,
    uint32_t carryIn
    )
{
    uint32_t xor1 = chip.XOR(inputWireA, inputWireB);
    uint32_t sum = chip.XOR(xor1, carryIn);
    uint32_t andIP = chip.AND(inputWireA, inputWireB);
    uint32_t andCX  = chip.AND(xor1, carryIn);
    uint32_t carryOut = chip.OR(andIP, andCX);

    return{sum, carryOut};
}