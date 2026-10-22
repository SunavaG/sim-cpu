#include "../src/combinational/mux_4.hpp"
#include <iostream>

int main()
{
    Chip chip;
    Bus a = makeInputBus(chip, 8); setBus(chip, a, 0xAA);
    Bus b = makeInputBus(chip, 8); setBus(chip, b, 0xBB);
    Bus cc = makeInputBus(chip, 8); setBus(chip, cc, 0xCC);
    Bus d = makeInputBus(chip, 8); setBus(chip, d, 0xDD);

    for (int sel = 0; sel < 4; ++sel) {
        // sel = sel2*2 + sel1
        uint32_t s1 = chip.input((sel & 1) ? State::HIGH : State::LOW);
        uint32_t s2 = chip.input((sel & 2) ? State::HIGH : State::LOW);
        Bus out = mux4Bus(chip, a, b, cc, d, s1, s2);
        if (!chip.settle()) { /* error */ }
        std::cout << "sel=" << sel << " : 0x" << std::hex
                << readBus(chip, out) << "\n";
    }
}