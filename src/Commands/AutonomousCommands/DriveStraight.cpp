#include <Commands/AutonomousCommands/DriveStraight.h>
#define MAX_TIME 8
#define SPEED_FORWARD .75

DriveStraight::DriveStraight()
{
	Requires(chassis);
}

void DriveStraight::Initialize()
{
	timer.Reset();
	timer.Start();
	chassis->driveBot(0, 0, 0, 0, false);
	state = 0;
	finished = false;
}

void DriveStraight::Execute()
{
	switch(state)
	{
	case 0:
		if(timer.HasPeriodPassed(MAX_TIME))
		{
			chassis->driveBot(0, SPEED_FORWARD, 0, 0, true);
		}
		else
		{
			state++;
		}
	break;

	case 1:

		finished = true;
		timer.Stop();
		chassis->driveBot(0, 0, 0, 0, false);

	break;

	default:
	finished = true;
	break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished()
{
	return finished;
}

// Called once after isFinished returns true
void DriveStraight::End()
{
	chassis->driveBot(0, 0, 0, 0, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted()
{

}
