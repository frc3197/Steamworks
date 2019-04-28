#include <Commands/AutonomousCommands/GearLeft.h>
#include <Commands/AutonomousCommands/GearMiddle.h>
#include <Commands/AutonomousCommands/GearRight.h>
#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/AutonomousCommands/Nothing.h"
#include "Commands/AutonomousCommands/DriveStraight.h"
class Robot: public IterativeRobot
{
public:
	double cX = 0;
	double cY = 0;
	int times = 0;
	std::shared_ptr<NetworkTable> table;

private:
	std::unique_ptr<Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

	void RobotInit()
	{
		CommandBase::init();

		table = NetworkTable::GetTable("GRIP/myContoursReport");
//		SmartDashboard::PutNumber("CenterX",0);
//		SmartDashboard::PutNumber("CenterY",0);
//		SmartDashboard::PutNumber("times",0);

		chooser.AddDefault("Do Nothing", new Nothing());
		chooser.AddObject("Go Straight", new DriveStraight());
		chooser.AddObject("Left position", new GearLeft());
		chooser.AddObject("Middle position", new GearMiddle());
		chooser.AddObject("Right position", new GearRight());
		SmartDashboard::PutData("Auto Modes", &chooser);

	}

	void DisabledInit()
	{
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}


	void AutonomousInit()
	{
		/* std::string autoSelected = SmartDashboard::GetString("Auto Selector", "Default");
		if(autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		} else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		autonomousCommand.reset(chooser.GetSelected());
		if (autonomousCommand.get() != nullptr)
			autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		LiveWindow::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot)
