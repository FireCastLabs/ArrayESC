# ArrayESC  [![Build Status](https://travis-ci.com/FireCastLabs/ArrayESC.svg?branch=master)](https://travis-ci.com/FireCastLabs/ArrayESC)

A sketch repository for Controlling an Array of 25 ESC driven motors with Adafruit PCA9685 16-Channel Servo Drivers and the I2C_Array_ESC library

## Summary
The sketch Based on [FireCastLabs/I2C_Array_ESC](https://github.com/FireCastLabs/I2C_Array_ESC) serial control example and extended to work with an array of 25 ESCs using four Adafruit PCA9685 16-Channel Servo Drivers on the I2C bus

## Supported platforms

This sketch is designed to work with the Arduino IDE versions 1.8.x or later; we have not tested it with earlier versions.  This sketch should support any Arduino-compatible board, Adafruit PCA9685 16-Channel Servo Drivers, and Aerostart RVS ESCs with reverse line function

## Getting Started
(a place holder for instructions of basic use)

### Hardware

Adafruit PCA9685 16-Channel Servo Drivers can be purchased on [Adafruit’s website](https://www.adafruit.com/product/815). See the [Adafruit PCA9685 16-Channel Servo Driver user’s guide and tutorial](https://learn.adafruit.com/16-channel-pwm-servo-driver/overview) for more details.

## Documentation

- no new functions have been added yet.
serial input commands
- 5
  - stop and reverse; must send 1000 once stopped then new speed command.
- 15
  - enter single potentiometer control
  - entering 20 while in potentiometer control will exit potentiometer control
- 1000 Zero throttle value and stops all motors
- 1050 aproximate minimum speed
- 2000 maximum speed

  ## Version History
  - no releases have been made yet
  - 2019/11/28 Pre-Prerelease major change; convert from broken I2C_ESC library to the working I2C_Array_ESC library. No version tags or releases have been made prior or with this change. This is only an informative note regarding a necessary change to this sketch.
