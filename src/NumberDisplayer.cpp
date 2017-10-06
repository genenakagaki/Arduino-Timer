#include "NumberDisplayer.h"

static const int NUMBER_SEGMENT_COMBINATION[][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1 },
  { 1, 1, 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 0, 1, 1 },
  { 1, 0, 1, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 0, 0, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 0, 0, 1, 1 }
};

int latchPin = 9;
int clockPin = 8;
int dataPin = 10;

int digitPins[] = {2, 3, 4, 5};

byte segments = 0;

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, segments);
  digitalWrite(latchPin, HIGH);
}

void NumberDisplayer::setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void NumberDisplayer::displayNumber(int digit1, int digit2, int digit3, int digit4) {
  int digits[4] = {digit1, digit2, digit3, digit4};

  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW);
  }

  for (int segment = 0; segment < 7; segment++) {
    segments = 0;
    updateShiftRegister();
    for (int iDigit = 0; iDigit < 4; iDigit++) {
      int digit = digits[iDigit];
      if (NUMBER_SEGMENT_COMBINATION[digit][segment] == 1) {
        bitSet(segments, segment);
        digitalWrite(digitPins[digit], HIGH);
      }
    }
  }
}
