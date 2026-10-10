//not.cpp
#include "../transistors/transistors.hpp"
#include <iostream>

int main()
{
    Circuit board;

    uint32_t VCC = board.createWire(true, State::HIGH);
    uint32_t GND = board.createWire(true, State::LOW);

    uint32_t inputHigh = board.createWire(true, State::DISCONNECTED);
    uint32_t output = board.createWire(false);

    board.addPMOS(inputHigh, VCC, output);
    board.addNMOS(inputHigh, GND, output);
    board.evaluate();

    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHigh));
    std::cout << "Output: " << static_cast<int>(board.getWireState(output));
}