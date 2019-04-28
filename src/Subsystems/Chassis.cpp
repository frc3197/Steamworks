#include "Chassis.h"
#include "../RobotMap.h"
#include "../Commands/drivewithJoystick.h"

#define ANGLEDEAD 1
#define DEADZONE .05
#define PROPORTIONSPEED 50
#define WIDTH 240
#define DEADPIX .08
#define SPEED -.2
#define TURN_SPEED -.3


Chassis::Chassis() :
		Subsystem("Chassis"),
		can1(1), can2(2), can3(3), can4(4),
		robotDrive(can3,can2,can4,can1)

		//robotDrive(can1,can2,can3,can4)
{
	robotDrive.SetSafetyEnabled(false);
}

void Chassis::InitDefaultCommand()
{

	// Set the default command for a subsystem here.
	SetDefaultCommand(new driveWithJoystick());
	robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	table = NetworkTable::GetTable("GRIP/myContoursReport");

}

void Chassis::driveBot(float horiz, float vert, float rotate, float gyroAngle, bool useGyro)
{
	bool turning = false;
	if(rotate > DEADZONE || rotate < -DEADZONE)//if you are turning, turning = true
	{
		turning = true;
	}

	float deltaTheta = gyroAngle-resetAngle;
	if((horiz<DEADZONE && horiz>-DEADZONE) && (vert<DEADZONE && vert>-DEADZONE) && !turning)//if robot isnt moving, the current angle is where it should adjust to
	{
		//not moving or turning
		resetAngle = gyroAngle;
	}
	else if(abs(deltaTheta) > ANGLEDEAD && !turning)//if robot is not aligned and you are not turning, then fix the alignment
	{
		//correcting while driving
		rotate = -deltaTheta / PROPORTIONSPEED;
		SmartDashboard::PutNumber("detaTheta", deltaTheta);
		SmartDashboard::PutNumber("newAngle", rotate);
	}

	SmartDashboard::PutBoolean("field perspective", useGyro);
	if(useGyro)//field perspective
	{
		robotDrive.MecanumDrive_Cartesian(horiz, vert, rotate, gyroAngle);
	}
	else//robot perspective
	{
		robotDrive.MecanumDrive_Cartesian(horiz, vert, rotate, 0);
	}
}

bool Chassis::autoAlignGear()
{
	float horiz = 0;

	std::vector<double> arr = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> arr2 = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	if(arr.size()<=0||arr2.size()<=0)//if size is 0, do nothing
	{
		cX = -5;
		cY = -5;
	}
	else if(arr.size()==1)//if is sees 1 shape, get one value
	{
		cX = arr[0];
		cY = arr2[0];
	}
	else if(arr.size()==2)//if is sees 2 shapes, get two values
	{
		cX = arr[0];
		cY = arr2[0];
		cX2 = arr[1];
		cY2 = arr2[1];
	}


	float deltaPix = 0;
	if(arr.size()==1)//calculate distance to center of screen
	{
		deltaPix = (WIDTH / 2) - cX;
	}
	else if(arr.size()==2)
	{
		deltaPix = (WIDTH / 2) - ((cX+cX2)/2);
	}
	else
	{
		deltaPix = 0;
	}

	if(abs(deltaPix) > (WIDTH * DEADPIX))
	{
		aligning = true;
	}

	if(aligning && (abs(deltaPix) > (WIDTH * DEADPIX))&& (arr.size()==1))//aligning to 1 shape
	{
		if(deltaPix>0)
		{
			horiz = SPEED;
		}
		else
		{
			horiz = -SPEED;
		}

		if(horiz>1)
		{
			horiz = 1;
		}
		if(horiz<-1)
		{
			horiz = -1;
		}
//		SmartDashboard::PutNumber("speed", horiz);
	}
	else if(aligning && (abs(deltaPix) > (WIDTH * DEADPIX))&& (arr.size()==2))//aligning to 2 shapes
	{
		if(deltaPix>0)
		{
			horiz = SPEED;
		}
		else
		{
			horiz = -SPEED;
		}

		if(horiz>1)
		{
			horiz = 1;
		}
		if(horiz<-1)
		{
			horiz = -1;
		}
//		SmartDashboard::PutNumber("speed", horiz);
	}
	else if(aligning) //done aligning because deltapix is dead
	{
		aligning = false;
	}

	if(!aligning)
	{
		robotDrive.MecanumDrive_Cartesian(0, 0, 0, 0);
	}
	else
	{
		robotDrive.MecanumDrive_Cartesian(0, horiz, 0, 0);
	}

	return aligning;
}

