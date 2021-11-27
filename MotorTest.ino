#include <Servo.h>

#include <Wire.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // For "blink" test
}

void loop()
{
  // "Blink" code for testing connection to board
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(300);                      // wait for a second
}