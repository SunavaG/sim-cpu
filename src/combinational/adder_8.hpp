#pragma once

#include "../bus.hpp"
#include "fulladder.hpp"

struct adder_8Result
{
    Bus sum;
    uint32_t carryOut;
};

inline adder_8Result rca_8(Chip& c, const Bus& inputBusA, const Bus& inputBusB, State cin)
{
    Bus sum;
    sum.bits.reserve(inputBusA.bits.size());

    uint32_t carry = c.input(cin);
    for(size_t i = 0; i < inputBusA.bits.size(); i++)
    {
        auto fa = fullAdder(c, inputBusA.bits[i], inputBusB.bits[i], carry);
        sum.bits.push_back(fa.sum);
        carry = fa.carryOut;
    }

    return {sum, carry};
}