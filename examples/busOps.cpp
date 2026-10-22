#include "../src/busOps.hpp"
#include <iostream>

int main() {
    Chip chip;
    Bus a = makeInputBus(chip, 8);
    Bus b = makeInputBus(chip, 8);
    setBus(chip, a, 0b10101010);
    setBus(chip, b, 0b11001100);

    Bus andR = busAND(chip, a, b);
    Bus orR  = busOR (chip, a, b);
    Bus xorR = busXOR(chip, a, b);
    Bus notA = busNOT(chip, a);

    if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

    std::cout << "AND: 0x" << std::hex << readBus(chip, andR) << "\n";   // 0x88
    std::cout << "OR:  0x" << std::hex << readBus(chip, orR)  << "\n";   // 0xEE
    std::cout << "XOR: 0x" << std::hex << readBus(chip, xorR) << "\n";   // 0x66
    std::cout << "NOT: 0x" << std::hex << readBus(chip, notA) << "\n";   // 0x55
    return 0;
}