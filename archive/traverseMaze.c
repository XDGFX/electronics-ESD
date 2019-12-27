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

// global variables
int sidedistance = 0;     // Will hold the values read in by the side Sonar Sensor.
int frontdistance = 0;     // Will hold the values read in by the front Sonar Sensor.
int leftlight = 0;     // Will hold the values read in by the left Light Sensor.
int rightlight = 0;     // Will hold the values read in by the right Light Sensor.
int thresholdLight = 45;          // Define the threshold between black and white colors (white ~ 50; black ~ 30)
int thresholdUltra = 20;  // threshold for ultrasongic sensors

void readsensors() {
	sidedistance = SensorValue(sideSensor);               // Store side Sonar Sensor values in 'sonarValueSide' variable.
	frontdistance = SensorValue(frontSensor);							// Store front Sonar Sensor values in 'sonarValueFront' variable.
	leftlight = SensorValue(leftLightSensor);          // Store left Light Sensor values in 'lightValueLeft' variable.
	rightlight = SensorValue(rightLightSensor);				// Store right Light Sensor values in 'lightValueRight' variable.
}

void drive() {
	while(true)        // While following a line
	{
		readsensors();
		if((leftlight > thresholdLight)&&(rightlight > thresholdLight))  // If both Light Sensors detect all white,
		{
			motor(leftmotor) = (leftlight - thresholdLight) * 3;                    // leftmotor is run at a 20 power level.
			motor(rightmotor) = (rightlight - thresholdLight) * 3;                   // rightmotor is run at a 20 power level.
		}

		if((leftlight < thresholdLight)&&(rightlight > thresholdLight))  // If left Light Sensor detects black and right Light sensor detects white,
		{
			motor(leftmotor) = 0;                  // leftmotor is run at a 0 power level.
			motor(rightmotor) = (rightlight - thresholdLight) * 10;                 // rightmotor is run at a 20 power level.
		}

		if((leftlight > thresholdLight)&&(rightlight < thresholdLight))  // If left Light Sensor detects white and right Light sensor detects black,
		{
			motor(leftmotor) = (leftlight - thresholdLight) * 10;                  // leftmotor is run at a 20 power level.
			motor(rightmotor) = 0;                  // rightmotor is run at a 0 power level.
		}

		if((leftlight < thresholdLight)&&(rightlight < thresholdLight))  // If the Light Sensor reads a value less than 45:
		{
			motor(leftmotor) = 0;                  // leftmotor is run at a 0 power level.
			motor(rightmotor) = 0;                 // rightmotor is run at a 0 power level.
			return;
		}

	}
}

void checkDir() {
	readsensors();

	// Check left
	if(sidedistance > thresholdUltra){

		playTone(500, 30);
		motor(rightmotor) = 20;
		motor(leftmotor) = -20;

		wait1Msec(353);

		while(rightlight > thresholdLight){
			readsensors();
		}

		motor(rightmotor) = 0;
		motor(leftmotor) = 0;

		} else if(frontdistance < thresholdUltra) {
		// turn right

		motor(rightmotor) = -20;
		motor(leftmotor) = 20;

		wait1Msec(353);

		while(rightlight > thresholdLight){
			readsensors();
		}

		motor(rightmotor) = 0;
		motor(leftmotor) = 0;

	}
}

task main() {

	while(true) {
		drive();

		motor(rightmotor) = 20;
		motor(leftmotor) = 20;
		wait1Msec(700);

		checkDir();
	}

}
