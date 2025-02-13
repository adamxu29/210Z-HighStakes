#include "display/lv_objx/lv_slider.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motors.h"
#include "map"

/*
Odometry coord finder: //https://path.jerryio.com/
*/

using namespace Eclipse;

// Red paths
void Eclipse::Autonomous_Paths::Red::solo_awp()
{
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-48, 127, .7);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(500);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32.9, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(86, 127, .55);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 25, 500);
	chassis.moveTo(0, 20, 450); // move back to align with ring closest to middle in 8-stack

	// turn to ring 2
	// r_pid.set_r_constants(2.5, 0, 17);
	// r_pid.rotation_pid(180, 90, 2); //185
	chassis.setPose(0, 0, 0);
	chassis.turnTo(100, 0, 700);

	// drive to intake ring 2 and drive back
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 16.5, 700);
	pros::delay(250);
	chassis.moveTo(0, 10, 700);

	// turn to ring 3
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(320, 127, 1);

	intake.move_voltage(12000);

	// intake ring 3
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 650); // 42

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(270, 127, 1.5);

	clamp.set_value(false);
	util.sorting = false;

	// stops on red ring
	util.stop_on_color = true;
	intake.move_voltage(9000);

	// intake double ring stack at mid
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 47, 2500, 60);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 127, .75); // 21.5 degrees <- face up

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -26, 1000);

	clamp.set_value(true);
	pros::delay(250);
	
	util.sorting = true;
	util.stop_on_color = false;

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-80, 127, .7);
	intake.move_voltage(12000);

	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 29, 1000);
	intake.move_voltage(12000);
	chassis.moveTo(-5, -6, 1000);
}

void Eclipse::Autonomous_Paths::Red::left_half_awp()
{
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-44, 127, 1.2);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(600);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(86, 127, .55);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 26, 1000, 100);
	chassis.moveTo(0, 22, 1000, 100);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(26, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 15, 500);

	intake_lift.set_value(false);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 16, 500, 75);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 16, 500, 75);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(55, 90, 2);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -60, 5000);
	
}

void Eclipse::Autonomous_Paths::Red::right_half_awp()
{
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(46, 127, .8);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(600);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 127, .7);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 1000, 100);
	chassis.moveTo(0, 22, 1000, 100);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-26, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 14, 1000);

	intake_lift.set_value(false);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 15, 500, 75);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 15, 500, 75);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-55, 90, 2);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -60, 5000);
}

void Eclipse::Autonomous_Paths::Red::goal_side_rush()
{
	chassis.setPose(-1.2, 0, 0);
	chassis.moveTo(0, 22, 850);

	doinker.set_value(true);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -14, 700);

	doinker.set_value(false);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -3, 400);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(125, 90, 0.75); // face back to second goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -18, 800);

	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(12000); // ring 1

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 1);

	clamp.set_value(false);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-100, 90, 1); // face pulled goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -32, 1000, 100);

	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(12000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-180, 90, 1);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 26, 1000, 150);

	pros::delay(1000);
	intake.move_voltage(12000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-211, 90, 0.6);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 1000);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 10, 800);

	intake_lift.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -4, 1000);
	chassis.moveTo(0, 2, 1000);

	pros::delay(250);

	chassis.moveTo(0, -4, 1000);
	chassis.moveTo(0, 2, 1000);

	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -30, 1000);
}

void Eclipse::Autonomous_Paths::Red::ring_side_rush()
{
	ring_rush.set_value(true);

	chassis.setPose(-.6, 0, 0);
	chassis.moveTo(0, 33.5, 1000, 150);
	pros::delay(150);
	chassis.moveTo(0, 24, 700);
	chassis.moveTo(-3, 7, 800);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-5, 90, .6);

	ring_rush.set_value(false);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-130, 90, .7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -21, 700); //-20 <- back into goal

	clamp.set_value(true);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 90, .6);

	// intake 3 rings
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 34, 1900, 55);
	pros::delay(250);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -10, 750);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-152, 90, .7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 700);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 17, 800);

	intake_lift.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -10, 1000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(90, 90, .8);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 42, 1000, 150);

	driver.next_state();
	intake.move_voltage(12000);
	driver.next_state();
	intake.move_voltage(12000);

	pros::delay(1100);
	intake.move_voltage(0);
	driver.next_state();

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(155, 90, .9);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 9, 1000);

	driver.alliance_stake();

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -9, 300);

	driver.next_state();
}

