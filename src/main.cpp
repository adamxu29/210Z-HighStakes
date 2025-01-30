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
	wall_stake_rotation_sensor.set_position(-1350);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	pros::Task wall_stake_control([]{
		while (true) {
			driver.control_wall_stake();
			driver.power_wall_stake();
			pros::delay(8);
		}
	});

	pros::Task color_sorting([]{
		while(util.sorting){
			if(gui.selected_color == 0){
				util.sort_red();
				util.stop_on_red();
			}
			else if(gui.selected_color == 1){
				util.sort_blue();
				util.stop_on_blue();
			}
			
			pros::delay(8);
		}
	});


	color.set_led_pwm(0);
}

void disabled() {
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void competition_initialize() {
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
char buffer[300];
void autonomous(){
	t_pid.set_drive_constants(3.25, 0.75, 600);
	// t_pid constants: kp: 5, kd: 15
	// r_pid constants: kd: 2.5, kd: 15
	
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);
	color.set_led_pwm(50);

	// Run auton selector for
	gui.run_selected_auton();
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
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	bool tuning = false;
	util.sorting = true;
	util.sort_delay = 27;

	driver.skills = false; // make true if running skills

	while(true){
		controller.print(0, 0, "DT: %0.1f", util.get_drive_temp());

		if(tuning){
			tuner.driver_tuner();
		}
		else if(!driver.color_sorting){
			driver.driver_control();
		}
		pros::delay(8);
	}
}