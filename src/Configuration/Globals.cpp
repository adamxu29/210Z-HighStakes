#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor_Group left_drive({-13, -12, -11});
pros::Motor_Group right_drive({18, 19, 20});

pros::Motor intake(-21);

pros::Motor wall_stake(-4);

pros::Rotation horizontal_rotation_sensor(10);
pros::Rotation wall_stake_rotation_sensor(9);

pros::Optical color(2);

pros::ADIDigitalOut clamp('g');
pros::ADIDigitalOut right_doinker('d');
pros::ADIDigitalOut left_doinker('a');
pros::ADIDigitalOut goal_rush_release('h');
pros::ADIDigitalOut intake_lift('b');

pros::ADIAnalogIn line('f');

pros::IMU imu1(14);
pros::IMU imu2(17);

Utility util;
OPControl driver;
PID_Tuner tuner;

Translation_PID t_pid;
Rotation_PID r_pid;
Curve_PID c_pid;
PID m_pid;
Odom odom;

Autonomous_Paths auton;
Autonomous_Paths::Red red;
Autonomous_Paths::Blue blue;

GUI gui;
