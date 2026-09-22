#pragma once
#include "../transistors/transistors.hpp"

inline void addNAND(
    Circuit& circuit,
    uint32_t inputWireA,
    uint32_t inputWireB,
    uint32_t outputWire,
    uint32_t VCC,
    uint32_t GND  
    )
{
    uint32_t intermediateWire = circuit.createWire(false);

    circuit.addNMOS(inputWireA, GND, intermediateWire);
    circuit.addNMOS(inputWireB, intermediateWire, outputWire);

    circuit.addPMOS(inputWireA, VCC, outputWire);
    circuit.addPMOS(inputWireB, VCC, outputWire);
}