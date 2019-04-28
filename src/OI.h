#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	static const int JOYSTICK = 0;
	static const int BUTTON1 = 1;
	static const int BUTTON2 = 2;
	static const int BUTTON3 = 3;
	static const int BUTTON4 = 4;
	static const int BUTTON5 = 5;
	static const int BUTTON6 = 6;
	static const int BUTTON7 = 7;
	static const int BUTTON8 = 8;
	static const int BUTTON9 = 9;
	static const int BUTTON10 = 10;

	Joystick stick;
	Joystick stick2;
	ADXRS450_Gyro gyro;
	Encoder shootEncoder;
	AnalogInput gearUltra;
	AnalogInput shootUltra;


	JoystickButton p1A; //A
	JoystickButton p1B; //B
	JoystickButton p1X; //X
	JoystickButton p1Y; //Y
	JoystickButton p1LB; //LB
	JoystickButton p1RB; //RB
	JoystickButton p1Back; //Back
	JoystickButton p1Start; //Start
	JoystickButton p1LStick; //Left Stick Click
	JoystickButton p1RStick; //Right Stick Click

	JoystickButton p2A; //A
	JoystickButton p2B; //B
	JoystickButton p2X; //X
	JoystickButton p2Y; //Y
	JoystickButton p2LB; //LB
	JoystickButton p2RB; //RB
	JoystickButton p2Back; //Back
	JoystickButton p2Start; //Start
	JoystickButton p2LStick; //Left Stick Click
	JoystickButton p2RStick; //Right Stick Click

	int gyroAdd = 0;

	bool oldGyro;

	bool oldAlignGear;
	bool oldAlignShoot;

	bool oldSuck;
	bool oldShoot;
	bool oldGear;



public:
	OI();
	float getDriveVert();
	float getdriveHoriz();
	float getRotation();
	float getGyro();
	bool gyroToggle();
	bool alignGearToggle();
	bool alignShootToggle();
	bool suckToggle();
	bool shootToggle();
	bool aug();
	bool runClimb();
	bool gearPlace();
	float getGearDist();
	float getShootDist();
	void addToGyro();

};

#endif
