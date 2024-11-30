#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep


using namespace Eclipse;

// Eclipse::RobotConfig RobotConfig(
// 	{-6, 5, 4}, // Left motor ports

// 	{-10, -9, 8}, // Right motor ports

// 	{12}, // intake ports

// 	{3}, // wall stake ports

// 	{'a'}, // tilter soleniod ports
	
// 	{'b'}, // doinker soleiond port

// 	{'d'}, // intake lift soleniod port
	
// 	{1, 2} // imu ports
// );

void initialize() {
	imu1.tare_rotation();
	imu2.tare_rotation();
	line.calibrate();
	chassis.calibrate();
	std::cout << "calibrated value: " << line.get_value_calibrated() << std::endl;
	wall_stake.set_zero_position(0);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	//pros::delay(3000);
}

// could potentially be used for auto hang after match ends, test it out
void disabled() {}

void competition_initialize() {}

void autonomous(){
	t_pid.set_drive_constants(2.75, 0.8, 600);
	// t_pid constants: kp: 5, kd: 15
	// r_pid constants: kd: 2.5, kd: 15
	
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	// auton.red_awp_rush(); //1
	// auton.blue_awp_rush(); //2
	// auton.test();
	auton.skills(); //8
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	//wall_stake.set_zero_position(0);
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	bool tuning = false;
	float drivetrain_temperature;

	skills = false; // make true if running skills

	while(true){
		drivetrain_temperature = (left_drive.get_temperatures()[0] + left_drive.get_temperatures()[1] + left_drive.get_temperatures()[2] + right_drive.get_temperatures()[0] + right_drive.get_temperatures()[1] + right_drive.get_temperatures()[2]) / 6.0;
		controller.print(0, 0, "DT: %0.1f", drivetrain_temperature);
		// controller.print(0, 0, "Heading: %0.1f", util.get_heading());
		// controller.print(0, 0, "Line: %04d", line.get_value());
		if(tuning){
			tuner.driver_tuner();
		}
		else{
			wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
			// std::cout << "pos: " << left_drive.get_positions()[0] << std::endl;
			// std::cout << "left pos: " << left_drive.get_positions()[0] << ", " << left_drive.get_positions()[1] << ", " << left_drive.get_positions()[2] << std::endl;
			// std::cout << "right pos: " << right_drive.get_positions()[0] << ", " << right_drive.get_positions()[1] << ", " << right_drive.get_positions()[2] << std::endl;
			driver.driver_control();
		}
		pros::delay(100);
	}
}