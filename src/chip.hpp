#pragma once

#include "gates/gates.hpp"
#include "transistors/transistors.hpp"

struct Chip
{
    Circuit ckt;
    uint32_t VCC, GND;

    Chip()
    {
        VCC = ckt.createWire(true, State::HIGH);
        GND = ckt.createWire(true, State::LOW);
    }

    uint32_t input(State s)
    {
        return ckt.createWire(true, s);
    }
    uint32_t wire()
    {
        return ckt.createWire(false, State::DISCONNECTED);
    }

    void  set(uint32_t w, State s) 
    { 
        ckt.setWireState(w, s); 
    }
    
    State get(uint32_t w) const 
    { 
        return ckt.getWireState(w); 
    }

    bool  settle()
    {
        return ckt.settle(); 
    }

    uint32_t NOT(uint32_t inputWire)
    {
        uint32_t output = wire();
        gates::addNOT(ckt, inputWire, output, VCC, GND);
        return output;
    }

    uint32_t NOR(uint32_t inputWireA, uint32_t inputWireB)
    {
        uint32_t output = wire();
        gates::addNOR(ckt, inputWireA, inputWireB, output, VCC, GND);
        return output;
    }

    uint32_t NAND(uint32_t inputWireA, uint32_t inputWireB)
    {
        uint32_t output = wire();
        gates::addNAND(ckt, inputWireA, inputWireB, output, VCC, GND);
        return output;
    }

    uint32_t OR(uint32_t inputWireA, uint32_t inputWireB)
    {
        uint32_t output = wire();
        gates::addOR(ckt, inputWireA, inputWireB, output, VCC, GND);
        return output;
    }

    uint32_t AND(uint32_t inputWireA, uint32_t inputWireB)
    {
        uint32_t output = wire();
        gates::addAND(ckt, inputWireA, inputWireB, output, VCC, GND);
        return output;
    }

    uint32_t XOR(uint32_t inputWireA, uint32_t inputWireB)
    {
        uint32_t output = wire();
        gates::addXOR(ckt, inputWireA, inputWireB, output, VCC, GND);
        return output;
    }
};
