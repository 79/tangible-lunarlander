#include "Keyboard.h";

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>;

const int thrustPin = 4;
const int startPin = 6;
const int resetPin = 1;

Encoder wheel(5, 3);
long oldPosition = -999;
unsigned long lastRotation;


void setup() {
  Serial.begin(9600);

  Keyboard.begin();

  pinMode(startPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(thrustPin, INPUT_PULLUP);

  lastRotation = millis();
}

void loop() {
  // 1. Read current state
  int startReading = digitalRead(startPin);
  int resetReading = digitalRead(resetPin);
  int thrustReading = digitalRead(thrustPin);
  long wheelPosition = wheel.read();

  if (wheelPosition != oldPosition) {
    if (wheelPosition > oldPosition) {
      Keyboard.press(KEY_RIGHT_ARROW);
    } else {
      Keyboard.press(KEY_LEFT_ARROW);
    }

    oldPosition = wheelPosition;
  }

  if (wheelPosition == oldPosition) {
    unsigned long newRotation = millis();

    if (newRotation - lastRotation > 30) {
      Keyboard.release(KEY_LEFT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
      lastRotation = newRotation;
    }
  }

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
    Serial.println("WHEEL \t THRUST \t RESET \t START");
    Serial.print(wheelPosition);
    Serial.print(" \t ");
    Serial.print(thrustReading);
    Serial.print(" \t ");
    Serial.print(resetReading);
    Serial.print(" \t ");
    Serial.println(startReading);
  #endif
}