// Blue paths
void Eclipse::Autonomous_Paths::Blue::solo_awp()
{
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(45, 127, .7);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(500);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-86, 127, .55);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 25, 500);
	chassis.moveTo(0, 20, 450); // move back to align with ring closest to middle in 8-stack

	// turn to ring 2
	// r_pid.set_r_constants(2.5, 0, 17);
	// r_pid.rotation_pid(180, 90, 2); //185
	chassis.setPose(0, 0, 0);
	chassis.turnTo(-100, 0, 700);

	// drive to intake ring 2 and drive back
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 16.5, 700);
	pros::delay(250);
	chassis.moveTo(0, 10, 700);

	// turn to ring 3
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-320, 127, 1);

	intake.move_voltage(12000);

	// intake ring 3
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 650); // 42

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-270, 127, 1.5);

	clamp.set_value(false);
	util.sorting = false;

	// stops on red ring
	util.stop_on_color = true;
	intake.move_voltage(9000);

	// intake double ring stack at mid
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 45, 2500, 60);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(8, 127, .75); // 21.5 degrees

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 1000);

	clamp.set_value(true);
	pros::delay(250);
	
	util.sorting = true;
	util.stop_on_color = false;

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(80, 127, .7);
	intake.move_voltage(12000);

	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 29, 1000);
	intake.move_voltage(0);
	chassis.moveTo(5, -6, 1000);
}

void Eclipse::Autonomous_Paths::Blue::left_half_awp()
{
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-44, 127, 1.2);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(600);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(86, 127, .55);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 26, 1000, 100);
	chassis.moveTo(0, 22, 1000, 100);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(26, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 15, 500);

	intake_lift.set_value(false);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 16, 500, 75);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 16, 500, 75);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(55, 90, 2);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -60, 5000);
}

void Eclipse::Autonomous_Paths::Blue::right_half_awp()
{
	wall_stake_rotation_sensor.set_position(382.0);
	// turn so front is facing alliance stake and back is facing goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(46, 127, .8);

	// score alliance stake
	driver.alliance_stake();
	pros::delay(600);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -5, 600);

	driver.next_state();
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(17, 127, .5); //-20

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 500);
	chassis.moveTo(0, -32, 500, 100);

	clamp.set_value(true);
	pros::delay(150);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 127, .7);

	// intake ring 1
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 1000, 100);
	chassis.moveTo(0, 22, 1000, 100);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-26, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 14, 1000);

	intake_lift.set_value(false);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 15, 500, 75);

	chassis.moveTo(0, 13, 500, 75);
	chassis.moveTo(0, 15, 500, 75);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-55, 90, 2);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -60, 5000);
}

void Eclipse::Autonomous_Paths::Blue::goal_side_rush()
{
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 900);

	doinker.set_value(true);
	pros::delay(200);
	goal_rush_release.set_value(true);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(-1, -20, 1000);

	doinker.set_value(false);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-128, 90, 0.75); // face back to second goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -14, 1000, 80);
	chassis.moveTo(0, -19.5, 1000, 50);

	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(12000); // ring 1

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 1);

	clamp.set_value(false);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(105, 90, 1); // face pulled goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -27, 1000, 80);

	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(12000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-180, 90, 1);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 1000, 80);

	pros::delay(1000);
	intake.move_voltage(12000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(215, 90, 0.6);
	
	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 31, 1000);

	intake_lift.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -2, 1000);
	chassis.moveTo(0, 2, 1000);

	pros::delay(250);

	chassis.moveTo(0, -2, 1000);
	chassis.moveTo(0, 2, 1000);

	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -40, 1000);
}

void Eclipse::Autonomous_Paths::Blue::ring_side_rush()
{
	ring_rush.set_value(true);

	chassis.setPose(-.4, 0, 0);
	chassis.moveTo(0, 33, 1000, 150);
	pros::delay(150);
	chassis.moveTo(0, 24, 700, 50);
	chassis.moveTo(2, 7, 800);

// i like meowing
	ring_rush.set_value(false);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(125, 90, .8);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -20, 700);

	clamp.set_value(true);
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(90, 90, .6);

	// intake 3 rings
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 2000, 45);
	pros::delay(250);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -8, 1000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(150, 90, .7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 700);

	intake_lift.set_value(true);
	pros::delay(250);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 18, 1000);

	pros::delay(250);

	intake_lift.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -10, 1000);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 90, .8);

	driver.next_state();
	driver.next_state();

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 40.6, 1000, 150);

	pros::delay(1100);
	intake.move_voltage(0);
	driver.next_state();

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-149, 90, .9);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 11, 1000);

	driver.alliance_stake();

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -10, 300);

	driver.next_state();
}

