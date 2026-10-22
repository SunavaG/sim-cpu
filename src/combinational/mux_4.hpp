#pragma once
#include "mux_2.hpp"

inline uint32_t mux4(Chip& chip, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t sel1, uint32_t sel2)
{
    uint32_t inter1 = mux2(chip, a, b, sel1);
    uint32_t inter2 = mux2(chip, c, d, sel1);

    return mux2(chip, inter1, inter2, sel2);
}

inline Bus mux4Bus(Chip& c, const Bus& inputBusA, const Bus& inputBusB, const Bus& inputBusC, const Bus& inputBusD, uint32_t sel1, uint32_t sel2)
{
    Bus inter1 = mux2Bus(c, inputBusA, inputBusB, sel1);
    Bus inter2 = mux2Bus(c, inputBusC, inputBusD, sel1);

    return mux2Bus(c, inter1, inter2, sel2);
}