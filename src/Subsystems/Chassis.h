#ifndef CHASSIS_H
#define CHASSIS_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "OI.h"
//#include <C:\Users\USER\wpilib\user\cpp\include\CANTalon.h>
#include <CANTalon.h>


class Chassis: public Subsystem
{
private:

	float cX = 0;
	float cY = 0;
	float cX2 = 0;
	float cY2 = 0;
	bool aligning = false;
	bool aligningShoot = false;

	std::shared_ptr<NetworkTable> table;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon can1;
	CANTalon can2;
	CANTalon can3;
	CANTalon can4;
	//CANTalon can5;

	RobotDrive robotDrive;

	float resetAngle = 0;

public:
	Chassis();
	void InitDefaultCommand();
	void driveBot(float horiz, float vert, float rotate, float gyroAngle, bool useGyro);
	bool autoAlignGear();
	bool autoAlignShoot();
};

#endif
