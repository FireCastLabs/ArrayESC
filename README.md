# ArrayESC  [![Build Status](https://travis-ci.com/FireCastLabs/ArrayESC.svg?branch=master)](https://travis-ci.com/FireCastLabs/ArrayESC)

A sketch repository for Controlling an Array of ESC driven motors with Adafruit PCA9685 16-Channel Servo Drivers

## Summary
The sketch Based on [RB-ENantel/RC_ESC library](https://github.com/RB-ENantel/RC_ESC) and extended to work with Adafruit PCA9685 16-Channel Servo Drivers on the I2C bus

## Supported platforms

This sketch is designed to work with the Arduino IDE versions 1.8.x or later; we have not tested it with earlier versions.  This sketch should support any Arduino-Mega-compatible boards Adafruit PCA9685 16-Channel Servo Drivers

## Getting Started
(a place holder for instructions of basic use)

### Hardware

Adafruit PCA9685 16-Channel Servo Drivers can be purchased on [Adafruit’s website](https://www.adafruit.com/product/815). See the [Adafruit PCA9685 16-Channel Servo Driver user’s guide and tutorial](https://learn.adafruit.com/16-channel-pwm-servo-driver/overview) for more details.

## Documentation

Due to a frequency issue encountered with the Adafruit PCA9685 16-Channel Servo Drivers and use as a library object in a Library we could only make this work as a sketch and could not make it work as a library. As such, the sketch and functions are all in one file. If we can work around this limitation this will become a library. 

- calib(int oPin)
  - Calibrate motor on specified pin
- arm(int oPin)
  - Arm motor on specified pin
- stop(int oPin)
  - Stop motor on specified pin
- speed(int oPin, int speed)
  - Set speed for motor on specified pin
  
  ## Version History
  - no releases have been made yet
