#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor_Group left_drive({-13, 5, 4});
pros::Motor_Group right_drive({-10, -9, 16});

pros::Motor intake(12);

pros::Motor_Group wall_stake({17, -6});


pros::ADIDigitalOut clamp('h');
pros::ADIDigitalOut doinker('g');
pros::ADIDigitalOut intake_lift('e');
pros::ADIDigitalOut ratchet('a'); // temp

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
Autonomous_Paths::Red red;
Autonomous_Paths::Blue blue;
GUI gui;

lemlib::Drivetrain_t drivetrain {
    &left_drive, // left drivetrain motors
    &right_drive, // right drivetrain motors
    9.5, // track width in inches
    3.75, // wheel diameter
    480 // wheel rpm
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1 (motor)
    nullptr, // vertical tracking wheel 2 (motor)
    nullptr, // horizontal tracking wheel 1 (none)
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &imu1, // inertial sensor
};

lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

lemlib::ChassisController_t angularController {
    4, // kP <- default: 4
    40, // kD <- default: 40
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    750, // largeErrorTimeout <- 500
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);