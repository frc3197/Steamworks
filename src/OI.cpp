#include "OI.h"
#include "SPI.h"

#define STICKDEAD 0.115
#define VOLTAGEMULT 40.2969076 //  (.977mv per mm) converted to inches

OI::OI():
	stick(0),
	stick2(1),
	gyro(SPI::kOnboardCS0),
	shootEncoder(0, 1, false, Encoder::k1X),
	gearUltra(2),
	shootUltra(3),

	p1A(&stick, BUTTON1),//A
	p1B(&stick, BUTTON2),//B
	p1X(&stick, BUTTON3),//X
	p1Y(&stick, BUTTON4),//Y
	p1LB(&stick, BUTTON5),//LB
	p1RB(&stick, BUTTON6),//RB
	p1Back(&stick, BUTTON7),//Back
	p1Start(&stick, BUTTON8),//Start
	p1LStick(&stick, BUTTON9),//Left Stick
	p1RStick(&stick, BUTTON10),//Right Stick

	p2A(&stick2, BUTTON1),//A
	p2B(&stick2, BUTTON2),//B
	p2X(&stick2, BUTTON3),//X
	p2Y(&stick2, BUTTON4),//Y
	p2LB(&stick2, BUTTON5),//LB
	p2RB(&stick2, BUTTON6),//RB
	p2Back(&stick2, BUTTON7),//Shoot
	p2Start(&stick2, BUTTON8),//Start
	p2LStick(&stick2, BUTTON9),//Left Stick
	p2RStick(&stick2, BUTTON10)//Right Stick

{
	gyro.Calibrate();
	gyro.Reset();

	oldGyro = false;
	oldAlignGear = false;
	oldAlignShoot = false;
	oldSuck = false;
	oldShoot = false;
	oldGear = false;
}


float OI::getDriveVert()//returns vertical speed
{
	float raw = stick.GetRawAxis(5);

	if(raw > STICKDEAD || raw < -STICKDEAD)
	{
		return raw;
	}
	else
	{
		return 0;
	}
}

float OI::getdriveHoriz() //returns horizontal speed
{
	float raw = stick.GetRawAxis(4);

	if(raw > STICKDEAD || raw < -STICKDEAD)
	{
		return raw;
	}
	else
	{
		return 0;
	}
}

float OI::getRotation() //returns turn value
{
	float raw = stick.GetRawAxis(0);

	if(raw > STICKDEAD || raw < -STICKDEAD)
	{
		return raw;
	}
	else
	{
		return 0;
	}
}

float OI::getGyro()
{
	float raw = gyro.GetAngle() + gyroAdd;
	return raw;
}

bool OI::gyroToggle()
{
	bool raw = p1A.Get();
	bool ret = false;
	if(!oldGyro && raw){
		ret = true;
	}
	oldGyro = raw;
	return ret;
}

bool OI::alignGearToggle()
{
	bool raw = p1RB.Get();
	bool ret = false;
	if(!oldAlignGear && raw){
		ret = true;
	}
	oldAlignGear = raw;
	return ret;
}

bool OI::alignShootToggle()
{
	bool raw = p1LB.Get();
	bool ret = false;
	if(!oldAlignShoot && raw){
		ret = true;
	}
	oldAlignShoot = raw;
	return ret;
}

bool OI::suckToggle()
{
	bool raw = p2LB.Get();
	bool ret = false;
	if(!oldSuck && raw){
		ret = true;
	}
	oldSuck = raw;
	return ret;
}

bool OI::aug()
{
	bool raw = p2Y.Get();
	return raw;
}

bool OI::shootToggle()
{
	bool raw = p2RB.Get();
	bool ret = false;
	if(!oldShoot && raw){
		ret = true;
	}
	oldShoot = raw;
	return ret;
}


bool OI::runClimb()
{
	bool raw = p1Start.Get();
	return raw;
}

bool OI::gearPlace()
{
	bool raw = p2A.Get();
	bool ret = false;
	if(!oldGear && raw)
	{
		ret = true;
	}
	return ret;
}

void OI::addToGyro()
{
	gyroAdd += 90;
}

float OI::getGearDist()
{
	float raw = (float)gearUltra.GetAverageVoltage()*VOLTAGEMULT;
	SmartDashboard::PutNumber("gearDist", raw);
	return raw;
}

float OI::getShootDist()
{
	float raw = (float)shootUltra.GetAverageVoltage()*VOLTAGEMULT;
	SmartDashboard::PutNumber("shootDist", raw);
	return raw;
}
