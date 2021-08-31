#pragma config(Sensor, dgtl1,  leftEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)
#define BASEDIST 562
void drive(int dist, int b_f){
	while(abs(SensorValue[rightEncoder]) < dist){
		if(abs(SensorValue[rightEncoder]) == abs(SensorValue[leftEncoder]))
			{
			motor[rightMotor] = 80*b_f;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 80*b_f;		    // Left Motor is run at power level 80
			}
		else if(SensorValue[rightEncoder] > abs(SensorValue[leftEncoder]))	// If rightEncoder has counted more encoder counts
		{
			motor[rightMotor] = 60*b_f;		    // Right Motor is run at power level 60
			motor[leftMotor]  = 80*b_f;		    // Left Motor is run at power level 80
		}
		else
		{
			// Turn slightly left
			motor[rightMotor] = 80*b_f;		    // Right Motor is run at power level 80
			motor[leftMotor]  = 60*b_f;		    // Left Motor is run at power level 60
		}
	}
}

void resetEncoder(){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

task main()
{
	wait1Msec(2000);							// Robot waits for 2000 milliseconds before executing program
	for (int i = 1; i < 6; i++) {
		resetEncoder();
		drive(BASEDIST*i,1);
		resetEncoder();
		drive(BASEDIST*i,-1);
}

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
