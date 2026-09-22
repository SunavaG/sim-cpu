//not.hpp
#pragma once
#include "../transistors/transistors.hpp"


void addNOT(
    Circuit& circuit,
    uint32_t inputWire,
    uint32_t outputWire,
    uint32_t VCC,
    uint32_t GND
)
{
    circuit.addPMOS(inputWire, VCC, outputWire);
    circuit.addNMOS(inputWire, GND, outputWire);    

    
}