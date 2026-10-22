#include "../src/combinational/alu.hpp"
#include <iostream>

int main() {
    const uint32_t vals[] = { 0, 1, 42, 127, 128, 255 };
    int failures = 0;
    int total = 0;

    for (uint32_t a : vals)
    for (uint32_t b : vals)
    for (int op = 0; op < 4; ++op) {
        Chip chip;
        Bus A = makeInputBus(chip, 8);
        Bus B = makeInputBus(chip, 8);
        setBus(chip, A, a);
        setBus(chip, B, b);

        uint32_t op0 = chip.input((op & 1) ? State::HIGH : State::LOW);
        uint32_t op1 = chip.input((op & 2) ? State::HIGH : State::LOW);

        auto r = alu(chip, A, B, op0, op1);
        if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

        uint32_t exp = (op == 0) ? ((a + b) & 0xFF)
                     : (op == 1) ? (a & b)
                     : (op == 2) ? (a | b)
                                 : (a ^ b);

        uint32_t got = readBus(chip, r.result);
        ++total;
        if (got != exp) {
            std::cout << "FAIL op=" << op << " a=" << a << " b=" << b
                      << " got=" << got << " exp=" << exp << "\n";
            ++failures;
        }
    }
    std::cout << total << " cases, " << failures << " failures\n";
    return failures ? 1 : 0;
}