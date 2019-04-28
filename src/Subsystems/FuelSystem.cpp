#include <Subsystems/FuelSystem.h>
#include "../RobotMap.h"
#include "../Commands/fuelManagementSystem.h"

#define SCOOPSPEED .7
#define AUGSPEED .2
#define SHOOTSPEED .5
#define P_RATE_SHOOT 2580
#define MAX_RPM_SHOOT 5310
#define SHOOT_SPEED .55
#define P_RATE_AUG 10000
#define MAX_RPM_AUG 130
#define AUG_SPEED .28
#define DEADZONE_SHOOT 50
#define DEADZONE_AUG 5


FuelSystem::FuelSystem() :
	Subsystem("FuelSystem"),
	scoopCan(6), shooterCan(7), augerCan(8)
{

}

void FuelSystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new fuelManagementSystem());

	shooterCan.SetFeedbackDevice(CANTalon::QuadEncoder);
	shooterCan.ConfigEncoderCodesPerRev(1024);
	shooterCan.SetSensorDirection(true);

	augerCan.SetFeedbackDevice(CANTalon::QuadEncoder);
	augerCan.ConfigEncoderCodesPerRev(7);
	augerCan.SetSensorDirection(true);

	shootSpeed = 0;
	augSpeed = 0;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void FuelSystem::scoopFuel(bool run)
{
	if(run)
	{
		scoopCan.Set(SCOOPSPEED);
	}
	else
	{
		scoopCan.Set(0);
	}
}

void FuelSystem::augFuel(bool run)
{
	float speed = -augerCan.GetEncVel();

	float idealRPM = MAX_RPM_AUG*AUG_SPEED;//what RPM should be

	float deltaRPM = idealRPM - speed;//difference between what RPM is and what it should be

	if(deltaRPM > DEADZONE_SHOOT)//if difference is greater than deadzone, correct
	{
		augSpeed += (deltaRPM/P_RATE_AUG);
	}
	else if(deltaRPM < -DEADZONE_SHOOT)//if difference is greater than deadzone, correct
	{
		augSpeed += (deltaRPM/P_RATE_AUG);
	}

	if(run)
	{
		augerCan.Set(augSpeed);
	}
	else
	{
		augerCan.Set(0);
	}
}

void FuelSystem::shootFuel(bool run)
{
	float speed = -((shooterCan.GetEncVel()*10*60)/(4096*2));//converted value

	float idealRPM = MAX_RPM_SHOOT*SHOOT_SPEED;//what RPM should be

	float deltaRPM = (idealRPM - speed);//difference between what RPM is and what it should be

	if(deltaRPM > DEADZONE_SHOOT)//if difference is greater than deadzone, correct
	{
		shootSpeed += (deltaRPM/P_RATE_SHOOT);
	}
	else if(deltaRPM < -DEADZONE_SHOOT)//if difference is greater than deadzone, correct
	{
		shootSpeed += (deltaRPM/P_RATE_SHOOT);
	}

	if(run)
	{
		shooterCan.Set(shootSpeed);

	}
	else
	{
		shooterCan.Set(0);
	}
}
//#include <Subsystems/FuelSystem.h>
//#include "../RobotMap.h"
//#include "../Commands/fuelManagementSystem.h"
//
//#define SCOOPSPEED .7
//#define AUGSPEED .2
//#define SHOOTSPEED .5
//
//
//FuelSystem::FuelSystem() :
//	Subsystem("FuelSystem"),
//	scoopCan(6), shooterCan(7), augerCan(8)
//{
//
//}
//
//void FuelSystem::InitDefaultCommand()
//{
//	// Set the default command for a subsystem here.
//	SetDefaultCommand(new fuelManagementSystem());
//
//	shooterCan.SetFeedbackDevice(CANTalon::QuadEncoder);
//	shooterCan.ConfigEncoderCodesPerRev(1024);
//	shooterCan.SetSensorDirection(true);
//
//	augCan.SetFeedbackDevice(CANTalon::QuadEncoder);
//	augCan.ConfigEncoderCodesPerRev(1024);
//	augCan.SetSensorDirection(true);
//
//}
//
//
//void FuelSystem::scoopFuel(bool run)
//{
//	if(run)
//	{
//		scoopCan.Set(SCOOPSPEED);
//	}
//	else
//	{
//		scoopCan.Set(0);
//	}
//}
//
//void FuelSystem::augFuel(bool run)
//{
//	//PI code here
//	if(run)
//	{
//		augerCan.Set(AUGSPEED);
//	}
//	else
//	{
//		augerCan.Set(0);
//	}
//}
//
//void FuelSystem::shootFuel(bool run)
//{
//	//PI code here
//	float speed = shooterCan.GetEncVel()*10;
//
//
//	if(run)
//	{
//		shooterCan.Set(SHOOTSPEED);
//		/*
//		 when shooter gets to desired speed, start auger
//		 */
//	}
//	else
//	{
//		shooterCan.Set(0);
//	}
//}
