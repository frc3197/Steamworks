#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "OI.h"
#include <iostream>

class driveWithJoystick: public CommandBase
{
private:
	float cX = 0;
	float cY = 0;
	float cX2 = 0;
	float cY2 = 0;

	bool useGyro;
	bool aligningGear;
	bool aligningShoot;

public:
	driveWithJoystick();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
