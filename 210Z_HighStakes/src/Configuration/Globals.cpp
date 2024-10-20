#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

Utility util;
OPControl driver;
PID_Tuner tuner;
Translation_PID t_pid;
Rotation_PID r_pid;
Curve_PID c_pid;