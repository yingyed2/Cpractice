#include <Arduino.h>

// assign digital IO pins
const int buttonPin = 2;
int ledPins[4] = {9, 10, 11, 12};

// global variables
uint8_t counter = 0;
int lastButtonState = 0;
unsigned long previousMillis = 0;
const unsigned long debounceDelay = 50;

// put your setup code here, to run once:
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// put your main code here, to run repeatedly:
void loop() {
  unsigned long currentMillis = millis();
  int currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == 0 && currentButtonState == HIGH) {
    if (currentMillis - previousMillis >= debounceDelay) {  // debouncing logic
      counter = (counter + 1);
      if (counter >= 16) {  // overflow logic (NOT COMPLETED)
          for (int i = 0; i < 4; i++) {
            digitalWrite(ledPins[i], LOW);
          }
          counter = 0;
          digitalWrite(LED_BUILTIN, HIGH);
        }
      for (int bit = 0; bit < 4; bit++) {   // counting

        uint8_t bitValue = (counter >> bit) & 0x01; // bit masking
        if (bitValue == 1) {
          digitalWrite(ledPins[bit], HIGH);
        } else {
          digitalWrite(ledPins[bit], LOW);
        } 
      }
      previousMillis = currentMillis;
    }
  }

  lastButtonState = currentButtonState;
}