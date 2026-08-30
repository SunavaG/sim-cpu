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
    }; //check if the transistor is conducting or not
};

class Circuit
{
    private:
        std::vector<Wire> wires;
        std::vector<Transistor> transistors;

    public:
        uint32_t createNode(State initialState = State::DISCONNECTED, bool isFixed)
        {
            uint32_t id = wires.size();
            wires.push_back({id, isFixed, initialState, initialState});
            return id;
        };

        void addPMOS(uint32_t gate, uint32_t source, uint32_t drain)
        {
            bool isPMOS = true;
            transistors.push_back({isPMOS, gate, source, drain});
        };

        void addNMOS(uint32_t gate, uint32_t source, uint32_t drain)
        {
            bool isPMOS = false;
            transistors.push_back({isPMOS, gate, source, drain});
        };
};