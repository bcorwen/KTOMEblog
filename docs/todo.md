[Dev blog](devblog.md) | [Project aims and goals](goals.md) | [Project to-do](todo.md) | [Youtube playlist](https://www.youtube.com/watch?v=8m7peVlW2mE&list=PLJqFvAhkcSkkks42zClG5WlvO1khFZCKK) | [KTANE IRL Discord server](https://discord.com/channels/711013430575890432)

---

# Current Tasks

- [x] : Refine sound cues by adding local back-up timer to widget ESP
- [x] : Alter sound amp circuit to make full range of input voltage range
- [x] : Tweek CAN setup (possibly pull out into another header or otherwise make simpler to define)
- [x] : Insert game over effects (shut down all lights and flash timer on success, or flash all lights briefly before going dark on failure)
- [x] : Convert previously coded modules to work on ESP and interact with CAN bus (Button, Wires and Simon says)

---

# Project To-do List

Module | Find components | Programming | Schematic | PCB built | Physical design | Print and build
--- | --- | --- | --- | --- | --- | ---
Timer | x | x | x | - | x | x
Widgets | x | x | x | - | - | -
Wires | x | x | x | - | x | x
Button | x | x | x | - | x | x
Keypads | x | x | x | - | x | x
Simon Says | x | x | x | - | x | x
Who's on First | - | - | - | - | - | -
Memory | x | x | x | - | x | x
Morse Code | x | x | x | - | - | -
Complicated Wires | x | x | x | - | - | -
Wire Sequences | - | - | - | - | - | -
Mazes | x | - | - | - | - | -
Passwords | x | x | x | - | x | x
Venting Gas | x | x | x | - | - | -
Capacitor Discharge | - | - | - | - | - | -
Knobs | - | - | - | - | - | -

---

## Programming

- [x] : Basic game logic common to all modules
- [x] : CAN communication between modules
- [x] : BLE communication between Master ESP32 and phone app
- [x] : Complete timer (Master) module
- [ ] : Complete standard modules (in progress)
- [ ] : Complete needy modules

## Design

- [x] : Basic module designs
- [x] : Case and edgework
- [ ] : Find electronics which matches game as closely as possible (in progress)
- [ ] : Power solution (in progress - 5V 18600 cells likely)
- [x] : Module connectors (in progress - USB type-A)
- [ ] : Complete standard modules
- [ ] : Complete needy modules
