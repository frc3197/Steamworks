#include "cameraControl.h"

cameraControl::cameraControl()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void cameraControl::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void cameraControl::Execute()
{
	//SmartDashboard::PutImage("Camera",image);
}

// Make this return true when this Command no longer needs to run execute()
bool cameraControl::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void cameraControl::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cameraControl::Interrupted()
{

}
