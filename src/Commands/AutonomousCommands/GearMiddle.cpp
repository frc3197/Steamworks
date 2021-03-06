#include <Commands/AutonomousCommands/GearMiddle.h>
#include "OI.h"

#define SPEED .55
#define ROBOT_WIDTH 38
#define DIST_FROM_WALL 25 //change me please
#define DIST_TO_GEAR 15
#define GEAR_PLACE_TIME 1
#define BACK_OFF_TIME .5

GearMiddle::GearMiddle()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(chassis);
	Requires(gear);
}

// Called just before this Command runs the first time
void GearMiddle::Initialize()
{
	state = 0;
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void GearMiddle::Execute()
{
	SmartDashboard::PutNumber("State",state);

	switch(state)
	{
	case 0: //goes forward for MAXSPEED
		rawAngle = oi->getGyro();
		chassis->driveBot(SPEED, 0, 0, rawAngle, true);
		dist = oi->getGearDist();
		if(dist <= DIST_FROM_WALL)
		{
			state++;
			chassis->driveBot(0, 0, 0, rawAngle, false);
			timer.Reset();
			timer.Start();
		}
	break;

	case 1:	//autoalign
		trying = chassis->autoAlignGear();
		if(!trying)
		{
			state++;
			timer.Reset();
			timer.Start();
		}
	break;

	case 2://drive forward
		rawAngle = oi->getGyro();
		chassis->driveBot(SPEED, 0, 0, rawAngle, true);
		dist = oi->getGearDist();
		if(dist <= DIST_TO_GEAR)
		{
			state++;
			chassis->driveBot(0, 0, 0, rawAngle, false);
			timer.Reset();
			timer.Start();
		}

	break;

	case 3://place gear
		if(!timer.HasPeriodPassed(GEAR_PLACE_TIME)) //place gear
		{
			//gear->flickGear(true, true);
		}
		else
		{
			gear->flickGear(false, false);
			state++;
			timer.Reset();
			timer.Start();
		}

	break;

	case 4://back off a tad
		rawAngle = oi->getGyro();
		if(!timer.HasPeriodPassed(BACK_OFF_TIME)) //place gear
		{
			chassis->driveBot(-SPEED, 0, 0, rawAngle, true);
		}
		else
		{
			chassis->driveBot(0, 0, 0, rawAngle, false);
			state++;
			timer.Reset();
			timer.Start();
		}

	break;

	case 5://close gear
		if(!timer.HasPeriodPassed(GEAR_PLACE_TIME)) //place gear
		{
			//gear->flickGear(true, false);
		}
		else
		{
			gear->flickGear(false, false);
			state++;
			timer.Reset();
			timer.Start();
		}
	break;

	default:

	break;
	}
}

// Make this return true when this Command no lonGer needs to run execute()
bool GearMiddle::IsFinished()
{
	if(state==6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Called once after isFinished returns true
void GearMiddle::End()
{
	chassis->driveBot(0, 0, 0, 0, false);
	oi->addToGyro();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearMiddle::Interrupted()
{

}
