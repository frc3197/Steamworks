#ifndef GEAR_MIDDLE_H
#define GEAR_MIDDLE_H

#include "../../CommandBase.h"
#include "WPILib.h"

class GearMiddle: public CommandBase
{
private:
	int state = 0;
	float rawAngle = 0;
	float dist = 0;
	bool trying;

	Timer timer;

public:
	GearMiddle();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
