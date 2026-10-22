#pragma once

#include "../busOps.hpp"
#include "rcadder.hpp"
#include "mux_4.hpp"

struct AluResult
{
    Bus result;
    uint32_t carry;
    uint32_t zero;
    uint32_t negative;
};

inline AluResult alu(Chip& c, const Bus& inputA, const Bus& inputB, uint32_t op0, uint32_t op1)
{
    auto aluAdd = rippleCarryAdder(c,inputA, inputB, State::LOW);
    Bus aluAnd = busAND(c, inputA, inputB);
    Bus aluOR = busOR(c,inputA, inputB);
    Bus aluXOR = busXOR(c, inputA, inputB);

    Bus res = mux4Bus(c, aluAdd.sum, aluAnd, aluOR, aluXOR, op0, op1);

    uint32_t carry = aluAdd.carryOut;
    uint32_t negative = res.bits.back();

    uint32_t anyHigh = res.bits[0];
    for (size_t i = 1; i < res.bits.size(); ++i)
        anyHigh = c.OR(anyHigh, res.bits[i]); 
    uint32_t zero = c.NOT(anyHigh);


    return {res, carry, zero, negative};
}
