#pragma once
#include "chip.hpp"
#include <vector>

struct Bus 
{
    std::vector<uint32_t> bits;   // bits[0] = LSB
};

inline Bus makeInputBus(Chip& c, int n) 
{
    Bus b;
    for (int i = 0; i < n; ++i) 
    {
        b.bits.push_back(c.input(State::LOW));
    }
    return b;
}

inline Bus makeInterBus(Chip& c, int n)
{
    Bus b;
    for (int i = 0; i < n; i++)
    {
        b.bits.push_back(c.wire());
    }
    return b;
}

inline void setBus(Chip& c, const Bus& b, uint32_t value) 
{
    for (size_t i = 0; i < b.bits.size(); ++i)
    {
        c.set(b.bits[i], (value >> i) & 1 ? State::HIGH : State::LOW);
    }
}

inline uint32_t readBus(const Chip& c, const Bus& b) 
{
    uint32_t v = 0;
    for (size_t i = 0; i < b.bits.size(); ++i)
    {
        if (c.get(b.bits[i]) == State::HIGH) v |= (1u << i);
    }
    return v;
}