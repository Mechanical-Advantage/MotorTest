# MotorTest
Code for the 6328 Motor Test Rig

This repository holds code for the Team 6328 "Motor Test Rig".

In its initial form, this consists of:
* An Arduino Nano with:
  * 4 analog slider inputs
  * 4 button inputs
  * 4 LED outputs
  * 4 PWM pin header connections
* The 4 PWM pin headers connect to:
  * 2 Spark motor controllers
  * 2 Spark Max motor controllers
* Power distribution, including automotive self-resetting breakers for the controllers, and a fuse for the Arduino board.

This is intended to be a simple, stand-alone apparatus that can run up to 2 brushed motors (from the Sparks) and 2 brushless motors (from the SparkMAX's).  Separate controllers are used for brushed/brushless to make it simple to hook up motors without having to reconfigure anything, and reduce the risk that someone will damage a motor by failing to reconfigure a controller.

## User Requirements

* When connected to power, the software shall initially set all channels Off.
* Each time a button is pressed, the software shall toggle that channel between On and Off state.  
* The software shall ensure reliable button reading by debouncing the button inputs to prevent false triggers.
* The software shall set PWM channel outputs to the PWM pulse width needed to drive FRC standard motor controllers.  (Typically, pulse width of 1000 to 2000uS, with 1500 corresponding to "stop", 2000 as full forward and 1000 as full reverse).
* When a channel is on, the software shall set the motor speed based on the analog inputs.  
  * When a center-detent (midrange) position is read (nominal 2.5V), the software shall set the output pulse width to a "stopped" value.  (A deadband may be necessary.)
  * When an "up" direction is read (2.5V to 5V), the software shall set the output pulse width to a "forward" value proportional to the position.
  * When a "down" direction is read (0 to 2.5V), the software shall set the output pulse width to a "reverse" value proportional to the position.

## Arduino Nano Pinout

The Arduino Nano pinout is as follows.  

* PWM outputs: pins D3, D5, D6, D9 (all PWM capable: https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us)
* Analog inputs: pins A4, A5, A6, A7 (sliders connected to 5V/Gnd from Arduino, wiper contact connected to listed analog pins)
* LED "channel on" outputs: A0, A1, A2, A3 (used as digital outputs)
* Button "on/off" inputs (for toggling channel state on/off): D8, D10, D11, D12 (must be configured to use internal pullup resistors, pinmode INPUT_PULLUP)

Channels 1-4 are connected in pin order; e.g., channel 1 corresponds to PWM pin D3, analog input A4, LED output A0, button D8.  Each successive channel uses the next listed pin.

## See also

Here are some relevant examples from other projects and resources:

WPILib PWM information: https://docs.wpilib.org/en/stable/docs/software/actuators/pwm-controllers.html

A not-dissimilar project with example code: https://mrmctavish.wordpress.com/2020/03/15/using-an-arduino-to-control-a-talon-or-spark-motor-controller-using-pwm/

PWM library: https://code.google.com/archive/p/arduino-pwm-frequency-library/downloads

Another Arduino-controlled FRC motor controller project: https://www.instructables.com/Cheap-and-Easy-Arduino-Thrifty-Throttle-pwm-Genera/

Example of debouncing and toggling state with a button: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
