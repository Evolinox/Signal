# Arduino DB Signal Controller

This repository contains an Arduino sketch (`Signal.ino`) designed to control a German Railway (Deutsche Bahn H/V system) main signal and distant signal with realistic state transitions.

The script simulates an automated sequence featuring randomized aspect selection (proceed and shunting signals) and realistic waiting times.

---

## Features

* **Signal Aspects:**
  * **Hp0 (Stop):** Both red LEDs on the main signal light up.
  * **Hp1 (Proceed):** Green light on the main signal.
  * **Hp2 (Proceed at reduced speed):** Green and yellow lights on the main signal.
  * **Sh1 (Shunting permitted):** One red light and one white light on the main signal.
* **Automated Cycle Control:**
  * Random selection of the next signal aspect after the stop phase (Hp1, Hp2, or Sh1).
  * Dark switching (all lights turned off briefly before state change) to prevent invalid overlapping states.
* **Timing Control:**
  * Stop phase (train sequence time): approx. 3.5 minutes
  * Proceed phase (Hp1 / Hp2): 8 minutes
  * Shunting phase (Sh1): 20 seconds

---

## Hardware Requirements & Pinout

### Required Hardware
* Arduino board (e.g., Uno, Nano, Mega)
* Signal model (H/V main signal with distant signal LEDs)
* Current-limiting resistors for the LEDs
* Breadboard and jumper wires

### Pin Assignment (Arduino Digital Pins)

#### Main Signal (HP)
| Function | Pin | Description |
| :--- | :--- | :--- |
| **RED 1** | Pin 2 | First red light (Hp0 / Sh1) |
| **RED 2** | Pin 3 | Second red light (Hp00) |
| **GREEN** | Pin 4 | Green light (Hp1 / Hp2) |
| **YELLOW** | Pin 5 | Yellow light (Hp2) |
| **WHITE** | Pin 6 | White light (Sh1) |

#### Distant Signal (VR)
| Function | Pin | Description |
| :--- | :--- | :--- |
| **YELLOW 1** | Pin 7 | Yellow light 1 |
| **YELLOW 2** | Pin 8 | Yellow light 2 |
| **GREEN 1** | Pin 9 | Green light 1 |
| **GREEN 2** | Pin 10 | Green light 2 |

> [!NOTE]
> Analog pin A0 is left floating/unconnected to provide random noise for `randomSeed()`.

---

## Installation & Usage

1. **Clone or download the repository:**
   
```bash
   git clone https://github.com/Evolinox/Signal.git
```

2. **In Arduino IDE, upload the script to your Arduino board.**

3. **Wire everything up and power the Arduino board.**

## Disclaimer

This project is provided "as is", without warranty of any kind.

> [!WARNING]
> Please double-check your wiring and ensure that appropriate current-limiting resistors are connected to each LED before connecting power.
> The author of this repository takes no responsibility or liability for any damage to hardware, burnt out LEDs, microcontrollers, or any other equipment resulting from improper wiring, incorrect voltage levels, or faulty assembly.
> Proceed at your own risk.