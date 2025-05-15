#include "main.h"

// controller
extern pros::Controller controller;

extern pros::Motor_Group left_drive;
extern pros::Motor_Group right_drive;

extern pros::Motor intake;
extern pros::Motor_Group wall_stake;

extern pros::Rotation horizontal_rotation_sensor;
extern pros::Rotation wall_stake_rotation_sensor;

extern pros::Optical color;

extern pros::ADIDigitalOut clamp;
extern pros::ADIDigitalOut right_doinker;
extern pros::ADIDigitalOut left_doinker;
extern pros::ADIDigitalOut goal_rush_clamp;
extern pros::ADIDigitalOut climb_release;
extern pros::ADIDigitalOut climb_claw_pto;
extern pros::ADIDigitalOut wall_stake_boost;

extern pros::ADIDigitalIn limit;

extern pros::ADIAnalogIn line;

extern pros::IMU imu1;
extern pros::IMU imu2;

extern pros::Distance front_sensor;
extern pros::Distance left_sensor;
extern pros::Distance right_sensor;
extern pros::Distance back_sensor;

extern Eclipse::Utility util;
extern Eclipse::OPControl driver;
extern Eclipse::PID_Tuner tuner;

extern Eclipse::Translation_PID t_pid;
extern Eclipse::Rotation_PID r_pid;
extern Eclipse::Curve_PID c_pid;
extern Eclipse::PID m_pid;
extern Eclipse::Odom odom;
extern Eclipse::Drive drive;
// extern Eclipse::MonteCarloLocalization mcl;

extern Eclipse::Autonomous_Paths auton;
extern Eclipse::Autonomous_Paths::Red red;
extern Eclipse::Autonomous_Paths::Blue blue;

extern Eclipse::GUI gui;

extern bool skills;
