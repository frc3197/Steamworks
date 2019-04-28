#ifndef FUEL_MANAGEMENTSYSTEM_H
#define FUEL_MANAGEMENT_SYSTEM_H

#include "../CommandBase.h"
#include "WPILib.h"

class fuelManagementSystem: public CommandBase
{
private:

	bool useScoop;
	bool useShoot;


public:
	fuelManagementSystem();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
