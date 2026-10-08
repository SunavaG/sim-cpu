#pragma once
#include "../transistors/transistors.hpp"
#include "nand.hpp"

namespace gates{

inline void addXOR(
    Circuit& circuit,
    uint32_t inputWireA,
    uint32_t inputWireB,
    uint32_t outputWire,
    uint32_t VCC,
    uint32_t GND 
)
{
    uint32_t interNAND1 = circuit.createWire(false);
    uint32_t interNAND2 = circuit.createWire(false);
    uint32_t interNAND3 = circuit.createWire(false);

    addNAND(circuit, inputWireA, inputWireB, interNAND1, VCC, GND);
    addNAND(circuit, inputWireA, interNAND1, interNAND2, VCC, GND);
    addNAND(circuit, inputWireB, interNAND1, interNAND3, VCC, GND);
    addNAND(circuit, interNAND2, interNAND3, outputWire, VCC, GND);
}}