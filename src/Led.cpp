#include "Led.h"

Led::Led(uint8_t pin)
  : pin_(pin) {}

void Led::init() const {
  pinMode(pin_, OUTPUT);
  set(LedState::Off);
}

void Led::set(LedState state) const {
  digitalWrite(pin_, state == LedState::On ? HIGH : LOW);
}