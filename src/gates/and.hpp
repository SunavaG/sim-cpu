#pragma once
#include "../transistors/transistors.hpp"
#include "not.hpp"
#include "nand.hpp"

namespace gates{

    inline void addAND(
        Circuit& circuit,
        uint32_t inputWireA,
        uint32_t inputWireB,
        uint32_t outputWire,
        uint32_t VCC,
        uint32_t GND 
        )
    {
        uint32_t intermediate = circuit.createWire(false);

        addNAND(circuit, inputWireA, inputWireB, intermediate, VCC, GND);
        addNOT(circuit, intermediate, outputWire, VCC, GND);
    }
}