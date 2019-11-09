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
I2C_ESC motorA (0x40, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE); //First chip set of 8 motors
I2C_ESC motorB (0x40, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorC (0x40, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorD (0x40, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorE (0x40, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorF (0x40, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorG (0x40, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorH (0x40, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorI (0x41, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE); //Second chip set of 8 motors
I2C_ESC motorJ (0x41, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorK (0x41, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorL (0x41, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorM (0x41, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorN (0x41, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorO (0x41, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorP (0x41, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorQ (0x42, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE); //Third chip set of 8 motors
I2C_ESC motorR (0x42, 2, 3, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorS (0x42, 4, 5, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorT (0x42, 6, 7, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorU (0x42, 8, 9, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorV (0x42, 10, 11, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorW (0x42, 12, 13, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorX (0x42, 14, 15, SPEED_MIN, SPEED_MAX, ARM_VALUE);
I2C_ESC motorY (0x43, 0, 1, SPEED_MIN, SPEED_MAX, ARM_VALUE); //Forth chip set of 8 motors

void setup()
{
  Serial.begin(9600);
  Serial.println("ESC I2C control!");

  /*
   * Analog servos run at ~60 Hz updates, begin prescale at 105 to get approximatly 60Hz
   * Very importaint to only enter prescale for the PWM frequency with one motor on the chip.
   * Multiple setting of the frequency on the I2C PCA9685 PWM/Servo extender chip is likely to cause
   * unusual behavior
   */
  motorA.begin(105); // First Chip set
  motorB.begin();
  motorC.begin();
  motorD.begin();
  motorE.begin();
  motorF.begin();
  motorG.begin();
  motorH.begin();
  motorI.begin(105); // Second Chip set
  motorJ.begin();
  motorK.begin();
  motorL.begin();
  motorM.begin();
  motorN.begin();
  motorO.begin();
  motorP.begin();
  motorQ.begin(105); // Third Chip set
  motorR.begin();
  motorS.begin();
  motorT.begin();
  motorU.begin();
  motorV.begin();
  motorW.begin();
  motorX.begin();
  motorY.begin(105); // Fourth chip set

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. is closer to 27MHz and is used for calculating things like writeMicroseconds
   * We only need to do this once per chipset
   */
  motorA.setOscillatorFrequency(26075000); // First Chip set
  motorI.setOscillatorFrequency(26075000); // Second Chip set
  motorQ.setOscillatorFrequency(26075000); // Third Chip set
  motorY.setOscillatorFrequency(26075000); // Fourth chip set

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency
  pinMode(13, OUTPUT);  // LED Visual Output pin

  // Arm the ESCs for the motors
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

  digitalWrite(13, HIGH); // LED High Once ESCs are Armed
  delay(5000);  // Wait for a while

  /*
   * Set ESCs to minimum speed now that the ESCs should be Armed
   * This is necessary or the ESCs will not be able to work
   */
  motorA.speed(SPEED_MIN);
  motorB.speed(SPEED_MIN);
  motorC.speed(SPEED_MIN);
  motorD.speed(SPEED_MIN);
  motorE.speed(SPEED_MIN);
  motorF.speed(SPEED_MIN);
  motorG.speed(SPEED_MIN);
  motorH.speed(SPEED_MIN);
  motorI.speed(SPEED_MIN);
  motorJ.speed(SPEED_MIN);
  motorK.speed(SPEED_MIN);
  motorL.speed(SPEED_MIN);
  motorM.speed(SPEED_MIN);
  motorN.speed(SPEED_MIN);
  motorO.speed(SPEED_MIN);
  motorP.speed(SPEED_MIN);
  motorQ.speed(SPEED_MIN);
  motorR.speed(SPEED_MIN);
  motorS.speed(SPEED_MIN);
  motorT.speed(SPEED_MIN);
  motorU.speed(SPEED_MIN);
  motorV.speed(SPEED_MIN);
  motorW.speed(SPEED_MIN);
  motorX.speed(SPEED_MIN);
  motorY.speed(SPEED_MIN);
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
