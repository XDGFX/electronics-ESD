#pragma config(Sensor, S1,     sideSensor,     sensorSONAR)
#pragma config(Sensor, S2,     frontSensor,    sensorSONAR)
#pragma config(Sensor, S3,     rightLightSensor, sensorLightActive)
#pragma config(Sensor, S4,     leftLightSensor, sensorLightActive)
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


task main()
{
  int sidedistance = 0;     // Will hold the values read in by the side Sonar Sensor.
  int frontdistance = 0;     // Will hold the values read in by the front Sonar Sensor.
  int leftlight = 0;     // Will hold the values read in by the left Light Sensor.
  int rightlight = 0;     // Will hold the values read in by the right Light Sensor.


  while(true)        // (infinite loop, also represented by 'while(1)).
  {
    sidedistance = SensorValue(sideSensor);               // Store side Sonar Sensor values in 'sonarValueSide' variable.
    frontdistance = SensorValue(frontSensor);							// Store front Sonar Sensor values in 'sonarValueFront' variable.
    leftlight = SensorValue(leftLightSensor);          // Store left Light Sensor values in 'lightValueLeft' variable.
    rightlight = SensorValue(rightLightSensor);				// Store right Light Sensor values in 'lightValueRight' variable.

    displayCenteredTextLine(0, "side distance");       /* Display side Sonar Sensor values */
    displayCenteredTextLine(1, "%d", sidedistance);   /* to LCD screen using %d.     */
    displayCenteredTextLine(2, "front distance");       /* Display front Sonar Sensor values */
 		displayCenteredTextLine(3, "%d", frontdistance);   /* to LCD screen using %d.     */
 		displayCenteredTextLine(4, "left light");       /* Display left Light Sensor values */
 		displayCenteredTextLine(5, "%d", leftlight);   /* to LCD screen using %d.     */
    displayCenteredTextLine(6, "Light right");       /* Display right Light Sensor values */
 		displayCenteredTextLine(7, "%d", rightlight);   /* to LCD screen using %d.     */
    wait1Msec(100);                                       // Only update the screen every 100 milliseconds.
   }
}
