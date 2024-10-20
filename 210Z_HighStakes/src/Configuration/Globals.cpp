#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
// drivetrain motors
pros::Motor front_left_drive(19, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor front_right_drive(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor mid_left_drive(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor mid_right_drive(13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_left_drive(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_right_drive(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
// drivetrain motor groups
// pros::Motor_Group left_drive({front_left_drive, mid_left_drive, back_left_drive});
// pros::Motor_Group right_drive({front_right_drive, mid_right_drive, back_right_drive});



// intake motors
// pros::Motor intake(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
// intertial sensors
// tilter pistons
// pros::ADIDigitalOut tilter('c');

Utility util;
OPControl driver;
Translation_PID t_pid;
Rotation_PID r_pid;
Curve_PID c_pid;