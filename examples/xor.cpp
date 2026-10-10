#include <iostream>
#include "../src/transistors/transistors.hpp"
#include "nand.hpp"

int main()
{
    Circuit board;

    uint32_t VCC = board.createWire(true, State::HIGH);
    uint32_t GND = board.createWire(true, State::LOW);
    
    uint32_t inputHighA = board.createWire(true, State::HIGH);
    uint32_t inputHighB = board.createWire(true, State::HIGH);
    uint32_t output = board.createWire(false); 

    uint32_t interNAND1 = board.createWire(false);
    uint32_t interNAND2 = board.createWire(false);
    uint32_t interNAND3 = board.createWire(false);

    gates::addNAND(board, inputHighA, inputHighB, interNAND1, VCC, GND);
    gates::addNAND(board, inputHighA, interNAND1, interNAND2, VCC, GND);
    gates::addNAND(board, inputHighB, interNAND1, interNAND3, VCC, GND);
    gates::addNAND(board, interNAND2, interNAND3, output, VCC, GND);

    if (!board.settle()) {
        std::cout << "circuit did not converge\n";
        return 1;
    }


    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputHighB)) << std::endl;
    std::cout << "NAND1: " << static_cast<int>(board.getWireState(interNAND1)) << std::endl;
    std::cout << "NAND2: " << static_cast<int>(board.getWireState(interNAND2)) << std::endl;
    std::cout << "NAND3: " << static_cast<int>(board.getWireState(interNAND3)) << std::endl;
    std::cout << "Output: " << static_cast<int>(board.getWireState(output));
}