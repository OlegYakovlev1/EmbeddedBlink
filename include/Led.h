#pragma once

#include <Arduino.h>
#include "LedMode.h"

class Led {
public:
  explicit Led(uint8_t pin);

  void init() const;
  void set(LedState state) const;

private:
  const uint8_t pin_;
};