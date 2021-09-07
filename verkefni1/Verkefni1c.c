#pragma config(Sensor, dgtl1,  leftEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)
#define BASEDEG 2.7
#define BASEDIST 562
int turnArray[14] = {1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1};
//bool turnArray[14] = {1,0,0,1,1,0,1,1,0,1,1,0,0,1};
//char turnArray[4] = {'L','R','L','R'};
void turn(float deg, int leftOrRight){
	while(abs(SensorValue[rightEncoder]) < deg*BASEDEG){
		motor[leftMotor] = 80* leftOrRight;
		motor[rightMotor] = -80* leftOrRight;
	}
}

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

void stopMyMotor(int stopTime){
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	wait1Msec(stopTime);
	}

task main()
{
	wait1Msec(2000);							// Robot waits for 2000 milliseconds before executing program
	resetEncoder();
	for(int i = 0; i < 14; i++){
			drive(BASEDIST,1);
			stopMyMotor(500);
			resetEncoder();
			turn(90, turnArray[i]);
			resetEncoder();
			stopMyMotor(500);
	}
	drive(BASEDIST,1);
}
