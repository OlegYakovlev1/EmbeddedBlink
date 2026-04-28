#include <Arduino.h>

#include "AppConfig.h"
#include "Led.h"
#include "LedMode.h"

volatile bool buttonPressed = false;

void IRAM_ATTR handleButtonInterrupt() {
  buttonPressed = true;
}

LedMode nextMode(LedMode mode) {
  switch (mode) {
    case LedMode::Blinking:
      return LedMode::AlwaysOn;

    case LedMode::AlwaysOn:
      return LedMode::AlwaysOff;

    case LedMode::AlwaysOff:
      return LedMode::Blinking;

    default:
      return LedMode::Blinking;
  }
}

void setup() {
  Serial.begin(115200);

  static Led led(AppConfig::LED_PIN);
  led.init();

  pinMode(AppConfig::BUTTON_PIN, INPUT);

  attachInterrupt(
    digitalPinToInterrupt(AppConfig::BUTTON_PIN),
    handleButtonInterrupt,
    RISING
  );
}

void loop() {
  const uint32_t loopStartMicros = micros();

  static Led led(AppConfig::LED_PIN);

  static LedMode mode = LedMode::Blinking;
  static LedState ledState = LedState::Off;

  static uint32_t lastBlinkTime = 0;
  static uint32_t lastButtonTime = 0;

  static uint16_t loopCounter = 0;

  const uint32_t currentMillis = millis();

  if (buttonPressed) {
    buttonPressed = false;

    if (currentMillis - lastButtonTime >= AppConfig::DEBOUNCE_MS) {
      lastButtonTime = currentMillis;
      mode = nextMode(mode);
    }
  }

  switch (mode) {
    case LedMode::Blinking:
      if (currentMillis - lastBlinkTime >= AppConfig::BLINK_INTERVAL_MS) {
        lastBlinkTime = currentMillis;

        ledState = ledState == LedState::On
          ? LedState::Off
          : LedState::On;

        led.set(ledState);
      }
      break;

    case LedMode::AlwaysOn:
      ledState = LedState::On;
      led.set(LedState::On);
      break;

    case LedMode::AlwaysOff:
      ledState = LedState::Off;
      led.set(LedState::Off);
      break;

    default:
      mode = LedMode::Blinking;
      break;
  }

  loopCounter++;

  if (loopCounter >= AppConfig::LOOP_MEASURE_INTERVAL) {
    loopCounter = 0;

    const uint32_t loopTimeMicros = micros() - loopStartMicros;

    Serial.print("Loop time: ");
    Serial.println(loopTimeMicros);
  }
}