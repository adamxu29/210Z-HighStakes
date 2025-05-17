#include "main.h"

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
	// initialize_particles();
	
	util.set_drive_constants(3.25, 0.75, 600);
	util.set_tpi();

	odom.set_horizontal_tracker_specs(2.75, -2.89);
	odom.set_vertical_tracker_specs(3.25, -6.56);

	imu1.tare_rotation();
	imu2.tare_rotation();

	wall_stake_rotation_sensor.set_position(600);
	horizontal_rotation_sensor.reset_position();

	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);

	color.set_led_pwm(0);
	color.set_integration_time(10);
	
	util.set_robot_position(0.0, 0.0);

	pros::delay(3000);
	controller.rumble(".");

	pros::Task update_gui([]{
		while(true){
			gui.update_sensors();
			gui.update_temps();
			gui.update_match_checklist();
			pros::delay(8);
		}
	});

	pros::Task update_odom([]{
		while(true){
			// Particle estimate = get_estimate();
			odom.update_position();
			// //predict();
			// run_localization_step();
			// pros::delay(10);

			// char buffer[300];
			// //sprintf(buffer, "Front: %.2f Back: %.2f Left: %.2f Right: %.2f", front_sensor.get(), back_sensor.get(), left_sensor.get(), right_sensor.get());
			// sprintf(buffer, "X: %.2f Y: %.2f Theta: %.2f", estimate.x, estimate.y, imu1.get_heading());
			// lv_label_set_text(gui.position_readings, buffer);

			pros::delay(8);
		}
	});

	pros::Task wall_stake_control([]{
		while (driver.wall_stake_on) {
			driver.power_wall_stake();
			driver.control_wall_stake();

			// if(wall_stake_rotation_sensor.get_position() < -120){
			// 	wall_stake_boost.set_value(false);
			// 	// driver.wall_stake_boost_activated = false;
			// }
			// driver.manual_wall_stake();
			pros::delay(8);
		}
	});

	pros::Task color_sorting([]{
		int stop_delay_counter = 0;
		while(true){
			if(util.sorting){
				if(gui.selected_color == 0){
					util.sort_red();
				}
				else if(gui.selected_color == 1){
					util.sort_blue();
				}
			}
			else{
				stop_delay_counter++;
				if(stop_delay_counter == 25){
					stop_delay_counter = 0;
					util.sorting = true;
				}
			}
			pros::delay(8);
		}
	});

	pros::Task stop([]{
		while(true){
			if(util.stop_on_color){
				if(gui.selected_color == 0){
					util.stop_on_red();
				}
				else if(gui.selected_color == 1){
					util.stop_on_blue();
				}
			}
			
			pros::delay(100);
		}
	});

	pros::Task goal_rush([]{
		while(true){
			if(limit.get_value() && pros::competition::get_status() == 6 && gui.selected_path == 3){
				auton.goal_rush = true;
				goal_rush_clamp.set_value(true);
				left_doinker.set_value(false);
				break;
			}
			pros::delay(8);
		}
	});

}

void disabled() {
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
}

void competition_initialize() {
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
}

char buffer[300];
void autonomous(){
	util.stop_on_color = false;
	// t_pid constants: kp: 5, kd: 15
	// r_pid constants: kd: 2.5, kd: 15

	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);
	color.set_led_pwm(100);

	// Run auton selector for
	// auton.skills();
	driver.skills ? auton.skills() : gui.run_selected_auton();
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
	int start_time = pros::millis();
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	bool tuning = false;
	util.sorting = true;
	util.stop_on_color = false;

	driver.skills = false; // make true if running skills

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
	// pros::lcd::initialize();

    // // Optional: wait a bit for sensors to boot
    // pros::delay(500);

    // initialize_particles();  // Spread out particles randomly

    // while (true) {
    //     run_localization_step();  // Run the MCL update loop
    //     pros::delay(10);  
	// }
}