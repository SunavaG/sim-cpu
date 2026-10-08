#pragma once
#include "chip.hpp"

struct halfAdderResult
{
    uint32_t sum;
    uint32_t carry;
};

inline halfAdderResult halfAdder(
    Chip& chip,
    uint32_t inputA,
    uint32_t inputB
    )
{
    return
    {
        chip.XOR(inputA,inputB),
        chip.AND(inputA, inputB)
    };
}