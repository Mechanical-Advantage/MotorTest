#include <Servo.h>
#include <Wire.h>
Servo myservo;

//add channel state (simple bool)

const int buttonPin = 1;
const int ledPin = 2;
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
int buttonState;
int ledState = LOW;
int lastButtonState = LOW;
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



  //convert analog reading from a scale of 0-1023 to a scale of 0-5(volts)  
  
  if (pwm1Value < (2.5 + deadBand) && pwm1Value > (2.5 - deadBand))
  {
    myservo.writeMicroseconds(1500);// stop
  }

  if (pwm1Value > (2.5 + deadBand))
  {
    myservo.writeMicroseconds(((pwm1Value - (2.5 + deadBand)) * gain) + 1500);
  }

  if (pwm1Value < (2.5 - deadBand))
  {
    myservo.writeMicroseconds(((pwm1Value - (2.5 + deadBand)) * gain) + 1500);
  }

 
}
  

 //Debounce Button code 
void isButtonPressed(int ledPin, int buttonPin, int lastButtonState, int lastLedState, bool channel)
{
  buttonReading = digitalRead(buttonPin); 

  if (buttonReading != lastButtonState)
  {

    debounceTime = millis();

    if (millis() - debounceTime > debounceDelay)
    { 
      buttonState = buttonReading;

    if (buttonState == HIGH)
    {
      ledState = HIGH;
    }
    else if (buttonState == LOW)
    {
      ledState = LOW;
    }
    
    }
  }
  

  digitalWrite(ledPin, ledState);

  lastButtonState = buttonReading;

}



 