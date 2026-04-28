# ESP32 LED State Machine (Embedded C++)

This project demonstrates how to implement the classic "LED blink" using an **Embedded C++ approach** on ESP32.

Instead of using blocking delays, it applies:
- superloop architecture
- state machine design
- interrupts (ISR)
- compile-time configuration (`constexpr`, `static const`)

---

## 🚀 Features

- LED operates in three modes:
  - **Blinking**
  - **Always ON**
  - **Always OFF**
- Button cycles through modes
- Fully **non-blocking logic** using `millis()`
- Minimal ISR (best practice)
- Clean separation into multiple files

---

## 🧠 Concepts Used

- `enum class` for strong-typed states
- `constexpr` and `static const` for configuration
- `volatile` for ISR communication
- superloop architecture (no RTOS, no delay)
- hardware interrupt handling
- modular Embedded C++ structure

---

## 🔌 Hardware Setup

### LED

GPIO16 → LED → resistor → GND

### Button Module (VCC / OUT / GND)

VCC → 3.3V
GND → GND
OUT → GPIO15

---

## ⚙️ Button Logic

- Not pressed → `LOW (0)`
- Pressed → `HIGH (1)`
- Interrupt trigger: `RISING`

---

## 🔁 Operating Modes

| Mode        | LED Behavior        |
|------------|--------------------|
| Blinking   | Toggles periodically |
| Always ON  | LED stays ON        |
| Always OFF | LED stays OFF       |

---

## ⏱ Non-Blocking Timing

Instead of `delay()`, the project uses:
- `millis()` for timing
- state machine for behavior control

This ensures responsive input handling and scalable design.

---

## 📌 Notes

- Debounce is handled in `loop()`, not in ISR
- ISR is intentionally minimal (only sets a flag)
- No dynamic memory allocation
- No STL usage (embedded-friendly)
