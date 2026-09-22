#include <cassert>
#include <iostream>
#include "../src/transistors/transistors.hpp"

void testResolveStates()
{
    assert(resolveStates(State::HIGH, State::HIGH)
           == State::HIGH);

    assert(resolveStates(State::LOW, State::LOW)
           == State::LOW);

    assert(resolveStates(State::HIGH, State::LOW)
           == State::CONFLICT);

    assert(resolveStates(State::LOW, State::HIGH)
           == State::CONFLICT);

    assert(resolveStates(State::DISCONNECTED, State::HIGH)
           == State::HIGH);

    assert(resolveStates(State::HIGH, State::DISCONNECTED)
           == State::HIGH);

    assert(resolveStates(State::DISCONNECTED, State::LOW)
           == State::LOW);

    assert(resolveStates(State::LOW, State::DISCONNECTED)
           == State::LOW);

    assert(resolveStates(State::CONFLICT, State::HIGH)
           == State::CONFLICT);

    assert(resolveStates(State::CONFLICT, State::LOW)
           == State::CONFLICT);

    std::cout << "resolveStates tests passed\n";
}

void testTransistors()
{
    Transistor pmos{
        true,
        0,
        1,
        2
    };

    Transistor nmos{
        false,
        0,
        1,
        2
    };

    assert(pmos.isConducting(State::LOW));
    assert(!pmos.isConducting(State::HIGH));

    assert(!nmos.isConducting(State::LOW));
    assert(nmos.isConducting(State::HIGH));

    std::cout << "transistor tests passed\n";
}

void testWire()
{
    Circuit circuit;

    uint32_t wire = circuit.createWire(true, State::LOW);

    assert(circuit.getWireState(wire) == State::LOW);

    circuit.setWireState(wire, State::HIGH);

    assert(circuit.getWireState(wire) == State::HIGH);

    std::cout << "wire tests passed\n";
}

void testInverter()
{
    Circuit circuit;

    // External/fixed wires
    uint32_t vdd = circuit.createWire(true, State::HIGH);
    uint32_t gnd = circuit.createWire(true, State::LOW);
    uint32_t in  = circuit.createWire(true, State::LOW);

    // Internal output
    uint32_t out = circuit.createWire(false);

    // CMOS inverter
    circuit.addPMOS(in, vdd, out);
    circuit.addNMOS(in, out, gnd);

    // IN = LOW
    circuit.evaluate();

    assert(circuit.getWireState(out) == State::HIGH);

    // IN = HIGH
    circuit.setWireState(in, State::HIGH);
    circuit.evaluate();

    assert(circuit.getWireState(out) == State::LOW);

    std::cout << "inverter test passed\n";
}

void testFloatingWire()
{
    Circuit circuit;

    uint32_t vdd = circuit.createWire(true, State::HIGH);
    uint32_t in  = circuit.createWire(true, State::LOW);
    uint32_t out = circuit.createWire(false);

    circuit.addPMOS(in, vdd, out);

    // PMOS ON
    circuit.evaluate();

    assert(circuit.getWireState(out) == State::HIGH);

    // PMOS OFF
    circuit.setWireState(in, State::HIGH);
    circuit.evaluate();

    assert(circuit.getWireState(out) == State::DISCONNECTED);

    std::cout << "floating wire test passed\n";
}

void testConflict()
{
    Circuit circuit;

    uint32_t vdd = circuit.createWire(true, State::HIGH);
    uint32_t gnd = circuit.createWire(true, State::LOW);

    uint32_t pmosGate = circuit.createWire(true, State::LOW);
    uint32_t nmosGate = circuit.createWire(true, State::HIGH);

    uint32_t out = circuit.createWire(false);

    circuit.addPMOS(pmosGate, vdd, out);
    circuit.addNMOS(nmosGate, out, gnd);

    circuit.evaluate();

    assert(circuit.getWireState(out) == State::CONFLICT);

    std::cout << "conflict test passed\n";
}

void testDisconnected()
{
    Circuit circuit;

    uint32_t out = circuit.createWire(false);

    circuit.evaluate();

    assert(circuit.getWireState(out) == State::DISCONNECTED);

    std::cout << "disconnected test passed\n";
}

void testMultipleConnectedWires()
{
    Circuit circuit;

    uint32_t vdd = circuit.createWire(true, State::HIGH);

    uint32_t gate1 = circuit.createWire(true, State::LOW);
    uint32_t gate2 = circuit.createWire(true, State::HIGH);
    uint32_t gate3 = circuit.createWire(true, State::LOW);

    uint32_t a = circuit.createWire(false);
    uint32_t b = circuit.createWire(false);
    uint32_t c = circuit.createWire(false);

    circuit.addPMOS(gate1, vdd, a);
    circuit.addNMOS(gate2, a, b);
    circuit.addPMOS(gate3, b, c);

    circuit.evaluate();

    assert(circuit.getWireState(a) == State::HIGH);
    assert(circuit.getWireState(b) == State::HIGH);
    assert(circuit.getWireState(c) == State::HIGH);

    std::cout << "multiple connection test passed\n";
}

int main()
{
    testResolveStates();
    testTransistors();
    testWire();

    testInverter();
    testFloatingWire();
    testConflict();
    testDisconnected();
    testMultipleConnectedWires();

    std::cout << "\nAll tests passed!\n";
}

