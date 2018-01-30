#include "Keyboard.h";

#define DEBUG 0
#define GET_VAR_NAME(var) #var

const int thrustPin = 4;
const int startPin = 6;
const int resetPin = 1;

void setup() {
  Serial.begin(9600);

  Keyboard.begin();

  pinMode(startPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(thrustPin, INPUT_PULLUP);
}

void loop() {
  // 1. Read current state
  int startReading = digitalRead(startPin);
  int resetReading = digitalRead(resetPin);
  int thrustReading = digitalRead(thrustPin);

  // 2. Map sensor readings to keyboard inputs
  if (startReading == LOW) {
    // TBD ON
  } else {
    // TBD OFF
  }

  if (resetReading == LOW) {
    // TBD RESET F5?
  } else {
    // TBD RESET F5?
  }

  if (thrustReading == LOW) {
    Keyboard.press(KEY_UP_ARROW);
  } else {
    Keyboard.release(KEY_UP_ARROW);
  }

  #ifdef DEBUG
    Serial.println("THRUST \t RESET \t START");
    Serial.print(thrustReading);
    Serial.print(" \t ");
    Serial.print(resetReading);
    Serial.print(" \t ");
    Serial.println(startReading);
  #endif
}
