#include <Commands/DoYouEvenClimb.h>

DoYouEvenClimb::DoYouEvenClimb()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(climber);
}

// Called just before this Command runs the first time
void DoYouEvenClimb::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DoYouEvenClimb::Execute()
{
	bool run = oi->runClimb();
	climber->StartClimber(run);
}

// Make this return true when this Command no longer needs to run execute()
bool DoYouEvenClimb::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DoYouEvenClimb::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DoYouEvenClimb::Interrupted()
{

}
