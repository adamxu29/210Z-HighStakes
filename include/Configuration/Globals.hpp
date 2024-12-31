#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

// controller
extern pros::Controller controller;

extern pros::Motor_Group left_drive;
extern pros::Motor_Group right_drive;

extern pros::Motor intake;
extern pros::Motor_Group wall_stake;

extern pros::ADIDigitalOut clamp;
extern pros::ADIDigitalOut doinker;
extern pros::ADIDigitalOut intake_lift;
extern pros::ADIDigitalOut ratchet;

extern pros::ADIAnalogIn line;

extern pros::IMU imu1;
extern pros::IMU imu2;

extern Eclipse::Utility util;
extern Eclipse::OPControl driver;
extern Eclipse::PID_Tuner tuner;
extern Eclipse::Translation_PID t_pid;
extern Eclipse::Rotation_PID r_pid;
extern Eclipse::Curve_PID c_pid;
extern Eclipse::Autonomous_Paths auton;
extern Eclipse::Autonomous_Paths::Red red;
extern Eclipse::Autonomous_Paths::Blue blue;
extern Eclipse::GUI gui;

extern bool skills;

extern lemlib::Chassis chassis;