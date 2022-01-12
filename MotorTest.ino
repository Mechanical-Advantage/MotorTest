#include <Servo.h>
#include <Wire.h>
Servo myservo;

// add channel state (simple bool)
const int button1Pin = 8;
const int led1Pin = A0;
const double deadBand = 0.5;
const double gain = 200;

bool channel1;
bool channel2;
bool channel3;
bool channel4;

int pwm1Value;
int pwm2Value;
int pwm3Value;
int pwm4Value;

int slider1Value;
int slider2Value;
int slider3Value;
int slider4Value;

int button1State = HIGH;
int button2State;
int button3State;
int button4State;

int lastButton1State = HIGH;
int lastButton2State = LOW;
int lastButton3State = LOW;
int lastButton4State = LOW;

int led1State = LOW;
int led2State = LOW;
int led3State = LOW;
int led4State = LOW;

int buttonReading;

unsigned long debounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
  Serial.begin(9600);
  Serial.write("Start");

  channel1 = false;
  channel2 = false;
  channel3 = false;
  channel4 = false;

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  myservo.attach(3);

  //  digitalWrite(A0, HIGH);
  //  delay(1000);
  //  digitalWrite(A0, LOW);
}

void loop()
{
  // pwmValue = digitalRead(D3);    //PWM input first pin: D3
  slider1Value = analogRead(A4); // analog input first pin: A4
  slider2Value = analogRead(A5);
  slider3Value = analogRead(A6);
  slider4Value = analogRead(A7);

  int pwm1Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm2Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm3Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm4Value = map(slider1Value, 0, 1023, 0, 5);

  isButtonPressed(button1Pin, button1State, lastButton1State, channel1);
  // Update LED representing the channel state
  digitalWrite(led1Pin, channel1 ? HIGH : LOW);

  toggleChannelState(channel1);
  toggleLEDState(led1State);
  slider(pwm1Value);
}

// convert analog reading from a scale of 0-1023 to a scale of 0-5(volts)
void slider(int pwmValue)
{
  if (pwmValue < (2.5 + deadBand) && pwmValue > (2.5 - deadBand))
  {
    myservo.writeMicroseconds(1500); // stop
  }

  if (pwmValue > (2.5 + deadBand))
  {
    myservo.writeMicroseconds(((pwmValue - (2.5 + deadBand)) * gain) + 1500);
  }

  if (pwmValue < (2.5 - deadBand))
  {
    myservo.writeMicroseconds(((pwmValue - (2.5 + deadBand)) * gain) + 1500);
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

void toggleChannelState(bool channel)
{
  if (button1State == HIGH)
  {
    if (channel == false)
    {
      channel = true;
    }

    if (channel == true)
    {
      channel = false;
    }
  }
}

void toggleLEDState(int ledState)
{
  if (channel1 == HIGH)
  {
    ledState = HIGH;
  }
  if (channel1 == LOW)
  {
    ledState = LOW;
  }
}
