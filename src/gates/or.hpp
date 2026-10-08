#pragma once
#include "../transistors/transistors.hpp"
#include "not.hpp"
#include "nor.hpp"


namespace gates
{
    inline void addOR(
        Circuit& circuit,
        uint32_t inputWireA,
        uint32_t inputWireB,
        uint32_t outputWire,
        uint32_t VCC,
        uint32_t GND 
        )
    {
        uint32_t intermediate = circuit.createWire(false);

        gates::addNOR(circuit, inputWireA, inputWireB, intermediate, VCC, GND);
        gates::addNOT(circuit, intermediate, outputWire, VCC, GND);
    }
}