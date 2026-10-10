#include "../transistors/transistors.hpp"
#include <iostream>

int main()
{
    Circuit board;

    uint32_t VCC = board.createWire(true, State::HIGH);
    uint32_t GND = board.createWire(true, State::LOW);
    
    uint32_t inputHighA = board.createWire(true, State::HIGH);
    uint32_t inputHighB = board.createWire(true, State::LOW);
    uint32_t output = board.createWire(false); 

    uint32_t interPmos = board.createWire(false);

    board.addPMOS(inputHighB, VCC, interPmos);
    board.addPMOS(inputHighA, interPmos, output);

    board.addNMOS(inputHighA, GND, output);
    board.addNMOS(inputHighB, GND, output);

    board.evaluate();
    
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighB)) << std::endl;
    std::cout << "Intermediate: " << static_cast<int>(board.getWireState(interPmos)) << std::endl;
    std::cout << "Output: " << static_cast<int>(board.getWireState(output));

}