bool Chassis::autoAlignShoot()
{
	float horiz = 0;

	std::vector<double> arr = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> arr2 = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	if(arr.size()<=0||arr2.size()<=0)
	{
		//if size is 0 it does nothing
		cX = -5;
		cY = -5;
//		SmartDashboard::PutNumber("CenterX", 0);
//		SmartDashboard::PutNumber("CenterY", 0);
	}
	else if(arr.size()==1)//if is sees 1 shape, get one value
	{
		cX = arr[0];
		cY = arr2[0];
//		SmartDashboard::PutNumber("CenterX", arr[0]);
//		SmartDashboard::PutNumber("CenterY", arr2[0]);
	}
	else if(arr.size()==2)//if is sees 2 shape, get 2 values
	{
		cX = arr[0];
		cY = arr2[0];
		cX2 = arr[1];
		cY2 = arr2[1];
//		SmartDashboard::PutNumber("CenterX", arr[0]);
//		SmartDashboard::PutNumber("CenterY", arr2[0]);
//		SmartDashboard::PutNumber("CenterX 2", arr[1]);
//		SmartDashboard::PutNumber("CenterY 2", arr2[1]);
	}


	float deltaPix = 0;
	if(arr.size()==1)
	{
		deltaPix = (WIDTH / 2) - cX;
	}
	else if(arr.size()==2)
	{
		deltaPix = (WIDTH / 2) - ((cX+cX2)/2);
	}
	else
	{
		deltaPix = 0;
	}

	if(abs(deltaPix) > (WIDTH * DEADPIX))
	{
		aligningShoot = true;
	}

	if(aligningShoot && (abs(deltaPix) > (WIDTH * DEADPIX))&& (arr.size()==1))//align to 1 shape
	{
		if(deltaPix>0)
		{
			horiz = TURN_SPEED;
		}
		else
		{
			horiz = -TURN_SPEED;
		}

		if(horiz>1)
		{
			horiz = 1;
		}
		if(horiz<-1)
		{
			horiz = -1;
		}
//		SmartDashboard::PutNumber("speed", horiz);
	}
	else if(aligningShoot && (abs(deltaPix) > (WIDTH * DEADPIX))&& (arr.size()==2))//align to 2 shapes
	{
		if(deltaPix>0)
		{
			horiz = TURN_SPEED;
		}
		else
		{
			horiz = -TURN_SPEED;
		}

		if(horiz>1)
		{
			horiz = 1;
		}
		if(horiz<-1)
		{
			horiz = -1;
		}
//		SmartDashboard::PutNumber("speed", horiz);
	}
	else if(aligningShoot) //done aligning because deltapix is dead
	{
		aligningShoot = false;
	}

	if(!aligningShoot)
	{
		robotDrive.MecanumDrive_Cartesian(0, 0, 0, 0);
	}
	else
	{
		robotDrive.MecanumDrive_Cartesian(0, 0, horiz, 0);
	}

	return aligningShoot;
}


