#include <Servo.h>
#include <Wire.h>

#define MAX_CHAN 4
#define PWM_OFF 1500 // pulse width for stopped
#define PWM_MIN 1000 // pulse width for maximum reverse
#define PWM_MAX 2000 // pulse width for maximum forward

Servo myservo[MAX_CHAN];
bool channel[MAX_CHAN];
int buttonState[MAX_CHAN];
int lastButtonState[MAX_CHAN];

// These arrays hold the Arduino pin identifiers for channels 1,2,3,4 in order
const int buttonPin[] = {8, 10, 11, 12};
const int ledPin[] = {A0, A1, A2, A3};
const int sliderPin[] = {A4, A5, A6, A7};
const int pwmPin[] = {3, 5, 6, 9};

unsigned long debounceTime = 0;
const unsigned long debounceDelay = 50;

void setup()
{
  //  Serial.begin(9600);
  //  Serial.write("Start");
  int i;

  for (i = 0; i < MAX_CHAN; i++)
  {
    channel[i] = false; //channel OFF by default
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);
    pinMode(sliderPin[i], INPUT);
    lastButtonState[i] = HIGH; // Pulled up so it is HIGH
    buttonState[i] = HIGH;     // Pulled up so it is HIGH
    myservo[i].attach(pwmPin[i]);
    // Turn on all LEDS
    digitalWrite(ledPin[i], HIGH);
  }

  // Leave LEDs on briefly to show they work
  delay(500);

  //Turn off all LEDS
  for (i = 0; i < MAX_CHAN; i++)
  {
    digitalWrite(ledPin[i], LOW);
  }
}

void loop()
{
  int i;
  int pwmValue;
  int sliderValue;

  for (i = 0; i < MAX_CHAN; i++)
  {
    // Read/debounce button and update channel state
    isButtonPressed(buttonPin[i], buttonState[i], lastButtonState[i], channel[i]);
    // Update LED representing the channel state
    digitalWrite(ledPin[i], channel[i] ? HIGH : LOW);
    // Read current slider value
    sliderValue = analogRead(sliderPin[i]);
    // PWM pulse width is from 1000 to 2000, where 1500 is stopped
    // If channel is ON scale input reading to pulse width, otherwise use stop value
    pwmValue = channel[i] ? map(sliderValue, 0, 1023, PWM_MIN, PWM_MAX) : PWM_OFF;
    // Set the output
    myservo[i].writeMicroseconds(pwmValue);
  }
}

// Debounce Button code
//
// Reads a button, applies debouncing logic, and changes channel state if pressed
//
// buttonPin: which pin to read
// buttonState: reference to variable holding current button state
// lastButtonState: reference to variable holding previous button state
// channel: reference to the channel state associated with this button
void isButtonPressed(int buttonPin, int &buttonState, int &lastButtonState, bool &channel)
{
  int buttonReading = digitalRead(buttonPin); // Current state of the button

  // If it's still changing, update the time it last changed
  if (buttonReading != lastButtonState)
  {
    debounceTime = millis();
  }

  // If it's been stable for long enough we can assess whether it's changed
  if ((millis() - debounceTime) > debounceDelay)
  {
    // Has it changed?
    if (buttonReading != buttonState)
    {
      buttonState = buttonReading;

      // If LOW the button is pressed, so switch channel state
      if (buttonState == LOW)
      {
        channel = !channel;
      }
    }
  }

  lastButtonState = buttonReading;
}