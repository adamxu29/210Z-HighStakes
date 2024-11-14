#include "main.h"

// controller
extern pros::Controller controller;

extern pros::Motor_Group left_drive;
extern pros::Motor_Group right_drive;

extern pros::Motor intake;
extern pros::Motor_Group wall_stake;

extern pros::ADIDigitalOut tilter;
extern pros::ADIDigitalOut doinker;
extern pros::ADIDigitalOut intake_lift;
extern pros::ADIDigitalOut rachet;

extern pros::ADIAnalogIn line;

extern pros::IMU imu1;
extern pros::IMU imu2;

extern Eclipse::Utility util;
extern Eclipse::OPControl driver;
extern Eclipse::PID_Tuner tuner;
extern Eclipse::Translation_PID t_pid;
extern Eclipse::Rotation_PID r_pid;
extern Eclipse::Curve_PID c_pid;

extern double maxSpeed;
extern double turn_maxSpeed;
extern double curve_maxSpeed;
// PID functions
extern void drive_pid(double target);
extern void turn_pid(double theta);
extern void curve_pid(double theta, double timeout, double curve_damper, bool backwards);