#ifndef DRIVE_STRAIGHT_H
#define DRIVE_STRAIGHT_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "OI.h"

class DriveStraight: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;


public:
	DriveStraight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
