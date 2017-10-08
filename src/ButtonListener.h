#include <Arduino.h>

using namespace std;

class ButtonListener {

public:
  void setup(int buttonPin);
  int readButtonState();
  int readButtonUp();
};
