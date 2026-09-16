### How does a Computer Work?

Computers are made up of ROCK and SAND, quite literally.

And somehow, from these materials, we've managed to build machines that can perform mathematical operations billions of times faster than a human — while also rendering increasingly realistic jiggle physics.<br>
So... what exactly happened?

### So, what exactly is a Computer?

At the heart of modern computing is silicon, a semiconductor that is the core of most modern electronic devices.

Over the decades, engineers have managed to take computing from room-sized machines built for relatively simple calculations to devices small enough to fit in pockets, capable of running operating systems, rendering games, training neural networks, and threatening Software Developer jobs.

But none of that happens directly in silicon.

There's a ladder of abstractions between the material and the software running on top of it.

And near the bottom of that ladder is one of the most important inventions in modern computing:

### MOSFETs

MOSFET or Metal-Oxide-Semiconductor Field-Effect Transistor.

At a high level, a MOSFET can be thought of as a voltage-controlled switch.

A control voltage applied to its gate determines whether current can flow between the two terminals - Source and Drain.

Modern digital circuits primarily use two types:

NMOS — conducts when its gate is HIGH.

PMOS — conducts when its gate is LOW.

<br>
By combining these switches in carefully designed networks, we construct logic gates.

And those logic gates can then be combined into increasingly complex structures:
<br>
```
                    MOSFETs
                      ↓
                Logic Gates
                      ↓
            Adders / Multiplexers / Registers
                      ↓
                     ALU
                      ↓
                     CPU
                      ↓
                Instructions
                      ↓
                   Software
```

That's the journey this project is attempting to reproduce — starting at the transistor level and climbing the abstraction ladder one layer at a time.

### From the Concept to Code

So how do we represent a MOSFET in a program?

A transistor needs to know three things:

- Which wire controls its gate?

- Which wire is connected to one terminal?

- Which wire is connected to the other terminal?

That's represented by:

```
struct Transistor
{
    bool isPMOS;
    uint32_t gateWireId;
    uint32_t sourceWireId;
    uint32_t drainWireId;

    bool isConducting(State state) const
    {
        if (isPMOS)
            return state == State::LOW;
        else
            return state == State::HIGH;
    }
};
```
<br>
The important abstraction here is that this simulator isn't attempting to model the full analog physics of a MOSFET.

Instead, a transistor is treated as a switch:<br>

             Gate
               │
               ▼
          ┌─────────┐
          │ MOSFET  │
          └─────────┘
           │       │
         Source   Drain


If the transistor is conducting, its two terminals become electrically connected.

If it isn't conducting, they remain disconnected.

This simple abstraction is enough to construct digital logic from individual transistors — which is exactly where we're going next.