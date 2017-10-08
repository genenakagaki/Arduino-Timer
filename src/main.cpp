#include <Arduino.h>
#include "NumberDisplayer.h"
#include "ButtonListener.h"

int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

int resetPin = 11;
ButtonListener pauseListener;
bool paused = false;

NumberDisplayer numberDisplayer;

void updateNumber() {
  digit1++;
  if (digit1 == 10) {
    digit1 = 0;
    digit2++;
    if (digit2 == 10) {
      digit2 = 0;
      digit3++;
      if (digit3 == 10) {
        digit3 = 0;
        digit4++;
        if (digit4 == 10) {
          digit4 = 0;
        }
      }
    }
  }
}

void setup() {
  Serial.begin(9600);

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 45535;
  TCCR1B |= (1 << CS11); // prescaler 1
  TIMSK1 |= (1 << TOIE1); // enable timer overflow

  pinMode(resetPin, INPUT);
  pauseListener.setup(12);

  numberDisplayer.setup();
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 45535;
  Serial.println(millis());

  if (!paused) {
    updateNumber();
  }
}

void loop() {
  if (digitalRead(resetPin) == HIGH) {
    digit1 = 0;
    digit2 = 0;
    digit3 = 0;
    digit4 = 0;
  }

  int pauseState = pauseListener.readButtonUp();

  if (pauseState == HIGH) {
    paused = !paused;
  }

  numberDisplayer.displayNumber(digit4, digit3, digit2, digit1);
}
