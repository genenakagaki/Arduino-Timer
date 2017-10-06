#include <Arduino.h>
#include "NumberDisplayer.h"

NumberDisplayer numberDisplayer;
void setup() {
}

void loop() {
  numberDisplayer.displayNumber(0, 1, 1, 1);
}
