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

  isButtonPressed(led1Pin, button1Pin, lastButton1State, channel1);
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
void isButtonPressed(int ledPin, int buttonPin, int lastButtonState, bool channel)
{
  int buttonReading = digitalRead(buttonPin);

  Serial.print("INITIAL READ: ");
  Serial.print(buttonReading);
  Serial.print(" ");
  Serial.print(button1State);
  Serial.print(" ");
  Serial.println(channel1);

  if (buttonReading != lastButtonState)
  {

    debounceTime = millis();
    Serial.println("MILLIS UPDATE");
  }

    if ((millis() - debounceTime) > debounceDelay)
    {
      
      Serial.println("FIRST IF");

      if (buttonReading != button1State){

        Serial.println("SECOND IF");

        button1State = buttonReading;

        Serial.print("BUTTON STATE UPDATE: ");
        Serial.print(button1State);
        Serial.print(" ");
        Serial.println(channel1);

        if (button1State==LOW){
          channel1 = !channel1;

          Serial.print("CHANNEL STATE UPDATE: ");
          Serial.println(channel1);

        }

      }
      
    }
  

  digitalWrite(led1Pin, channel1 ? HIGH : LOW);

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
  if (channel1 == LOW){
    ledState = LOW;
  }
}
