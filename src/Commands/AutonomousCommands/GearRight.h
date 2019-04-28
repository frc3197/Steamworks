#ifndef GEAR_RIGHT_H
#define GEAR_RIGHT_H

#include "../../CommandBase.h"
#include "WPILib.h"

class GearRight: public CommandBase
{
private:
	int state = 0;
	float rawAngle = 0;
	float dist = 0;
	bool trying;

	Timer timer;

public:
	GearRight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
