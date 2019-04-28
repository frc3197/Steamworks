#include "Gear.h"
#include "../RobotMap.h"
#include "../Commands/gearFlickr.h"

#define FLICKSPEED -1
#define MAX_HIGH 1023
#define MIN_HIGH 0

Gear::Gear() :
		Subsystem("Gear"),
		CANFlick(5)
{
	CANFlick.SetFeedbackDevice(CANTalon::AnalogPot);
}

void Gear::InitDefaultCommand()
{
	SetDefaultCommand(new gearFlickr());
	isRunning = false;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Gear::flickGear(bool run, bool outwards)
{
	int counts = CANFlick.GetAnalogIn();

	if(run) //running
	{
		isRunning = true;

		if(outwards) //outwards
		{
			if(counts < MAX_HIGH)//hasnt reached pot limit
			{
				CANFlick.Set(FLICKSPEED);
			}
			else//reached limit
			{
				CANFlick.Set(0);
				isRunning = false;
			}
		}
		else //inwards
		{
			if(counts > MIN_HIGH)//hasnt reached pot limit
			{
				CANFlick.Set(-FLICKSPEED);
			}
			else
			{
				CANFlick.Set(0);//reached limit
				isRunning = false;
			}
		}
	}
	else //not running
	{
		isRunning = false;
		CANFlick.Set(0);
	}

	return isRunning;
}
