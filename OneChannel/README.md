# MotorTest
Code for AdvantageRun, the 6328 single-channel motor controller.  This is adapted from the original 4-channel "Motor Test Rig".

AdvantageRun includes:
* An Arduino Nano with:
  * Analog potentiometer input for speed control
  * Button input for toggling the motor on/off
  * 3 LED outputs for standby/run, forward, reverse indication
  * 1 PWM pin output connections
* A self-resetting breaker for the motor.

This is intended to be a simple, stand-alone apparatus that can run a single motor at a time via PWM.

## User Requirements

* When connected to power, the software shall initially set outputPWM Off.
* Each time a button is pressed, the software shall toggle the output between On and Off state.  
* The software shall ensure reliable button reading by debouncing the button inputs to prevent false triggers.
* The software shall set PWM channel outputs to the PWM pulse width needed to drive FRC standard motor controllers.  (Typically, pulse width of 1000 to 2000uS, with 1500 corresponding to "stop", 2000 as full forward and 1000 as full reverse).
* When the PWM output is on, the software shall set the motor speed based on the analog inputs.  
  * When a center-detent (midrange) position is read (nominal 2.5V), the software shall set the output pulse width to a "stopped" value.  (A deadband may be necessary.)
  * When an "up" direction is read (2.5V to 5V), the software shall set the output pulse width to a "forward" value proportional to the position.
  * When a "down" direction is read (0 to 2.5V), the software shall set the output pulse width to a "reverse" value proportional to the position.

## Arduino Nano Pinout

The Arduino Nano pinout is as follows.  

* PWM outputs: pin D3 (PWM capable: https://store-usa.arduino.cc/products/arduino-nano?selectedStore=us)
* Analog inputs: pin A4 (potentiometer connected to 5V/Gnd from Arduino, wiper contact connected to analog pin)
* LED outputs: D9, D10, D11
* Button "on/off" input (for toggling channel state on/off): D8 (must be configured to use internal pullup resistors, pinmode INPUT_PULLUP)

## See also

Here are some relevant examples from other projects and resources:

WPILib PWM information: https://docs.wpilib.org/en/stable/docs/software/actuators/pwm-controllers.html

An Arduino-controlled FRC motor controller project: https://www.instructables.com/Cheap-and-Easy-Arduino-Thrifty-Throttle-pwm-Genera/
This uses the standard "Servo" library which seems like the most likely way to go.

A not-dissimilar project with example code: https://mrmctavish.wordpress.com/2020/03/15/using-an-arduino-to-control-a-talon-or-spark-motor-controller-using-pwm/
This one uses this PWM library: https://code.google.com/archive/p/arduino-pwm-frequency-library/downloads
HOWEVER, it seems that FRC controllers are more easily controlled using the "Servo" library, as in the earlier example.

Example of debouncing and toggling state with a button: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
