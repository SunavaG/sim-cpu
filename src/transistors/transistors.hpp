#pragma once
#include <vector>
#include <cstdint>

enum class State: uint8_t 
{
    HIGH = 1,
    LOW = 0,
    DISCONNECTED = 2,
    CONFLICT = 3,
};

struct Wire
{
    uint32_t id;
    bool isFixed; //connected to vcc, ggnd, or input(basically externally driven)
    State currentState;
    State nextState;
};

struct Transistor
{
    bool isPMOS;
    uint32_t gateWireId; //wire id connected to Gate
    uint32_t sourceWireId; //wire id connected to Source
    uint32_t drainWireId; //wire id connected to Drain

    bool isConducting(State state) const
    {
        if (isPMOS)
            return state == State::LOW;
        else
            return state == State::HIGH;
    }; //check if the transistor is condcting or not
};

