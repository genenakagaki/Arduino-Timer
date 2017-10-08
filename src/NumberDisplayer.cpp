#include "NumberDisplayer.h"

static const bool NUMBER_SEGMENT_COMBINATION[][7] = {
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

byte segments = 1;

int digits[4];

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, segments);
  digitalWrite(latchPin, HIGH);
}

void NumberDisplayer::setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void displaySegment(int segment, int number, int digitPin) {
  if (NUMBER_SEGMENT_COMBINATION[number][segment]) {
    digitalWrite(digitPin, LOW);
  } else {
    digitalWrite(digitPin, HIGH);
  }
}

void displaySegmentOnAllDigits(int segment) {
  segments = 0;
  updateShiftRegister();
  bitSet(segments, segment);
  updateShiftRegister();

  displaySegment(segment, digits[0], 2);
  displaySegment(segment, digits[1], 3);
  displaySegment(segment, digits[2], 4);
  displaySegment(segment, digits[3], 5);
  delay(1);
}

void NumberDisplayer::displayNumber(int digit4, int digit3, int digit2, int digit1) {
  digits[0] = digit4;
  digits[1] = digit3;
  digits[2] = digit2;
  digits[3] = digit1;

  displaySegmentOnAllDigits(0);
  displaySegmentOnAllDigits(1);
  displaySegmentOnAllDigits(2);
  displaySegmentOnAllDigits(3);
  displaySegmentOnAllDigits(4);
  displaySegmentOnAllDigits(5);
  displaySegmentOnAllDigits(6);

  // dot
  segments = 0;
  updateShiftRegister();
  bitSet(segments, 7);
  updateShiftRegister();
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
