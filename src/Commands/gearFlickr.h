#ifndef GEAR_FLICKR_H
#define GEAR_FLICKR_H

#include "../CommandBase.h"
#include "WPILib.h"

class gearFlickr: public CommandBase
{
private:
	bool flick = false;
	bool oldFlick = false;

	bool turningOut = false;
	bool running = false;

	Timer timer; //

public:
	gearFlickr();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
