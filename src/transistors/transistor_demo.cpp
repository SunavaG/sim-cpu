#include "../src/transistors/transistors.hpp"
#include <iostream>
#include <fstream>

void addpmos(std::ofstream& file);
void addnmos(std::ofstream& file);
void inv(std::ofstream& file);
void seriesnmos(std::ofstream& file);


int main()
{
    std::ofstream Myfile("transtest.txt");
    addpmos(Myfile);
    addnmos(Myfile);
    inv(Myfile);

    seriesnmos(Myfile);
}

void addpmos(std::ofstream& file)
{
    Circuit breadboard;

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireLow = breadboard.createWire(true, State::LOW);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addPMOS(inputWireLow, VCC, outputWire);
    breadboard.evaluate();

    file << "Adding PMOS to circuit" << "\n\n\n";
    file << "INPUT = " << static_cast<int>(breadboard.getWireState(inputWireLow)) << '\n';
    file << "OUTPUT = " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireHigh = breadboard.createWire(true, State::HIGH);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addPMOS(inputWireHigh, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireHigh)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireDisc = breadboard.createWire(true, State::DISCONNECTED);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addPMOS(inputWireDisc, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireDisc)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

}

void addnmos(std::ofstream& file)
{
    Circuit breadboard;

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireLow = breadboard.createWire(true, State::LOW);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addNMOS(inputWireLow, GND, outputWire);
    breadboard.evaluate();

    file << "Adding NMOS to circuit" << "\n\n\n";
    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireLow)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireHigh = breadboard.createWire(true, State::HIGH);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addNMOS(inputWireHigh, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireHigh)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }
    
    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireDisc = breadboard.createWire(true, State::DISCONNECTED);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addNMOS(inputWireDisc, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireDisc)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }
}

void inv(std::ofstream& file)
{
    Circuit breadboard;

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireLow = breadboard.createWire(true, State::LOW);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addPMOS(inputWireLow, VCC, outputWire);
    breadboard.addNMOS(inputWireLow, GND, outputWire);
    breadboard.evaluate();

    file << "Adding Inverter" << "\n\n";
    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireLow)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireHigh = breadboard.createWire(true, State::HIGH);
    uint32_t outputWire = breadboard.createWire(false);

    breadboard.addPMOS(inputWireHigh, VCC, outputWire);
    breadboard.addNMOS(inputWireHigh, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireHigh)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }

    {
    uint32_t VCC = breadboard.createWire(true, State::HIGH);
    uint32_t GND = breadboard.createWire(true, State::LOW);

    uint32_t inputWireDisc = breadboard.createWire(true, State::DISCONNECTED);
    uint32_t outputWire = breadboard.createWire(false);


    breadboard.addPMOS(inputWireDisc, VCC, outputWire);
    breadboard.addNMOS(inputWireDisc, GND, outputWire);
    breadboard.evaluate();

    file << "Input: " << static_cast<int>(breadboard.getWireState(inputWireDisc)) << '\n';
    file << "Output: " << static_cast<int>(breadboard.getWireState(outputWire)) << "\n\n";
    breadboard.clear();
    }
    
}


void seriesnmos(std::ofstream& file)
{
    Circuit breadboard;
    {
        uint32_t VCC = breadboard.createWire(true, State::HIGH);
        uint32_t GND = breadboard.createWire(true, State::LOW);

        uint32_t inputHigh = breadboard.createWire(true, State::HIGH);
        uint32_t inputLow = breadboard.createWire(true, State::LOW);
        uint32_t intermediate = breadboard.createWire(false);
        uint32_t output = breadboard.createWire(false);

        breadboard.addNMOS(inputHigh, GND, intermediate);
        breadboard.addNMOS(inputLow, intermediate, output);
        breadboard.evaluate();

        file << "Adding NMOS in series with two inputs and same Output line" << '\n';
        file << "Input A: " << static_cast<int>(breadboard.getWireState(inputHigh)) << '\n';
        file << "Input B: " << static_cast<int>(breadboard.getWireState(inputLow)) << '\n';
        file << "Output: " << static_cast<int>(breadboard.getWireState(output)) << "\n\n\n";
        breadboard.clear();
    }

    {
        uint32_t VCC = breadboard.createWire(true, State::HIGH);
        uint32_t GND = breadboard.createWire(true, State::LOW);

        uint32_t inputHigh = breadboard.createWire(true, State::HIGH);
        uint32_t inputLow = breadboard.createWire(true, State::LOW);
        uint32_t output = breadboard.createWire(false);

        breadboard.addNMOS(inputLow, GND, output);
        breadboard.addNMOS(inputHigh, GND, output);
        breadboard.evaluate();

        file << "Input A: " << static_cast<int>(breadboard.getWireState(inputHigh)) << '\n';
        file << "Input B: " << static_cast<int>(breadboard.getWireState(inputLow)) << '\n';
        file << "Output: " << static_cast<int>(breadboard.getWireState(output)) << "\n\n\n";
        breadboard.clear();
    }

    {
        uint32_t VCC = breadboard.createWire(true, State::HIGH);
        uint32_t GND = breadboard.createWire(true, State::LOW);

        uint32_t inputHigh = breadboard.createWire(true, State::HIGH);
        uint32_t inputDisc = breadboard.createWire(true, State::DISCONNECTED);
        uint32_t output = breadboard.createWire(false);

        breadboard.addNMOS(inputHigh, GND, output);
        breadboard.addNMOS(inputDisc, GND, output);
        breadboard.evaluate();

        file << "Input A: " << static_cast<int>(breadboard.getWireState(inputHigh)) << '\n';
        file << "Input B: " << static_cast<int>(breadboard.getWireState(inputDisc)) << '\n';
        file << "Output: " << static_cast<int>(breadboard.getWireState(output)) << "\n\n\n";
        breadboard.clear();
    }
}