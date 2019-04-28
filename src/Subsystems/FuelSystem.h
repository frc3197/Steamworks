#ifndef FUEL_SYSTEM_H
#define FUEL_SYSTEM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <CANTalon.h>

class FuelSystem: public Subsystem
{
private:
	CANTalon scoopCan;
	CANTalon shooterCan;
	CANTalon augerCan;

	float shootSpeed;
	float augSpeed;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	FuelSystem();
	void InitDefaultCommand();


	void scoopFuel(bool run);
	void augFuel(bool run);
	void shootFuel(bool run);




};

#endif
