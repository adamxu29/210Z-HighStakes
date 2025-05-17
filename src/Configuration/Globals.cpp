#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor_Group left_drive({19, -18, 20});
pros::Motor_Group right_drive({-12, -11, 13});

pros::Motor intake(14);

pros::Motor_Group wall_stake({10, -1});

pros::Rotation horizontal_rotation_sensor(6);
pros::Rotation wall_stake_rotation_sensor(2);

pros::Optical color(8);

pros::ADIDigitalOut clamp('h');
pros::ADIDigitalOut right_doinker('g');
pros::ADIDigitalOut left_doinker('d');
pros::ADIDigitalOut goal_rush_clamp('e');
pros::ADIDigitalOut climb_release('f');
pros::ADIDigitalOut climb_claw_pto('c');
pros::ADIDigitalOut wall_stake_boost('b');

pros::ADIDigitalIn limit('a');

pros::IMU imu1(15);
pros::IMU imu2(17);

// pros::Distance front_sensor(5);
// pros::Distance left_sensor(6);
// pros::Distance right_sensor(16);
// pros::Distance back_sensor(7);

Utility util;
OPControl driver;
PID_Tuner tuner;

Translation_PID t_pid;
Rotation_PID r_pid;
Curve_PID c_pid;
PID m_pid;
Odom odom;
Drive drive;
// MonteCarloLocalization mcl;

Autonomous_Paths auton;
Autonomous_Paths::Red red;
Autonomous_Paths::Blue blue;

GUI gui;
