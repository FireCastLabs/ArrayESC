/*************************************************** 
  This is Array of ESCs controlled with Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  PWM extender replacements in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface, and 2 pins for power and ground for a total of 4 pins.
  5 wires are used to chain the PWM extenders together

  Serial parsing example from  Example 5 - Receive with start- and end-markers combined with parsing
  http://forum.arduino.cc/index.php?topic=396450

*****************************************************/
#include <I2C_ESC.h>

#define LED_PIN (13)            // Pin for the LED 
#define SERVO_FREQ (50)         // Analog servos run at ~50 Hz updates
#define SPEED_MIN (1000)        // Set the Zero Throttle Speed in microseconds
#define SPEED_MAX (2000)        // Set the Maximum Speed in microseconds
#define ARM_VALUE (500)         // Set the Arm value in microseconds
#define POT_PIN (A0)            // Analog pin used to connect the potentiometer

int potVal;                     // Variable to read the value from the analog pin
int oESC;                       // Variable for the speed sent to the ESC

/**
 * variables for parsing
 * 
**/
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array for use when parsing
// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;

/*
 * Instantiate the PWM extenders
 * ESC_Name (I2C_address, ESC PIN, reverse pin, Zero throttle Value, Maximum Value, Arm Value)
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
  Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
  Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
  Serial.println()

  /*
   * Multiple setting of the I2C bus on the I2C PCA9685 PWM/Servo extender chip is likely to cause
   * unusual behavior
   * begin() calls the wire.begin() and should only be done once per chipset
   * Analog servos run at ~50 Hz updates, begin prescale at ### to get approximatly 50Hz
   */
  motorA.begin(); // First Chip set
  motorI.begin(); // Second Chip set
  motorQ.begin(); // Third Chip set
  motorY.begin(); // Fourth chip set

  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't that precise. 
   * You can 'calibrate' by tweaking this number till you get the frequency you're expecting!
   * The int.osc. a range between about 23-27MHz and is used for calculating things like writeMicroseconds
   * We need to do this for each library instance as it is used in internal library calculations
   */
  motorA.setOscillatorFrequency(24675000); // First Chip set
  motorB.setOscillatorFrequency(24675000);
  motorC.setOscillatorFrequency(24675000);
  motorD.setOscillatorFrequency(24675000);
  motorE.setOscillatorFrequency(24675000);
  motorF.setOscillatorFrequency(24675000);
  motorG.setOscillatorFrequency(24675000);
  motorH.setOscillatorFrequency(24675000);
  motorI.setOscillatorFrequency(25000000); // Second Chip set
  motorJ.setOscillatorFrequency(25000000);
  motorK.setOscillatorFrequency(25000000);
  motorL.setOscillatorFrequency(25000000);
  motorM.setOscillatorFrequency(25000000);
  motorN.setOscillatorFrequency(25000000);
  motorO.setOscillatorFrequency(25000000);
  motorP.setOscillatorFrequency(25000000);
  motorQ.setOscillatorFrequency(26075000); // Third Chip set
  motorR.setOscillatorFrequency(24675000);
  motorS.setOscillatorFrequency(24675000);
  motorT.setOscillatorFrequency(24675000);
  motorU.setOscillatorFrequency(24675000);
  motorV.setOscillatorFrequency(24675000);
  motorW.setOscillatorFrequency(24675000);
  motorX.setOscillatorFrequency(24675000);
  motorY.setOscillatorFrequency(26075000); // Fourth chip set

 /*
  * Set the analog servo PWM frequency
  * alternativly you could set this using the prescale 50Hz is a prescale of about ### (depending on the internal oscillator frequency)
  * We need to do this for each library instance as it is used in internal library calculations
  */
  motorA.setPWMFreq(SERVO_FREQ); // First Chip set
  motorB.setPWMFreq(SERVO_FREQ);
  motorC.setPWMFreq(SERVO_FREQ);
  motorD.setPWMFreq(SERVO_FREQ);
  motorE.setPWMFreq(SERVO_FREQ);
  motorF.setPWMFreq(SERVO_FREQ);
  motorG.setPWMFreq(SERVO_FREQ);
  motorH.setPWMFreq(SERVO_FREQ);
  motorI.setPWMFreq(SERVO_FREQ); // Second Chip set
  motorJ.setPWMFreq(SERVO_FREQ);
  motorK.setPWMFreq(SERVO_FREQ);
  motorL.setPWMFreq(SERVO_FREQ);
  motorM.setPWMFreq(SERVO_FREQ);
  motorN.setPWMFreq(SERVO_FREQ);
  motorO.setPWMFreq(SERVO_FREQ);
  motorP.setPWMFreq(SERVO_FREQ);
  motorQ.setPWMFreq(SERVO_FREQ); // Third Chip set
  motorR.setPWMFreq(SERVO_FREQ);
  motorS.setPWMFreq(SERVO_FREQ);
  motorT.setPWMFreq(SERVO_FREQ);
  motorU.setPWMFreq(SERVO_FREQ);
  motorV.setPWMFreq(SERVO_FREQ);
  motorW.setPWMFreq(SERVO_FREQ);
  motorX.setPWMFreq(SERVO_FREQ);
  motorY.setPWMFreq(SERVO_FREQ); // Fourth chip set

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
  delay(5000); // Wait for a while for all ESCs to be ready for commands

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
    recvWithStartEndMarkers();

    if (newData == true)
    {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            // because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
}

// helper functions

//============

void recvWithStartEndMarkers()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;

                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
}

// split the data into its parts
void parseData()
{
    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,","); // get the first part - the string
    strcpy(messageFromPC, strtokIndx);  // copy it to messageFromPC

    strtokIndx = strtok(NULL, ",");   // this continues where the previous call left off
    integerFromPC = atoi(strtokIndx); // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);   // convert this part to a float
}

void showParsedData()
{
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(integerFromPC);
    Serial.print("Float ");
    Serial.println(floatFromPC);
}


void oldparsing()
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
    else if (oESC == 15)
    {
      while (1)
      {
        potVal = analogRead(POT_PIN);         // reads the value of the potentiometer (value between 0 and 1023)
        potVal = map(potVal, 0, 1023, SPEED_MIN, SPEED_MAX);  // scale it to use it with the ESC (value between Minimum and Maximum)
        // sets the Array ESC speed according to the scaled value from the potentiometer
        motorA.speed(potVal);
        motorB.speed(potVal);
        motorC.speed(potVal);
        motorD.speed(potVal);
        motorE.speed(potVal);
        motorF.speed(potVal);
        motorG.speed(potVal);
        motorH.speed(potVal);
        motorI.speed(potVal);
        motorJ.speed(potVal);
        motorK.speed(potVal);
        motorL.speed(potVal);
        motorM.speed(potVal);
        motorN.speed(potVal);
        motorO.speed(potVal);
        motorP.speed(potVal);
        motorQ.speed(potVal);
        motorR.speed(potVal);
        motorS.speed(potVal);
        motorT.speed(potVal);
        motorU.speed(potVal);
        motorV.speed(potVal);
        motorW.speed(potVal);
        motorX.speed(potVal);
        motorY.speed(potVal);
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