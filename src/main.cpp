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
	gui.initialize_styles();
	gui.initialize_objects();

	gui.display_home();

	imu1.tare_rotation();
	imu2.tare_rotation();
	chassis.calibrate();
	wall_stake.set_zero_position(0);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	wall_stake_rotation_sensor.set_position(-1350);

	color.set_led_pwm(50);
}

// could potentially be used for auto hang after match ends, test it out
void disabled() {

}

void competition_initialize() {

}
char buffer[300];
void autonomous(){
	t_pid.set_drive_constants(3.25, 0.75, 600);
	// t_pid constants: kp: 5, kd: 15
	// r_pid constants: kd: 2.5, kd: 15
	
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	// Run auton selector for
	// gui.run_selected_auton();

	m_pid.set_constants(4, 0, 0, 3, 4, 5, 50, 127 * 0.9);
	m_pid.motor_pid(wall_stake, wall_stake_rotation_sensor, 90.0, 100, 1000);
	
	// auton.skills();

	// auton.test();
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
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	bool tuning = false;

	skills = false; // make true if running skills

	while(true){
		controller.print(0, 0, "DT: %0.1f", util.get_drive_temp());

		if(tuning){
			tuner.driver_tuner();
		}
		else{
			driver.driver_control();
		}
		pros::delay(8);
	}
}