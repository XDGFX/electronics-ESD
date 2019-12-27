#pragma config(Sensor, S1,     sideSensor,     sensorSONAR)
#pragma config(Sensor, S2,     frontSensor,    sensorSONAR)
#pragma config(Sensor, S3,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S4,     leftLightSensor, sensorLightActive)
#pragma config(Motor,  motorA,          leftmotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightmotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*  This program reads the light sensor and follow a line materialised by a black tape on a white floor   *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]               [Type]              [Description]                      *|
|*    Port A                  leftmotor              NXT                 Left motor                       *|
|*    Port B                  rightmotor             NXT                 Right motor                      *|
|*    Port 1                  sideSensor          Sonar Sensor           side facing                      *|
|*    Port 2                  frontSensor         Sonar Sensor           front facing                     *|
|*    Port 3                  rightLightSensor    Light Sensor           floor facing                     *|
|*    Port 4                  leftLightSensor     Light Sensor           floor facing                     *|
\*--------------------------------------------------------------------------------------------------------*/

//global variables
int sidedistance;    // Will hold the values read in by the side Sonar Sensor.
int frontdistance;   // Will hold the values read in by the front Sonar Sensor.
int leftlight;       // Will hold the values read in by the left Light Sensor.
int rightlight;      // Will hold the values read in by the right Light Sensor.
int threshold = 3;  // Define the threshold between black and white colors (white ~ 6; black ~ 1)//

void readsensors()
{
	sidedistance = SensorValue(sideSensor);               // Store side Sonar Sensor values in 'sonarValueSide' variable.
	frontdistance = SensorValue(frontSensor);							// Store front Sonar Sensor values in 'sonarValueFront' variable.
	leftlight = SensorValue(leftLightSensor);          // Store left Light Sensor values in 'lightValueLeft' variable.
	rightlight = SensorValue(rightLightSensor);				// Store right Light Sensor values in 'lightValueRight' variable.
	wait1Msec(100);
}

task main()
{
	while(true)        // (infinite loop, also represented by 'while(1)).
	{
		readsensors();
		if((leftlight > threshold)&&(rightlight > threshold))  // If both Light Sensors detect all white,
		{
			motor(leftmotor) = 20;                    // leftmotor is run at a 20 power level.
			motor(rightmotor) = 20;                   // rightmotor is run at a 20 power level.
		}

		if((leftlight < threshold)&&(rightlight > threshold))  // If left Light Sensor detects black and right Light sensor detects white,
		{
			motor(leftmotor) = 0;                  // leftmotor is run at a 0 power level.
			motor(rightmotor) = 20;                 // rightmotor is run at a 20 power level.
		}

		if((leftlight > threshold)&&(rightlight < threshold))  // If left Light Sensor detects white and right Light sensor detects black,
		{
			motor(leftmotor) = 20;                  // leftmotor is run at a 20 power level.
			motor(rightmotor) = 0;                  // rightmotor is run at a 0 power level.
		}

		if((leftlight < threshold)&&(rightlight < threshold))  // If the Light Sensor reads a value less than 45:
		{
			motor(leftmotor) = 0;                  // leftmotor is run at a 0 power level.
			motor(rightmotor) = 0;                 // rightmotor is run at a 0 power level.
		}

	}
}
