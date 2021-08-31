int turnArray[14] = {1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1};
//bool turnArray[14] = {1,0,0,1,1,0,1,1,0,1,1,0,0,1};
//char turnArray[4] = {'L','R','L','R'};
task main()
{
	for(int i = 0; i < 14; i++){
		writeDebugStream("This is a turning indicator = %d \n", turnArray[i]);
	}

	turn(90, turnArray[i]);
}
void turn(int deg, int leftOrRight){
	while(abs(SensorValue[rightEncoder]) < deg*BASEDEG){
		motor[leftMotor] = 80* leftOrRight;
		motor[leftMotor] = -80* leftOrRight;
	}
}
