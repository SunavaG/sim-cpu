#pragma once
#include "../chip.hpp"
#include "../bus.hpp"

inline uint32_t mux2(Chip& c, uint32_t a, uint32_t b, uint32_t sel)
{
    uint32_t notSel = c.NOT(sel);
    uint32_t inter1 = c.AND(a, notSel);
    uint32_t inter2 = c.AND(b, sel);

    return c.OR(inter1, inter2);
}

inline Bus mux2Bus(Chip& c, const Bus& inputBusA, const Bus& inputBusB, uint32_t sel)
{
    uint32_t notSel = c.NOT(sel); 
    Bus out;
    out.bits.reserve(inputBusA.bits.size());
    for (size_t i = 0; i < inputBusA.bits.size(); ++i) {
        uint32_t t1 = c.AND(inputBusA.bits[i], notSel);
        uint32_t t2 = c.AND(inputBusB.bits[i], sel);
        out.bits.push_back(c.OR(t1, t2));
    }
    return out;
}