//#include "Chassis.h"
//#include "../RobotMap.h"
//#include "../Commands/drivewithJoystick.h"
//
//#define ANGLEDEAD 1
//#define DEADZONE .05
//#define PROPORTIONSPEED 50
//#define WIDTH 240
//#define DEADPIX .05
//#define SPEEDPERPIX 200
//
//
//Chassis::Chassis() :
//		Subsystem("Chassis"),
//		can1(1), can2(2), can3(3), can4(4),
//		robotDrive(can3,can2,can4,can1)
//
//		//robotDrive(can1,can2,can3,can4)
//{
//	robotDrive.SetSafetyEnabled(false);
//}
//
//void Chassis::InitDefaultCommand()
//{
//	SetDefaultCommand(new driveWithJoystick());
//
//	//invert right side to run straight
//	robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
//	robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
//
//	//maybe multiple in future for seperate cameras
//	table = NetworkTable::GetTable("GRIP/myContoursReport");
//
//}
//
//void Chassis::driveBot(float horiz, float vert, float rotate, float gyroAngle, bool useGyro, bool autoAlign)
//{
//	//updates contour report
//	contourUpdate();
//
//	if(autoAlign) //do not interfere
//	{
//		robotDrive.MecanumDrive_Cartesian(horiz, 0, 0, gyroAngle);
//	}
//	else
//	{
//		bool turning = false;
//
//		if(abs(rotate) > DEADZONE) //turning
//		{
//			turning = true;
//		}
//
//		float deltaTheta = gyroAngle - resetAngle; //degrees off from angle at start
//
//		if(abs(horiz) < DEADZONE && abs(vert) < DEADZONE && !turning) //initiates angle to adjust to if not turning
//		{
//			resetAngle = gyroAngle;
//		}
//		else if(abs(deltaTheta) > ANGLEDEAD && !turning)
//		{
//			//correcting while driving
//			rotate = -deltaTheta / PROPORTIONSPEED;
//		}
//
//		SmartDashboard::PutBoolean("field perspective", useGyro);
//
//		if(useGyro) //field perspective
//		{
//			robotDrive.MecanumDrive_Cartesian(horiz, vert, rotate, gyroAngle);
//		}
//		else //robot perspective
//		{
//			robotDrive.MecanumDrive_Cartesian(horiz, vert, rotate, 0);
//		}
//	}
//}
//
//void Chassis::contourUpdate()
//{
//	std::vector<double> arrX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
//	std::vector<double> arrY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
//
//	arrSizeX = arrX.size();
//	arrSizeY = arrY.size();
//
//	if(arrSizeX <=0 || arrSizeY <= 0) //default values if no contours found
//	{
//		cX = -5; //?? ask ethan if this is middle or something
//		cY = -5;
//	}
//	else if(arrSizeX == 1)
//	{
//		cX = arrX[0];
//		cY = arrY[0];
//	}
//	else if(arrSizeX == 2)
//	{
//		cX = arrX[0];
//		cY = arrY[0];
//		cX2 = arrX[1];
//		cY2 = arrY[1];
//	}
//
//	if(arrSizeX == 1) //center screen to centerx
//	{
//		deltaPix = (WIDTH / 2) - cX;
//	}
//	else if(arrSizeX == 2) //center screen to avg of centerx's
//	{
//		deltaPix = (WIDTH / 2) - ((cX+cX2)/2);
//	}
//	else
//	{
//		deltaPix = 0;
//	}
//
//
//	if(abs(deltaPix) > (WIDTH * DEADPIX))
//	{
//		canAlign = true;
//	}
//	else
//	{
//		canAlign = false;
//	}
//}
//
//bool Chassis::align(bool strafe)
//{
//
//	if(canAlign)
//	{
//		adjustment = deltaPix / SPEEDPERPIX;
//	}
//
//	if(!canAlign)
//	{
//		robotDrive.MecanumDrive_Cartesian(0, 0, 0, 0);
//	}
//	else if(strafe) //strafing adjustment
//	{
//		robotDrive.MecanumDrive_Cartesian(adjustment, 0, 0, 0);
//	}
//	else if(!strafe) //turning adjustment
//	{
//		robotDrive.MecanumDrive_Cartesian(0, 0, adjustment, 0);
//	}
//
//	return canAlign;
//}
