#include <Servo.h>
#include <Wire.h> 
Servo myservo;   

//add channel state (simple bool)

const int buttonPin = 1; 
const int ledPin = 2;  
const double deadBand = 50;  

bool channel1; 
bool channel2; 
bool channel3; 
bool channel4;

int pwmValue; 
int sliderValue;
int buttonState; 
int ledState = LOW; 
int lastButtonState = LOW;  
int buttonReading;
 
unsigned long debounceTime = 0; 
unsigned long debounceDelay = 50;

void setup(){ 
  channel1 = false; 
  channel2 = false; 
  channel3 = false; 
  channel4 = false;

  pinMode(buttonPin, INPUT_PULLUP);   
  pinMode(ledPin, OUTPUT); 
  myservo.attach(3);
}

void loop(){  
  buttonReading = digitalRead(buttonPin);  
  pwmValue = analogRead(D3); //PWM input first pin: D3
  sliderValue = analogRead(A4); //analog input first pin: A4 
  
  int pwnValue = map(sliderValue, 0, 1023, 1000, 2000);
 //convert analog reading from a scale of 0-1023 to a scale of 0-5(volts) 

//set motor speeds based on analog inputs
  if(pwmValue < (1500 + deadBand) && pwnValue > (1500 - deadBand)) { 
    myservo.writeMicroseconds(1500);
  }

  if(pwmValue > (2.5 + deadBand)) { 
    myservo.writeMicroseconds(2000);
  }  

  if(pwmValue < (2.5 - deadBand)) { 
    myservo.writeMicroseconds(1000);
  }

//Debounce Button code --> turn this into a function
}  


int isButtonPressed(int ledPin, int buttonPin, int lastButtonState, int lastLedState) {

  if(buttonReading != lastButtonState) {
    debounceTime = millis(); 
  } 
  if(millis() - debounceTime > debounceDelay){ 
    if(buttonReading != buttonState) {
      buttonState = buttonReading;
    } 
    if(buttonState == HIGH){ 
      ledState = HIGH;
    }
  } 

  digitalWrite(ledPin, ledState);  

  lastButtonState = buttonReading; 
} 