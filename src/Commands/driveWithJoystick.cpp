#include "driveWithJoystick.h"

#define PRESSURE_LIMIT 75
#define TIME .25
#define WIDTH 240
#define DEADPIX .05
#define SPEEDPERPIX 200
#define SPEED .25

driveWithJoystick::driveWithJoystick()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(chassis);
}

// Called just before this Command runs the first time
void driveWithJoystick::Initialize()
{
	aligningGear = false;
	aligningShoot = false;
	useGyro = true;
}

// Called repeatedly when this Command is scheduled to run
void driveWithJoystick::Execute()
{
	float horiz = oi->getdriveHoriz();
	float vert = oi->getDriveVert();
	float rotation = oi->getRotation();
	float gyro= oi->getGyro();
	bool toggle = oi->gyroToggle();
	bool autoAlignGear = oi->alignGearToggle();
	bool autoAlignShoot = oi->alignShootToggle();

	if(useGyro && toggle)//if field pers and press, robot pers
	{
		useGyro = false;
	}
	else if(!useGyro&&toggle)//if robot pers and press, field pers
	{
		useGyro = true;
	}

	if(aligningGear && autoAlignGear)//if aligning gear and press, stop aligning
	{
		aligningGear = false;
		chassis->driveBot(0, 0, 0, 0, false);
	}
	else if(!aligningGear && autoAlignGear)//if not aligning and press, start aligning gear
	{
		aligningGear = chassis->autoAlignGear();
	}
	else if(aligningGear)//if still aligning gear, continue
	{
		aligningGear = chassis->autoAlignGear();
	}
	else if(aligningShoot && autoAlignShoot)//if aligning shoot and press, stop aligning
	{
		aligningShoot = false;
		chassis->driveBot(0, 0, 0, 0, false);
	}
	else if(!aligningShoot && autoAlignShoot)//if not aligning and press, start aligning shoot
	{
		aligningShoot = chassis->autoAlignShoot();
	}
	else if(aligningShoot)//if still aligning shoot, continue
	{
		aligningShoot = chassis->autoAlignShoot();
	}
	else//if not aligning, drive normally
	{
		chassis->driveBot(horiz, vert, rotation, gyro, useGyro);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool driveWithJoystick::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void driveWithJoystick::End()
{
	chassis->driveBot(0,0,0,0,false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void driveWithJoystick::Interrupted()
{

}
