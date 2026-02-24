#include <Servo.h>
#include <Wire.h>

#define PWM_OFF 1500  // pulse width for stopped
#define PWM_MIN 1000  // pulse width for maximum reverse
#define PWM_MAX 2000  // pulse width for maximum forward

#define SPEED_DEADBAND 15     // range above/below center for "center off"
#define SPEED_ENDBAND 2       // range at ends to fix to min/max values
#define SPEED_VALUE_MIN 0     // Full reverse
#define SPEED_VALUE_MAX 1023  // Full forward
#define SPEED_VALUE_NEUTRAL 512

#define LED_UPDATE_INTERVAL 10  // ms
#define LED_BLINK_ON_COUNT 1    // in units of LED_UPDATE_INTERVAL
#define LED_BLINK_OFF_COUNT_SLOW 49
#define LED_BLINK_OFF_COUNT_FAST 0
#define LED_BLIP_ON_COUNT 1
#define LED_BLIP_OFF_COUNT 99

Servo myservo;

bool channelOn;  // Whether or not we are driving the output (non neutral)
int speedValue;  // SPEED_VALUE_MIN to SPEED_VALUE_MAX

const int buttonPin = 8;
const int ledPwrPin = 9;
const int ledFwdPin = 10;
const int ledRevPin = 11;
const int speedPin = A4;
const int pwmPin = 3;

int buttonState;
int lastButtonState;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 50;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.write("Start");
  int i;

  channelOn = false;  //channel OFF by default
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPwrPin, OUTPUT);
  pinMode(ledFwdPin, OUTPUT);
  pinMode(ledRevPin, OUTPUT);
  pinMode(speedPin, INPUT);
  lastButtonState = HIGH;  // Pulled up so it is HIGH
  buttonState = HIGH;      // Pulled up so it is HIGH
  myservo.attach(pwmPin);
  // Turn on all LEDS
  digitalWrite(ledPwrPin, HIGH);
  digitalWrite(ledFwdPin, HIGH);
  digitalWrite(ledRevPin, HIGH);
  // Leave LEDs on briefly to show they work
  delay(500);
  //Turn off all LEDS
  digitalWrite(ledPwrPin, LOW);
  digitalWrite(ledFwdPin, LOW);
  digitalWrite(ledRevPin, LOW);
}

void loop() {
  int i;
  int pwmValue;
  unsigned long currentMillis = millis();

  // Read/debounce button and update channel state
  isButtonPressed(buttonPin, buttonState, lastButtonState, channelOn);

  // Read current slider value
  speedValue = analogRead(speedPin);
  // Apply deadband
  if (speedValue < (SPEED_VALUE_NEUTRAL + SPEED_DEADBAND) && speedValue > (SPEED_VALUE_NEUTRAL - SPEED_DEADBAND)) {
    speedValue = SPEED_VALUE_NEUTRAL;
  }
  // Nail the ends of the range to limits
  if (speedValue >= (SPEED_VALUE_MAX - SPEED_ENDBAND)) {
    speedValue = SPEED_VALUE_MAX;
  }
  if (speedValue <= (SPEED_VALUE_MIN + SPEED_ENDBAND)) {
    speedValue = SPEED_VALUE_MIN;
  }
  // PWM pulse width is from 1000 to 2000, where 1500 is stopped
  // If channel is ON scale input reading to pulse width, otherwise use stop value
  pwmValue = channelOn ? map(speedValue, SPEED_VALUE_MIN, SPEED_VALUE_MAX, PWM_MIN, PWM_MAX) : PWM_OFF;
  // Set the output
  myservo.writeMicroseconds(pwmValue);

  if ((currentMillis - previousMillis) >= LED_UPDATE_INTERVAL) {
    previousMillis = currentMillis;
    updateLEDState();
  }
}

void updateLEDState() {
  // "blink" is used for the speed indicator LEDs (only one ever on at a time)
  static bool blinkState;
  static uint8_t blinkCount;
  uint8_t blinkOffCount;

  // "blip" is used for the standby state of the power LED
  static bool blipState;
  static uint8_t blipCount;

  // scale current speed to the appropriate blink off count
  if (speedValue > SPEED_VALUE_NEUTRAL) {
    // Forward
    blinkOffCount = map(speedValue, SPEED_VALUE_NEUTRAL, SPEED_VALUE_MAX,
                        LED_BLINK_OFF_COUNT_SLOW, LED_BLINK_OFF_COUNT_FAST);
  } else if (speedValue < SPEED_VALUE_NEUTRAL) {
    // Reverse
    blinkOffCount = map(speedValue, SPEED_VALUE_NEUTRAL, SPEED_VALUE_MIN,
                        LED_BLINK_OFF_COUNT_SLOW, LED_BLINK_OFF_COUNT_FAST);
  }

  blinkCount++;
  if (blinkState && (blinkCount >= LED_BLINK_ON_COUNT)) {
    blinkState = 0;
    blinkCount = 0;
  }
  if (!blinkState && (blinkCount >= blinkOffCount)) {
    blinkState = 1;
    blinkCount = 0;
  }

  blipCount++;
  if (blipState && (blipCount > LED_BLIP_ON_COUNT)) {
    blipState = 0;
    blipCount = 0;
  }
  if (!blipState && (blipCount > LED_BLIP_OFF_COUNT)) {
    blipState = 1;
    blipCount = 0;
  }

  Serial.print(channelOn);
  Serial.print(" ");
  Serial.print(speedValue);
  Serial.print(" ");
  Serial.println(blipState);

  if (channelOn) {
    digitalWrite(ledPwrPin, HIGH);
  } else {
    digitalWrite(ledPwrPin, blipState);
  }

  if (channelOn && speedValue > SPEED_VALUE_NEUTRAL) {
    // Forward
    digitalWrite(ledRevPin, LOW);
    digitalWrite(ledFwdPin, blinkState);
  } else if (channelOn && speedValue < SPEED_VALUE_NEUTRAL) {
    // Reverse
    digitalWrite(ledFwdPin, LOW);
    digitalWrite(ledRevPin, blinkState);
  } else {
    // Off / Neutral
    digitalWrite(ledFwdPin, LOW);
    digitalWrite(ledRevPin, LOW);
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
void isButtonPressed(int buttonPin, int &buttonState, int &lastButtonState, bool &channel) {
  int buttonReading = digitalRead(buttonPin);  // Current state of the button

  // If it's still changing, update the time it last changed
  if (buttonReading != lastButtonState) {
    debounceTime = millis();
  }

  // If it's been stable for long enough we can assess whether it's changed
  if ((millis() - debounceTime) > debounceDelay) {
    // Has it changed?
    if (buttonReading != buttonState) {
      buttonState = buttonReading;

      // If LOW the button is pressed, so switch channel state
      if (buttonState == LOW) {
        channel = !channel;
      }
    }
  }

  lastButtonState = buttonReading;
}