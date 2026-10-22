#pragma once

#include "../bus.hpp"
#include "fulladder.hpp"
#include <iostream>

struct adderResult
{
    Bus sum;
    uint32_t carryOut;
};

inline adderResult rippleCarryAdder(Chip& c, const Bus& inputBusA, const Bus& inputBusB, State cin)
{
    Bus sum;
    sum.bits.reserve(inputBusA.bits.size());

    if(inputBusA.bits.size() != inputBusB.bits.size())
    {
        std::cout << "Bus size doesn't match";
    }

    uint32_t carry = c.input(cin);
    for(size_t i = 0; i < inputBusA.bits.size(); i++)
    {
        auto fa = fullAdder(c, inputBusA.bits[i], inputBusB.bits[i], carry);
        sum.bits.push_back(fa.sum);
        carry = fa.carryOut;
    }

    return {sum, carry};
}