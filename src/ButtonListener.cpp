#include "ButtonListener.h"

int buttonPin;
int buttonState;
int lastButtonState = LOW;

unsigned long lastDebouceTime = 0;
unsigned long debounceDelay = 50;

void ButtonListener::setup(int pin) {
  buttonPin = pin;
  pinMode(buttonPin, INPUT);
}

int ButtonListener::readButtonState() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebouceTime = millis();
  }

  if ((millis() - lastDebouceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
  }

  lastButtonState = reading;

  return buttonState;
}

int ButtonListener::readButtonUp() {
  int prevState = buttonState;
  readButtonState();

  if (prevState == HIGH && buttonState == LOW) {
    return HIGH;
  } else {
    return LOW;
  }
}
