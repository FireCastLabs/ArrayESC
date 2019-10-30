/*************************************************** 
  This is Array of ESCs controlled with Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  PWM extender replacements in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface, and 2 pins for power and ground for a total of 4 pins.
  5 wires are used to chain the PWM extenders together


 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// Instantiate the PWM extenders
Adafruit_PWMServoDriver ESC = Adafruit_PWMServoDriver(0x40);
//Adafruit_PWMServoDriver ESC2 = Adafruit_PWMServoDriver(0x41);

#define FREQ 60 // Analog servos run at ~60 Hz updates
#define OUTPUTMIN 1000
#define OUTPUTMAX 2000
#define ARMVAL 500
#define ESC_CAL_DELAY 8000
#define ESC_STOP_PULSE 500
#define motorA 0
#define motorB 1
#define motorC 2
#define motorD 3
#define motorE 4
#define motorF 5
#define motorG 6
#define motorH 7
#define motorI 8
#define motorJ 9
#define motorK 10
#define motorL 11
#define motorM 12
#define motorN 13
#define motorO 14
#define motorP 15
//#define motorQ 0
//#define motorR 1
//#define motorS 2
//#define motorT 3
//#define motorU 4
//#define motorV 5
//#define motorW 6
//#define motorX 7
//#define motorY 8
/*
  Calibrate the maximum and minimum PWM signal the ESC is expecting
*/
void calib(int oPin)
{
  ESC.writeMicroseconds(oPin, OUTPUTMAX);
    delay(ESC_CAL_DELAY);
  ESC.writeMicroseconds(oPin, OUTPUTMIN);
    delay(ESC_CAL_DELAY);
  arm(oPin);
}

/*
  Arm the ESC
*/
void arm(int oPin)
{
  ESC.writeMicroseconds(oPin, ARMVAL);
}

/*
  Stop the ESC with the specified PWM signal the ESC is expecting
*/
void stop(int oPin)
{
  ESC.writeMicroseconds(oPin, ESC_STOP_PULSE);
}

/*
  Set the ESC Speed with the specified PWM signal the ESC is expecting
*/
void speed(int oPin, int outputESC)
{
  int oESC = constrain(outputESC, OUTPUTMIN, OUTPUTMAX);
  ESC.writeMicroseconds(oPin, oESC);
}


void setup() {
  Serial.begin(9600);
  Serial.println("ESC I2C control!");

  ESC.begin();
  ESC.setPWMFreq(FREQ);  // Analog servos run at ~60 Hz updates

  delay(10);
  pinMode(13, OUTPUT);  // LED Visual Output
  arm(motorA);
  //ESC.writeMicroseconds(motorA,500);// Send the Arm value so the ESC will be ready to take commands
  digitalWrite(13, HIGH); // LED High Once Armed
  delay(1000);  // Wait for a while
  //ESC.writeMicroseconds(motorA, 1064);
  speed(motorA, 1064);
}

void loop() {
  if (Serial.available() > 0) // read the value from the serial
  {
    int oESC = Serial.parseInt();

    //ESC.writeMicroseconds(motorA, oESC);
    speed(motorA, oESC);
    Serial.print(oESC);
    Serial.println(" speed");

    delay(10); 
  } // Wait for a while before restart
}