// Misc paths
void Eclipse::Autonomous_Paths::skills()
{
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	// ALLIANCE STAKE SECTION
	intake.move_voltage(12000);
	pros::delay(500);
	intake.move_voltage(0);

	// move forward from alliance stake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 11, 800);

	// turn to face goal
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 90, 0.8);

	// clamp goal
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -13.5, 600, 80);
	clamp.set_value(true);
	pros::delay(150);
	chassis.moveTo(0, -21.5, 800);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 0.8);

	intake.move_voltage(12000);

	// intake ring 1
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 900, 100);
	chassis.moveTo(3, 21, 800);

	// turn and intake ring 2
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(17, 90, 0.8);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 59, 800);
	chassis.moveTo(23.5, 61.2, 1500, 80); // make sure x is aligned with top ring

	// intake ring 3 for lb
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 1);

	// lb up
	intake.move_voltage(0);
	driver.next_state(); // shorten this delay if the lb moves into pos in time
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 10, 1100, 50);

	// intake ring 4 for lb
	chassis.setPose(0, 0, 0);
	chassis.turnTo(-18, -50, 900, true);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -51, 2500, 100); // move back <- align y with wallstake
	intake.move_voltage(0);

	driver.next_state();

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(90, 90, 0.7); // face wallstake

	chassis.setPose(0, 8, 0);
	chassis.moveTo(0, 12, 800);
	intake.move_voltage(12000);		 // avoid hooking onto tilted goal
	chassis.moveTo(0, 28, 1500, 40); // intake ring			 // intake delay

	pros::delay(300);
	intake.move_voltage(0);

	// 2 quick jorks
	intake.move_voltage(12000);
	pros::delay(80);
	intake.move_voltage(0);
	intake.move_voltage(12000);
	pros::delay(80);
	intake.move_voltage(0);

	driver.next_state(); // score on wallstake
	pros::delay(1100);
	// turn to line of rings and intake
	chassis.moveTo(0, 14.8, 1500, 50);

	driver.next_state(); // move lb down
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(180, 90, 0.7);

	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 46, 1000, 70);
	chassis.moveTo(0, 60, 2000, 25);
	pros::delay(650);

	// intake last ring
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(50, 90, 0.7);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 17, 1000);
	pros::delay(200);

	// unclamp in corner
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-20, 90, 0.7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -12, 1000);
	clamp.set_value(false);
	intake.move_voltage(-12000);
	pros::delay(100);

	chassis.moveTo(0, -3.5, 1000);
	intake.move_voltage(0);
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(90, 90, 0.7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 900, 80); // allign w wall

	// second half //////////////////////////////////////////////////////////////////////////////////////////////

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -90, 1000);
	chassis.moveTo(0, -91.1, 1000, 70);

	clamp.set_value(true);
	pros::delay(100);
	chassis.moveTo(0, -84.8, 900);

	// turn to ring 1
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 0.7);

	intake.move_voltage(12000);

	// intake ring 1
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 23.5, 900, 100);
	pros::delay(300);

	// turn and intake ring 2
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-90, 90, 0.8); // tune this value to align with ring 1

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 800);
	pros::delay(300);

	// intake ring 3 in front of wallstake
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-22.5, 90, 1);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 25, 1000, 100);
	pros::delay(600);
	chassis.moveTo(0, 4.1, 1000);

	r_pid.set_r_constants(2.8, 0, 17);
	r_pid.rotation_pid(-175, 90, 1.6); // buggy

	// intake chain all of the rings in bottom corner
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 38, 1000, 70);
	chassis.moveTo(0, 54, 1000, 25);
	pros::delay(650);

	// intake last ring
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-50, 90, 0.7);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 17, 1000);
	pros::delay(200);

	// unclamp in corner
	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(20, 90, 0.7);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -11.6, 1000);
	clamp.set_value(false);
	intake.move_voltage(-12000);
	pros::delay(150);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(-10, 50, 1000);
	intake.move_voltage(6000);
	chassis.moveTo(-15, 92, 2000, 40); // move out of corner / get ring
	pros::delay(100);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-104.8, 90, 0.9); // face middle mogo

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -59, 1500, 80);

	clamp.set_value(true); // clamp goal
	pros::delay(200);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 16, 800); // tune to align with alliance stake value

	//////////////////////////////////////////split///////////////////////////////////////////

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(129, 90, 0.7); // face next ring
	intake.move_voltage(12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 35.5, 1000);
	pros::delay(300);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(64, 90, 0.7); // face next ring in top corner
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 26.5, 1000); // in front of row

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(0, 90, 0.7); // face next ring in top corner
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 25, 1500, 70); // intake row of 2
	chassis.turnTo(-24, -16, 800);

	clamp.set_value(false); // drop goal and then back up
	intake.move_voltage(-12000);
	pros::delay(150);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -25, 1000, 100); // back into corner

	// move out
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 36, 1000);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 17);
	r_pid.rotation_pid(-67.5, 90, 0.7); // face goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 100, 10000);
}

void Eclipse::Autonomous_Paths::test()
{
	intake_lift.set_value(true);
	pros::delay(250);

	intake.move_voltage(6000);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 10, 900);

	intake_lift.set_value(false);
}