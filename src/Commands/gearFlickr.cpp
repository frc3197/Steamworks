#include "gearFlickr.h"

gearFlickr::gearFlickr()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(gear);
}

// Called just before this Command runs the first time
void gearFlickr::Initialize()
{
	timer.Reset();
	turningOut = false;
}

// Called repeatedly when this Command is scheduled to run
void gearFlickr::Execute()
{
	flick = oi->gearPlace();
	if(flick&&running)//if running and press, stop
	{
		running = false;
		timer.Stop();
		timer.Reset();
	}
	else if(flick&&!running)//if not running and press, start
	{
		running = true;
		timer.Reset();
		timer.Start();
		if(!turningOut)
		{
			turningOut = true;
		}
		else
		{
			turningOut = false;
		}
	}
	//oldFlick = flick;

	running = gear->flickGear(running, turningOut);

//	if(turningOut && running) //
//	{
//		if(timer.HasPeriodPassed(TURNTIMEOUT))
//		{
//			gear->flickGear(false, false);
//			running = false;
//		}
//		else
//		{
//			gear->flickGear(true, true); //turn out
//		}
//	}
//	else if(!turningOut && running) //
//	{
//		if(timer.HasPeriodPassed(TURNTIMEIN))
//		{
//			gear->flickGear(false, false);
//			running = false;
//		}
//		else
//		{
//			gear->flickGear(true, false); //turn in
//		}
//	}
//	else
//	{
//		gear->flickGear(false, false);
//	}

}

// Make this return true when this Command no longer needs to run execute()
bool gearFlickr::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void gearFlickr::End()
{
	gear->flickGear(false, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void gearFlickr::Interrupted()
{

}
