#include <Servo.h>
#include <Wire.h>
Servo myservo;

//add channel state (simple bool)

const int button1Pin = 1;
const int led1Pin = 2;
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

int button1State;
int button2State;
int button3State;
int button4State;

int lastButton1State = LOW;
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
  channel1 = false;
  channel2 = false;
  channel3 = false;
  channel4 = false;

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  myservo.attach(3);
}

void loop()
{
  //pwmValue = digitalRead(D3);    //PWM input first pin: D3
  slider1Value = analogRead(A4); //analog input first pin: A4
  slider2Value = analogRead(A5);
  slider3Value = analogRead(A6);
  slider4Value = analogRead(A7);

  int pwm1Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm2Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm3Value = map(slider1Value, 0, 1023, 0, 5);
  int pwm4Value = map(slider1Value, 0, 1023, 0, 5);

  isButtonPressed(led1Pin, button1Pin, lastButton1State, channel1)
  toggleChannelState(channel1)
  toggleLEDState(led1State)
  slider(pwm1Value)

}


//convert analog reading from a scale of 0-1023 to a scale of 0-5(volts)  
  void slider(pwmValue)
  {
    if (pwmValue < (2.5 + deadBand) && pwmValue > (2.5 - deadBand))
  {
    myservo.writeMicroseconds(1500);// stop
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
  

 //Debounce Button code 
void isButtonPressed(int ledPin, int buttonPin, int lastButtonState, bool channel)
{
  buttonReading = digitalRead(buttonPin); 

  if (buttonReading != lastButtonState)
  {

    debounceTime = millis();

    if (millis() - debounceTime > debounceDelay)
    { 
      buttonState = buttonReading;
    
    }
  }
  

  digitalWrite(ledPin, ledState);

  lastButtonState = buttonReading;

}

void toggleChannelState(channel)
{
  if (buttonstate == HIGH)
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

void togleLEDState(ledState)
{
  if (buttonstate == HIGH)
  {
    if (ledState == HIGH)
    {
      ledState = LOW;
    }

    if (ledState == LOW)
    {
      ledState = HIGH;
    }
  }
}



 