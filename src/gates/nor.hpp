#pragma once
#include "../transistors/transistors.hpp"


namespace gates
{
    inline void addNOR(
        Circuit& circuit,
        uint32_t inputWireA,
        uint32_t inputWireB,
        uint32_t outputWire,
        uint32_t VCC,
        uint32_t GND  
        )
    {
        uint32_t intermediateWire = circuit.createWire(false);

        circuit.addNMOS(inputWireA, GND, outputWire);
        circuit.addNMOS(inputWireB, GND, outputWire);

        circuit.addPMOS(inputWireA, VCC, intermediateWire);
        circuit.addPMOS(inputWireB, intermediateWire, outputWire);
    }
}