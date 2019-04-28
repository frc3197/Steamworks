#ifndef GEAR_H
#define GEAR_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <CANTalon.h>

class Gear: public Subsystem
{
private:
	CANTalon CANFlick;

	bool isRunning = false;

public:
	Gear();
	void InitDefaultCommand();
	bool flickGear(bool run, bool direction);
};

#endif
