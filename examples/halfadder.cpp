#include "../src/gates/gates.hpp"
#include <iostream>

int main()
{
    Circuit cir;

    uint32_t VCC = cir.createWire(true, State::HIGH);
    uint32_t GND = cir.createWire(true, State::LOW);

    uint32_t inputA = cir.createWire(true, State::HIGH);
    uint32_t inputB = cir.createWire(true, State::HIGH);

    uint32_t sum = cir.createWire(false);
    uint32_t carry = cir.createWire(false);

    gates::addXOR(cir, inputA, inputB, sum, VCC, GND);
    gates::addAND(cir, inputA, inputB, carry, VCC, GND);

    if (!cir.settle()) {
        std::cout << "circuit did not converge\n";
        return 1;
    }

    std::cout << "Input: " << static_cast<int>(cir.getWireState(inputA)) << std::endl;
    std::cout << "Input: " << static_cast<int>(cir.getWireState(inputB)) << std::endl;
    std::cout << "Carry: " << static_cast<int>(cir.getWireState(carry)) << std::endl;
    std::cout << "Sum: " << static_cast<int>(cir.getWireState(sum)) << std::endl;

    std::cout << "A B | Cout Sum\n----+---------\n";
    for (int a = 0; a < 2; ++a)
    for (int b = 0; b < 2; ++b) {
        cir.setWireState(inputA, a ? State::HIGH : State::LOW);
        cir.setWireState(inputB, b ? State::HIGH : State::LOW);
        if (!cir.settle()) { std::cerr << "no converge\n"; return 1; }
        int s = cir.getWireState(sum)   == State::HIGH;
        int c = cir.getWireState(carry) == State::HIGH;
        int expS = a ^ b;
        int expC = a & b;
        std::cout << a << " " << b << " |  " << c << "    " << s
                << ((s == expS && c == expC) ? "" : "  <-- WRONG") << "\n";
    }

}