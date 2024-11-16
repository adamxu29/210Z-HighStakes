#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor_Group left_drive({-13, 5, 4});
pros::Motor_Group right_drive({-10, -9, 16});

pros::Motor intake(12);

// pros::Motor left_wall_stake(17);
// pros::Motor right_wall_stake(-6);
pros::Motor_Group wall_stake({-17, 6});


pros::ADIDigitalOut clamp('h');
pros::ADIDigitalOut doinker('g');
pros::ADIDigitalOut intake_lift('e');
pros::ADIDigitalOut rachet('a'); // temp

pros::ADIAnalogIn line('f');

pros::IMU imu1(1);
pros::IMU imu2(2);

Utility util;
OPControl driver;
PID_Tuner tuner;
Translation_PID t_pid;
Rotation_PID r_pid;
Curve_PID c_pid;
Autonomous_Paths auton;