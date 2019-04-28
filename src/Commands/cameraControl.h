#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "CameraServer.h"

class cameraControl: public CommandBase
{
private:

public:
	cameraControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
