#pragma config(Sensor, in2,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Sensor, dgtl11, robot_stop,     sensorTouch)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop, reversed)

int threshold = 2000;

task stop_all(){
	while(!robot_stop || vexRT[Btn5D]!=1){
	}
	stopAllTasks();
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);          // The program waits for 2000 milliseconds before continuing.
	startTask(stop_all);

     /* found by taking a reading on both DARK and LIGHT    */
		/* surfaces, adding them together, then dividing by 2. */
		while(true)
		{
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
			displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
			displayLCDPos(1,0);                                     //  Sensor    |
			displayNextLCDNumber(SensorValue(lineFollowerLEFT));    //  Readings  |
			displayLCDPos(1,6);                                     //  to LCD.   |
			displayNextLCDNumber(SensorValue(lineFollowerCENTER));  //            |
			displayLCDPos(1,12);                                    //  L  C  R   |
			displayNextLCDNumber(SensorValue(lineFollowerRIGHT));   //  x  x  x   |
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+

		// RIGHT sensor sees dark:
		if(SensorValue(lineFollowerRIGHT) > threshold)
		{
			// counter-steer right:
			motor[leftMotor]  = 63;
			motor[rightMotor] = 0;
		}
		// Left sensor sees dark:
		if(SensorValue(lineFollowerLEFT) > threshold)
		{
			//counter-steer left:
			motor[leftMotor] = 0;
			motor[rightMotor] = 63;
		}

		// Left sensor sees dark:
		if(SensorValue(lineFollowerCENTER) > threshold)
		{
			//counter-steer left:
			motor[leftMotor] = 63;
			motor[rightMotor] = 63;
		}
	}
}
