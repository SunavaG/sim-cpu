#include "../transistors/transistors.hpp"
#include "nand.hpp"
#include "not.hpp"
#include <iostream>

int main()
{
    Circuit board;

    uint32_t VCC = board.createWire(true, State::HIGH);
    uint32_t GND = board.createWire(true, State::LOW);

    uint32_t inputA = board.createWire(true, State::HIGH);
    uint32_t inputB = board.createWire(true, State::HIGH);

    uint32_t output = board.createWire(false);
    uint32_t intermediate = board.createWire(false);

    addNAND(board, inputA, inputB, intermediate, VCC, GND);
    addNOT(board, intermediate, output, VCC, GND);

    if (!board.settle()) {
        std::cout << "circuit did not converge\n";
        return 1;
    }


    std::cout << "Input: " << static_cast<int>(board.getWireState(inputA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(board.getWireState(inputB)) << std::endl;
    std::cout << "Intermediate: " << static_cast<int>(board.getWireState(intermediate)) << std::endl;
    std::cout << "Output: " << static_cast<int>(board.getWireState(output));

}