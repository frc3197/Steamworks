#ifndef GEAR_LEFT_H
#define GEAR_LEFT_H

#include "../../CommandBase.h"
#include "WPILib.h"

class GearLeft: public CommandBase
{
private:
	int state = 0;
	float rawAngle = 0;
	float dist = 0;
	bool trying;

	Timer timer;

public:
	GearLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
