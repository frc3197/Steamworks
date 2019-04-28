#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/cameraControl.h"

Camera::Camera() :
		Subsystem("Camera")
{

}

void Camera::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new cameraControl());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

