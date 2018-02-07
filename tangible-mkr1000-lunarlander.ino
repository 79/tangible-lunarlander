#include "Keyboard.h";
#include "Mouse.h";

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>;

#define DEBUG 1

const int thrustPin = 4;
const int startPin = 6;
const int resetPin = 1;
int oldResetState = HIGH;

bool started = false;

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
  /**
    1. Read current state
  */
  int startReading = digitalRead(startPin);
  int resetReading = digitalRead(resetPin);
  int thrustReading = digitalRead(thrustPin);
  long wheelPosition = wheel.read();

  /**
    2. Map sensor readings to keyboard inputs
  */
  // Start! (Only once)
  if (!started && startReading == LOW) {
    started = true;

    // Alfred
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
    Keyboard.releaseAll();

    Keyboard.write("l");
    Keyboard.write("u");
    Keyboard.write("n");
    Keyboard.write("a");
    Keyboard.write("r");

    Keyboard.write(KEY_RETURN);

    delay(3000);
  }

  // Reset, but only when transitoning from HIGH -> LOW
  if (oldResetState == HIGH && resetReading == LOW) {
    Mouse.click(MOUSE_LEFT);
  }
  oldResetState = resetReading;

  // Thrust button
  if (thrustReading == LOW) {
    Keyboard.press(KEY_UP_ARROW);
  } else {
    Keyboard.release(KEY_UP_ARROW);
  }

  // Determine LEFT or RIGHT for rotary encoder
  if (wheelPosition != oldPosition) {
    if (wheelPosition > oldPosition) {
      Keyboard.press(KEY_RIGHT_ARROW);
    } else {
      Keyboard.press(KEY_LEFT_ARROW);
    }

    oldPosition = wheelPosition;
  }

  // NOTE: Wait a little before we release from the rotary encoder!
  if (wheelPosition == oldPosition) {
    unsigned long newRotation = millis();

    if (newRotation - lastRotation > 30) {
      Keyboard.releaseAll();
      lastRotation = newRotation;
    }
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
