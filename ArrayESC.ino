/*************************************************** 
  This is Array of ESCs controlled with Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  PWM extender replacements in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface, and 2 pins for power and ground for a total of 4 pins.
  5 wires are used to chain the PWM extenders together

*****************************************************/
#include <I2C_Array_ESC.h>

#define LED_PIN (13)            // Pin for the LED 
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates
#define SPEED_MIN (1000)        // Set the Zero throttle Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum throttle Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define POT_PIN (A0)            // Analog pin used to connect the potentiometer

int potVal;                     // Variable to read the value from the analog pin
int oESC;                       // Variable for the speed sent to the ESC

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, Minimum Value, Maximum Value, Default Speed, Arm Value)
 * 8 ESC/motors per I2C PWM/Servo extender, 16 signals per extender 2 lines per ESC with 1 for motor and 1 for reverse pin
 * Total 4 I2C PWM/Servo extenders for the 25 motors leaving 13 available signals on the last I2C PWM driver
 */
I2C_Array_ESC motorsAH (0x40, SPEED_MIN, SPEED_MAX, ARM_VALUE); //First chip set of 8 motors
I2C_Array_ESC motorsIP (0x41, SPEED_MIN, SPEED_MAX, ARM_VALUE); //Second chip set of 8 motors
I2C_Array_ESC motorsQX (0x42,SPEED_MIN, SPEED_MAX, ARM_VALUE); //Third chip set of 8 motors
I2C_Array_ESC motorsY (0x43, SPEED_MIN, SPEED_MAX, ARM_VALUE); //Forth chip set of 1 motor

void setup()
{
  Serial.begin(9600);
  Serial.println("ESC I2C control!");

  /*
   * begin() calls the wire.begin() and is only done once per chipset
   */
  motorsAH.begin(); // First Chip set
  motorsIP.begin(); // Second Chip set
  motorsQX.begin(); // Third Chip set
  motorsY.begin(); // Fourth chip set

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You must 'calibrate' by tweaking this number until you get the PWM update frequency you're expecting!
   * The int.osc. is used for calculating things like writeMicroseconds
   * Analog servos run at ~50 Hz updates, It is very importaint to use an oscilloscope in setting the frequency 
   * for the I2C PCA9685 PWM/Servo extender chip. 
   * 1) Attach the oscilloscope to one of the PWM signal pin and ground on the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and affects the calculations for the PWM update frequency.
   * Failure to correctly set this value will cause unusual behavior in the ESCs
   * We only need to do this once per chipset
   */
  motorsAH.setOscillatorFrequency(24600000); // First Chip set
  motorsIP.setOscillatorFrequency(25000000); // Second Chip set
  motorsQX.setOscillatorFrequency(26075000); // Third Chip set
  motorsY.setOscillatorFrequency(26075000); // Fourth chip set

 /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale, 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
  * This is only done once per Adafruit PCA9685 PWM/Servo driver
  */
  motorsAH.setPWMFreq(SERVO_FREQ);
  motorsIP.setPWMFreq(SERVO_FREQ);
  motorsQX.setPWMFreq(SERVO_FREQ);
  motorsY.setPWMFreq(SERVO_FREQ);

  delay(10); // Set a small delay to allow the PCA9685 chips time to set their frequency
  pinMode(13, OUTPUT);  // LED Visual Output pin

  // Arm the ESCs for the motors
  motorsAH.armArray();
  motorsIP.armArray();
  motorsQX.armArray();
  motorsY.arm(0);

  digitalWrite(13, HIGH); // LED High Once ESCs are Armed
  delay(5000);  // Wait for a while for ESCs to be ready for all further commands

  /*
   * Set ESCs to the Zero throttle setting now that the ESCs should be Armed
   * This is necessary or the ESCs will not be able to work
   */
  motorsAH.speedArray(SPEED_MIN);
  motorsIP.speedArray(SPEED_MIN);
  motorsQX.speedArray(SPEED_MIN);
  motorsY.speed(0, SPEED_MIN);
}

void loop()
{
  if (Serial.available() > 0) // read the value from the serial
  {
    int oESC = Serial.parseInt();
    if (oESC == 5)
    {
      Serial.println("stopping and setting all ESCs to reverse mode");
      motorsAH.reverseArray();
      motorsIP.reverseArray();
      motorsQX.reverseArray();
      motorsY.reverse(1);
    }
    else if (oESC == 15)
    {
      while (1)
      {
        potVal = analogRead(POT_PIN);         // reads the value of the potentiometer (value between 0 and 1023)
        potVal = map(potVal, 0, 1023, SPEED_MIN, SPEED_MAX);  // scale it to use it with the ESC (value between Minimum and Maximum)
        // sets the Array ESC speed according to the scaled value from the potentiometer
        motorsAH.speedArray(potVal);
        motorsIP.speedArray(potVal);
        motorsQX.speedArray(potVal);
        motorsY.speed(0, potVal);
        Serial.print(potVal);
        Serial.println(" speed for all ESCs over pot");
        if (Serial.available() > 0)                             // read the value from the serial
        {
          oESC = Serial.parseInt();
          
          if (oESC == 20)
          {
            break;
          }
        }
      }
    }
    else
    {
      motorsAH.speedArray(oESC);
      motorsIP.speedArray(oESC);
      motorsQX.speedArray(oESC);
      motorsY.speed(0, oESC);
      Serial.print(oESC);
      Serial.println(" speed for all ESCs");
    }
  }

  delay(10); // Wait for a while before restarting the loop
}
