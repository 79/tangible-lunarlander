#include "Keyboard.h";

#define DEBUG 0
#define GET_VAR_NAME(var) #var

const int leftPin = 5;
const int rightPin = 3;
const int upPin = 4;
//const int downPin = 4;
//const int buttonPin = 5;

void setup() {
  Serial.begin(9600);

  Keyboard.begin();

  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(upPin, INPUT_PULLUP);
//  pinMode(downPin, INPUT_PULLUP);
//  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // 1. Read current state
  int leftReading = digitalRead(leftPin);
  int rightReading = digitalRead(rightPin);
  int upReading = digitalRead(upPin);
//  int downReading = digitalRead(downPin);
//  int buttonReading = digitalRead(buttonPin);

  // 2. Map sensor readings to keyboard inputs
  if (leftReading == LOW) {
    Keyboard.press(KEY_LEFT_ARROW);
  } else {
    Keyboard.release(KEY_LEFT_ARROW);
  }

  if (rightReading == LOW) {
    Keyboard.press(KEY_RIGHT_ARROW);
  } else {
    Keyboard.release(KEY_RIGHT_ARROW);
  }

  if (upReading == LOW) {
    Keyboard.press(KEY_UP_ARROW);
  } else {
    Keyboard.release(KEY_UP_ARROW);
  }

//  if (downReading == LOW) {
//    Keyboard.press(KEY_DOWN_ARROW);
//  } else {
//    Keyboard.relase(KEY_DOWN_ARROW);
//  }
//
//  if (buttonReading == LOW) {
//    Keyboard.press(KEY_RETURN);
//  } else {
//    Keyboard.relase(KEY_RETURN);
//  }

  #ifdef DEBUG
    Serial.println("LEFT \t UP \t RIGHT");
    Serial.print(leftReading);
    Serial.print(" \t ");
    Serial.print(upReading);
    Serial.print(" \t ");
    Serial.println(rightReading);
  #endif
}
