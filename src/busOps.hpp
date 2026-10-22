#pragma once
#include "bus.hpp"
#include <cassert>


inline Bus busAND(Chip& c, const Bus& inputBusA, const Bus& inputBusB)
{
    assert(inputBusA.bits.size() == inputBusB.bits.size());

    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.AND(inputBusA.bits[i], inputBusB.bits[i]));
    }
    return out;
}

inline Bus busOR(Chip& c, const Bus& inputBusA, const Bus& inputBusB)
{
    assert(inputBusA.bits.size() == inputBusB.bits.size());
    
    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.OR(inputBusA.bits[i], inputBusB.bits[i]));
    }
    return out;
}

inline Bus busNAND(Chip& c, const Bus& inputBusA, const Bus& inputBusB)
{
    assert(inputBusA.bits.size() == inputBusB.bits.size());
    
    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.NAND(inputBusA.bits[i], inputBusB.bits[i]));
    }
    return out;
}

inline Bus busNOT(Chip& c, const Bus& inputBusA)
{
    
    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.NOT(inputBusA.bits[i]));
    }
    return out;
}

inline Bus busNOR(Chip& c, const Bus& inputBusA, const Bus& inputBusB)
{
    assert(inputBusA.bits.size() == inputBusB.bits.size());
    
    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.NOR(inputBusA.bits[i], inputBusB.bits[i]));
    }
    return out;
}

inline Bus busXOR(Chip& c, const Bus& inputBusA, const Bus& inputBusB)
{
    assert(inputBusA.bits.size() == inputBusB.bits.size());
    
    Bus out;
    size_t sz = inputBusA.bits.size();
    for(int i = 0; i < sz; i++)
    {
        out.bits.push_back(c.XOR(inputBusA.bits[i], inputBusB.bits[i]));
    }
    return out;
}