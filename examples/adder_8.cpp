#include "../src/bus.hpp"
#include "../src/combinational/fulladder.hpp"
#include <iostream>

struct adder_8Result
{
    Bus sum;
    uint32_t carryOut;
};

adder_8Result rca_8(Chip& c, const Bus& a,const Bus& b, uint32_t cin)
{
    Bus sum = makeInterBus(c, (int)a.bits.size());

    uint32_t carry = cin;

    for(size_t i = 0; i < a.bits.size(); i++)
    {
        auto fa = fullAdder(c, a.bits[i], b.bits[i], carry);
        sum.bits[i] = fa.sum;
        carry = fa.carryOut;
    }

    return {sum, carry};
}

int redSweep()
{
    const uint32_t vals[] = { 0, 1, 127, 128, 254, 255 };
    int failures = 0;
    for (uint32_t a : vals)
    for (uint32_t b : vals) {
        Chip chip;
        Bus A = makeInputBus(chip, 8);
        Bus B = makeInputBus(chip, 8);
        setBus(chip, A, a);
        setBus(chip, B, b);
        uint32_t cinWire = chip.input(State::LOW);

        auto r = rca_8(chip, A, B, cinWire);
        if (!chip.settle()) { std::cerr << "no converge\n"; return 1; }

        uint32_t got = readBus(chip, r.sum);
        uint32_t exp = (a + b) & 0xFF;
        if (got != exp) {
            std::cout << "FAIL: " << a << " + " << b
                    << " = " << got << " (expected " << exp << ")\n";
            ++failures;
        }
    }
    std::cout << (failures ? "FAILED\n" : "all " + std::to_string(6*6) + " cases passed\n");
    return failures ? 1 : 0;
}

int main()
{
    Chip rca8;
    Bus a = makeInputBus(rca8, 8), b = makeInputBus(rca8, 8);
    setBus(rca8, a, 42);
    setBus(rca8, b, 3);
    uint32_t cin = rca8.input(State::LOW);
    auto r = rca_8(rca8, a, b, cin);

    rca8.settle();

    std::cout << "Bus A: " << readBus(rca8, a) << std::endl;
    std::cout << "Bus B: " << readBus(rca8, b) << std::endl;
    std::cout << "CarryIN: " << static_cast<int>(rca8.get(cin)) << std::endl;
    std::cout << "Sum: " << readBus(rca8, r.sum) << std::endl;

    redSweep();
}