#include "Climber.h"
#include "../RobotMap.h"
#include "../Commands/DoYouEvenClimb.h"

#define CLIMB_SPEED .3

Climber::Climber() :
		Subsystem("Climber")
		//CANTlimber(9)
{

}

void Climber::InitDefaultCommand()
{
	// Set the default command DoYouEvenClimbfor a subsystem here.
	SetDefaultCommand(new DoYouEvenClimb());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Climber::StartClimber(bool startClimber)
{
//	if(startClimber)
//	{
//		CANTlimber.Set(CLIMB_SPEED);
//	}
//	else
//	{
//		CANTlimber.Set(0);
//
//	}
}
