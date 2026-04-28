#pragma once

#include <Arduino.h>

enum class LedState : uint8_t {
  Off,
  On
};

enum class LedMode : uint8_t {
  Blinking,
  AlwaysOn,
  AlwaysOff
};

LedMode nextMode(LedMode mode);