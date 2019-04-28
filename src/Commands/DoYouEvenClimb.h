#ifndef DO_YOU_EVEN_CLIMB_H
#define DO_YOU_EVEN_CLIMB_H

#include "../CommandBase.h"
#include "WPILib.h"

class DoYouEvenClimb: public CommandBase
{
public:
	DoYouEvenClimb();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
