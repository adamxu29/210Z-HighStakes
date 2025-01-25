#include "main.h"

using namespace Eclipse;
// use AssetConfig, this should be for backup

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor_Group left_drive({-13, -12, -11});
pros::Motor_Group right_drive({18, 19, 20});

pros::Motor intake(-21);

pros::Motor wall_stake(4);

pros::Rotation horizontal_rotation_sensor(10);
pros::Rotation wall_stake_rotation_sensor(9);

pros::Optical color(16);

pros::ADIDigitalOut clamp('h');
pros::ADIDigitalOut doinker('g');
pros::ADIDigitalOut ring_rush('f');
pros::ADIDigitalOut intake_lift('e');
pros::ADIDigitalOut ratchet('a'); // temp

pros::ADIAnalogIn line('f');

pros::IMU imu1(14);
pros::IMU imu2(17);

// lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_rotation_sensor);

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


lemlib::Drivetrain_t drivetrain {
    &left_drive, // left drivetrain motors
    &right_drive, // right drivetrain motors
    11.5, // track width in inches
    3.25, // wheel diameter
    450 // wheel rpm
};

lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1 (motor)
    nullptr, // vertical tracking wheel 2 (motor)
    nullptr,// &horizontal_tracking_wheel, // horizontal tracking wheel 1 (none)
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &imu2, // inertial sensor
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