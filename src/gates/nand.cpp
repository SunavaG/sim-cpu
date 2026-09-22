#include "../transistors/transistors.hpp"
#include <iostream>

int main()
{
    Circuit board;

    uint32_t VCC = board.createWire(true, State::HIGH);
    uint32_t GND = board.createWire(true, State::LOW);
    
    uint32_t inputHighA = board.createWire(true, State::LOW);
    uint32_t inputHighB = board.createWire(true, State::HIGH);
    uint32_t output = board.createWire(false); 

    uint32_t interNmos = board.createWire(false);

    board.addNMOS(inputHighB, GND, interNmos);
    board.addNMOS(inputHighA, interNmos, output);

    board.addPMOS(inputHighA, VCC, output);
    board.addPMOS(inputHighB, VCC, output);

    board.evaluate();
    
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighB)) << std::endl;
    std::cout << "Output: " << static_cast<int>(board.getWireState(output));

}