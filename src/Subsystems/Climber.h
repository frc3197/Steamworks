#ifndef CLIMBER_H
#define CLIMBER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <CANTalon.h>

class Climber: public Subsystem
{
private:
	//CANTalon CANTlimber; //in loving memory of Brennan Z. 1/20/17

public:
	Climber();
	void InitDefaultCommand();
	void StartClimber(bool startClimber);
};

#endif
