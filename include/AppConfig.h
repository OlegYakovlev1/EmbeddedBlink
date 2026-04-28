#pragma once

#include <Arduino.h>

class AppConfig {
public:
  static constexpr uint8_t LED_PIN = 16;
  static constexpr uint8_t BUTTON_PIN = 15;

  static constexpr uint32_t BLINK_INTERVAL_MS = 500;
  static constexpr uint32_t DEBOUNCE_MS = 50;

  static constexpr uint16_t LOOP_MEASURE_INTERVAL = 3000;

  static const uint8_t SHORT_PRESS_BLINK_COUNT = 3;
};