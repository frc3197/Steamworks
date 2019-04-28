#include "fuelManagementSystem.h"

fuelManagementSystem::fuelManagementSystem()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(fuelSystem);
}

// Called just before this Command runs the first time
void fuelManagementSystem::Initialize()
{
	useScoop = false;
	useShoot = false;
}

// Called repeatedly when this Command is scheduled to run
void fuelManagementSystem::Execute()
{
	bool scoop = oi->suckToggle();
	bool shoot = oi->shootToggle();
	bool auger = oi->aug();


	if(scoop&&useScoop)
	{
		useScoop = false;
	}
	else if(scoop&&!useScoop)
	{
		useScoop = true;
	}

	if(shoot&&useShoot)
	{
		useShoot = false;
	}
	else if(shoot&&!useShoot)
	{
		useShoot = true;
	}


	fuelSystem->scoopFuel(useScoop);
	fuelSystem->shootFuel(useShoot);
	fuelSystem->augFuel(auger);
}

// Make this return true when this Command no longer needs to run execute()
bool fuelManagementSystem::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void fuelManagementSystem::End()
{
	fuelSystem->scoopFuel(false);
	fuelSystem->shootFuel(false);
	fuelSystem->augFuel(false);

	useScoop = false;
	useShoot = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void fuelManagementSystem::Interrupted()
{

}
