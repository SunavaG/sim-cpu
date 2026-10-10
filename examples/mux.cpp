#include "../src/chip.hpp"
#include <iostream>

int main()
{
    Chip chip;

    uint32_t inputSel = chip.input(State::LOW);

    uint32_t inputA = chip.input(State::HIGH);
    uint32_t inputB = chip.input(State::LOW);

    uint32_t x = chip.NOT(inputSel);
    uint32_t y = chip.AND(inputA, x);
    uint32_t z = chip.AND(inputB, inputSel);

    uint32_t out = chip.OR(y,z);

    chip.settle();

    std::cout << "Input: " << static_cast<int>(chip.get(inputA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(chip.get(inputB)) << std::endl;
    std::cout << "Select: " << static_cast<int>(chip.get(inputSel)) << std::endl;
    std::cout << "Out: " << static_cast<int>(chip.get(out)) << std::endl;

}
