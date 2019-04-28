#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
//std::unique_ptr<ExampleSubsystem> CommandBase::examplesubsystem;
std::unique_ptr<OI> CommandBase::oi;
Chassis* CommandBase::chassis = NULL;
Camera* CommandBase::camera = NULL;
FuelSystem* CommandBase::fuelSystem = NULL;
Climber* CommandBase::climber = NULL;
Gear* CommandBase::gear = NULL;

CommandBase::CommandBase(const std::string &name):
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
//	examplesubsystem.reset(new ExampleSubsystem());
	oi.reset(new OI());
	chassis = new Chassis();
	camera = new Camera();
	fuelSystem = new FuelSystem();
	climber = new Climber();
	gear = new Gear();
}
