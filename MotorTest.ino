#include <Servo.h>
#include <Wire.h>

Servo myservo;
int button1Pin = D8 int slider1Pin = A4 int led1Pin = A0;
int led1State = LOW; // stores the value from potentiometer
int button1State;
int lastButton1State = LOW; //

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(slider1Pin, INPUT);
  pinMode(led1Pin, OUTPUT);

  digitalWrite(led1Pin, led1state);
}

int IsButtonPressed(int buttonpin, int buttonReading, int buttonState,
                    int lastButtonState, int lastDebounceTime,
                    int debounceDelay, int ledState, int ledPin)
{

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (buttonReading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (buttonReading != buttonState)
    {
      buttonState = buttonReading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH)
      {
        led1State = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, led1State);
  return ledState;

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = buttonReading;
}

void loop()
{
  int button1Reading = digitalRead(button1Pin);
  if (IsButtonPressed() == HIGH)
  {
    // read slider values and set outputs based on those values
  }
}
