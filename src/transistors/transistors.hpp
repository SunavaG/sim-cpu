#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>
#include <unordered_map>

enum class State : uint8_t
{
    HIGH = 1,
    LOW = 0,
    DISCONNECTED = 2,
    CONFLICT = 3,
};

struct Wire
{
    uint32_t id;
    bool isFixed; // connected to vcc, gnd, or input(basically externally driven)
    State currentState;
    State nextState;
};

struct Transistor
{
    bool isPMOS;
    uint32_t gateWireId;   // wire id connected to Gate
    uint32_t sourceWireId; // wire id connected to Source
    uint32_t drainWireId;  // wire id connected to Drain

    bool isConducting(State state) const
    {
        if (isPMOS)
            return state == State::LOW;
        else
            return state == State::HIGH;
    }; // check if the transistor is conducting or not
};

State resolveStates(State a, State b)
{
    if (a == State::CONFLICT || b == State::CONFLICT)
        return State::CONFLICT;

    if (a == State::DISCONNECTED)
        return b;

    if (b == State::DISCONNECTED)
        return a;

    if (a == b)
        return a;

    return State::CONFLICT;
}

class UnionFind
{
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;

public:
    UnionFind(size_t size) : parent(size), rank(size, 0)
    {
        for (size_t i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    size_t find(size_t x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void unite(size_t a, size_t b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return;
        }
        if (rank[a] < rank[b])
        {
            parent[a] = b;
        }
        else if (rank[a] > rank[b])
        {
            parent[b] = a;
        }
        else
        {
            parent[b] = a;
            rank[a]++;
        }
    }
};

class Circuit
{
private:
    std::vector<Wire> wires;
    std::vector<Transistor> transistors;

public:
    uint32_t createWire(bool isFixed, State initialState = State::DISCONNECTED)
    {
        uint32_t id = wires.size();
        wires.push_back({id, isFixed, initialState, initialState});
        return id;
    };

    void addPMOS(uint32_t gate, uint32_t source, uint32_t drain)
    {
        bool isPMOS = true;
        transistors.push_back({isPMOS, gate, source, drain});
    };

    void addNMOS(uint32_t gate, uint32_t source, uint32_t drain)
    {
        bool isPMOS = false;
        transistors.push_back({isPMOS, gate, source, drain});
    };

    void setWireState(uint32_t wireId, State state)
    {
        if (wireId < wires.size())
        {
            wires[wireId].currentState = state;
            wires[wireId].nextState = state;
        }
    }

    State getWireState(uint32_t wireId) const
    {
        if (wireId < wires.size())
        {
            return wires[wireId].currentState;
        }
        return State::DISCONNECTED;
    }

    void evaluate()
    {
        std::vector<bool> conducting(transistors.size(), false);

        for (uint32_t i = 0; i < transistors.size(); i++)
        {
            const auto &t = transistors[i];

            State gateVal = wires[t.gateWireId].currentState;
            conducting[i] = t.isConducting(gateVal);
        };

        UnionFind uf(wires.size());

        for (uint32_t i = 0; i < transistors.size(); i++)
        {
            if (!conducting[i])
                continue;

            const auto &t = transistors[i];
            uf.unite(t.sourceWireId, t.drainWireId);
        };

        for (auto &wire : wires)
        {
            if (!wire.isFixed)
            {
                wire.nextState = State::DISCONNECTED;
            }
        }

        std::unordered_map<size_t, State> componentState;

        for (size_t wireId = 0; wireId < wires.size(); wireId++)
        {
            if (!wires[wireId].isFixed)
                continue;

            const size_t root = uf.find(wireId);

            const State value = wires[wireId].currentState;

            auto iter = componentState.find(root);

            if (iter == componentState.end())
            {
                componentState.emplace(root, value);
            }
            else
            {
                iter->second = resolveStates(iter->second, value);
            }
        }

        for (size_t wireId = 0; wireId < wires.size(); wireId++)
        {
            if (wires[wireId].isFixed)
                continue;

            const size_t root = uf.find(wireId);

            auto iter = componentState.find(root);

            if (iter != componentState.end())
            {
                wires[wireId].nextState = iter->second;
            }
            else
            {
                wires[wireId].nextState = State::DISCONNECTED;
            }
        }

        for (auto &wire : wires)
        {
            wire.currentState = wire.nextState;
        }
    };

    bool settle(size_t maxIter = 128)
    {
        std::vector<State> before(wires.size());
        for (size_t i = 0; i < maxIter; ++i)
        {
            for (size_t j = 0; j < wires.size(); ++j)
                before[j] = wires[j].currentState;
            evaluate();
            bool stable = true;
            for (size_t j = 0; j < wires.size(); ++j)
                if (wires[j].currentState != before[j])
                {
                    stable = false;
                    break;
                }
            if (stable)
                return true;
        }
        return false;
    }

    void clear()
    {
        wires.clear();
        transistors.clear();
    }
};