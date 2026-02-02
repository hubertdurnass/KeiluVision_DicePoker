# 🎲 Dice Poker (Embedded C)

![Platform](https://img.shields.io/badge/Platform-NXP%20MKL05Z-blue)
![Architecture](https://img.shields.io/badge/Arch-Cortex--M0%2B-lightgrey)
![Language](https://img.shields.io/badge/Language-Embedded%20C-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)

A microcontroller-based implementation of a **Dice Poker** game, developed for the **NXP Kinetis MKL05Z4** platform. The project simulates strategic dice rolling mechanics with hardware-based randomness and direct peripheral control.

---

## 🎯 Project Objective

The goal of this project is to simulate a poker-style dice game where the user rolls five dice up to three times to achieve the best possible hand. It mimics aspects of probability theory and decision-making under uncertainty.

**Key Features:**
* **True Randomness:** Unlike standard software RNGs, this project generates random numbers by sampling **analog noise** (entropy) via the **ADC (Analog-to-Digital Converter)** on a floating pin.
* **Interactive Interface:** Users interact via a matrix keypad and view results on an LCD screen.

---

## 🕹️ Controls (Keypad 4x4)

The game is controlled using a matrix keypad with the following mapping:

| Key | Function |
|:---:|:---|
| **1 - 5** | Select/Hold specific dice (corresponding to positions 1-5) |
| **7** | **Confirm** dice selection |
| **8** | **Roll** the dice |
| **9** | **Next Turn** / Proceed |
| **0** | **End Game** / Reset |

---

## ⚙️ Hardware & Peripherals

The system interacts directly with hardware components using low-level drivers:

* **Microcontroller:** NXP Kinetis MKL05Z4 (ARM Cortex-M0+)
* **Display:** LCD 1602 (HD44780 controller) connected via **I2C**.
* **Input:** 4x4 Matrix Keypad.
* **RNG Source:** ADC Channel 8 (Pin PTB11) measuring floating voltage noise.

---

## 📁 Code Structure & Modules

The codebase is modular, separating hardware drivers from game logic:

* `main.c`: Handles the core game loop, state machine, and user decision flow.
* `klaw2.c`: Driver for scanning the 4x4 matrix keypad (`k_read` function).
* `ADC.c`: Configures the ADC to sample noise for seed generation (`ADC_Init`, `make_a_dice_roll`).
* `i2c.c` / `lcd1602.c`: Implements I2C communication protocol to drive the display (`show_dice_lcd`).

---

## 🚀 How to Build & Flash

1.  Open the project file (`*.uvprojx`) in **Keil uVision 5**.
2.  Select the target device: **MKL05Z32xxx4**.
3.  Build the project (**F7**).
4.  Flash to the FRDM-KL05Z board using the on-board OpenSDA programmer.

---

## 📄 Documentation

For detailed flowcharts, electrical diagrams, and logic description, please refer to the full documentation:
[📥 Final_Documentation_ang.pdf](Final_Documentation_ang.pdf)

---

### 👨‍💻 Author
**Hubert Durnaś** (AGH UST)
