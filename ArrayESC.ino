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
#include <I2C_ESC.h>

#define LED_PIN (13)            // Pin for the LED 
#define SERVO_FREQ (60)         // Analog servos run at ~60 Hz updates
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds

int oESC;  // Variable for the speed sent to the ESC

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 * Total 4 I2C PWM/Servo extenders for the 25 motors leaving 13 available signals
 */
I2C_ESC motorA (0x40, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorB (0x40, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorC (0x40, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorD (0x40, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorE (0x40, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorF (0x40, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorG (0x40, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorH (0x40, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorI (0x41, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorJ (0x41, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorK (0x41, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorL (0x41, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorM (0x41, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorN (0x41, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorO (0x41, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorP (0x41, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorQ (0x42, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorR (0x42, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorS (0x42, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorT (0x42, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorU (0x42, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorV (0x42, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorW (0x42, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorX (0x42, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorY (0x43, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE);

void setup()
{
  Serial.begin(9600);
  Serial.println("ESC I2C control!");

  // Analog servos run at ~60 Hz updates, begin prescale at 105 to get approximatly 60Hz
  motorA.begin(105);
  motorB.begin(105);
  motorC.begin(105);
  motorD.begin(105);
  motorE.begin(105);
  motorF.begin(105);
  motorG.begin(105);
  motorH.begin(105);
  motorI.begin(105);
  motorJ.begin(105);
  motorK.begin(105);
  motorL.begin(105);
  motorM.begin(105);
  motorN.begin(105);
  motorO.begin(105);
  motorP.begin(105);
  motorQ.begin(105);
  motorR.begin(105);
  motorS.begin(105);
  motorT.begin(105);
  motorU.begin(105);
  motorV.begin(105);
  motorW.begin(105);
  motorX.begin(105);
  motorY.begin(105);

  delay(10);
  pinMode(13, OUTPUT);  // LED Visual Output

  // Arm the motors
  motorA.arm();
  motorB.arm();
  motorC.arm();
  motorD.arm();
  motorE.arm();
  motorF.arm();
  motorG.arm();
  motorH.arm();
  motorI.arm();
  motorJ.arm();
  motorK.arm();
  motorL.arm();
  motorM.arm();
  motorN.arm();
  motorO.arm();
  motorP.arm();
  motorQ.arm();
  motorR.arm();
  motorS.arm();
  motorT.arm();
  motorU.arm();
  motorV.arm();
  motorW.arm();
  motorX.arm();
  motorY.arm();

  digitalWrite(13, HIGH); // LED High Once Armed
  delay(1000);  // Wait for a while
}

void loop()
{
  if (Serial.available() > 0) // read the value from the serial
  {
    int oESC = Serial.parseInt();
    if (oESC == 5)
    {
      Serial.println("stopping and setting all ESCs to reverse mode");
      motorA.reverse();
      motorB.reverse();
      motorC.reverse();
      motorD.reverse();
      motorE.reverse();
      motorF.reverse();
      motorG.reverse();
      motorH.reverse();
      motorI.reverse();
      motorJ.reverse();
      motorK.reverse();
      motorL.reverse();
      motorM.reverse();
      motorN.reverse();
      motorO.reverse();
      motorP.reverse();
      motorQ.reverse();
      motorR.reverse();
      motorS.reverse();
      motorT.reverse();
      motorU.reverse();
      motorV.reverse();
      motorW.reverse();
      motorX.reverse();
      motorY.reverse();
    }
    else
    {
      motorA.speed(oESC);
      motorB.speed(oESC);
      motorC.speed(oESC);
      motorD.speed(oESC);
      motorE.speed(oESC);
      motorF.speed(oESC);
      motorG.speed(oESC);
      motorH.speed(oESC);
      motorI.speed(oESC);
      motorJ.speed(oESC);
      motorK.speed(oESC);
      motorL.speed(oESC);
      motorM.speed(oESC);
      motorN.speed(oESC);
      motorO.speed(oESC);
      motorP.speed(oESC);
      motorQ.speed(oESC);
      motorR.speed(oESC);
      motorS.speed(oESC);
      motorT.speed(oESC);
      motorU.speed(oESC);
      motorV.speed(oESC);
      motorW.speed(oESC);
      motorX.speed(oESC);
      motorY.speed(oESC);
      Serial.print(oESC);
      Serial.println(" speed for all ESCs");
    }
  }

  delay(10); // Wait for a while before restarting the loop
}
