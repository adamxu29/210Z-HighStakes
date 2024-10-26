#include "main.h"

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


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	imu1.tare();
	imu2.tare();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(){
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	t_pid.set_drive_constants(2.75, 1.1, 600);

	//only one auto for nnow

	t_pid.set_t_constants(5, 0, 35, 600);
    t_pid.translation_pid(24, 75, 3);

	// r_pid.set_r_constants(7, 0, 45);
	// r_pid.rotation_pid(90, 90, 2);

	// t_pid.set_t_constants(5, 0, 35, 600);
    // t_pid.translation_pid(-13.5, 90, 3);

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
	bool tuning = false;
	while(true){
		if(tuning){
			tuner.driver_tuner();
		}
		else{
			driver.driver_control();
		}
		pros::delay(10);

	}
}
