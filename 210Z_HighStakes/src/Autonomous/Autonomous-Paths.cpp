#include "main.h"

using namespace Eclipse;

// ITEGRATE ALLIANCE STAKES ONCE BUILT

void Eclipse::Autonomous_Paths::solo_awp(){

}

void Eclipse::Autonomous_Paths::red_left(){
    // clamp goal and score ring
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(15, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-40, 50, 2);

	tilter.set_value(true);
	intake.move_voltage(-12000);

    // intake and score second ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(67, 90, 2);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(19, 50, 2);

	pros::delay(600);

    // drive to autonomous line, intake and score third ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(180, 50, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(11, 50, 2);

	pros::delay(1500);

    // turn and score last ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(103, 50, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(10, 50, 2);

    // touch elevation ladder
}

void Eclipse::Autonomous_Paths::red_right(){
    // clamp goal and score ring
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(15, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-40, 50, 2);

	tilter.set_value(true);
	pros::delay(250);
	intake.move_voltage(-12000);

    // intake and score second ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(67, 90, 2);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(21, 50, 2);

	pros::delay(100);

    // place goal in corner
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(180, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-35, 75, 2);

	tilter.set_value(false);

    // grab fifth goal
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(175, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(45, 75, 2);

	doinker.set_value(true);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-35, 75, 2);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(30, 90, 2);

	doinker.set_value(false);

    // touch elevation ladder
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(140, 90, 2);

    t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(52, 75, 2);
}

void Eclipse::Autonomous_Paths::blue_left(){
    // clamp goal and score ring
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(15, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-40, 50, 2);

	tilter.set_value(true);
	pros::delay(250);
	intake.move_voltage(-12000);

    // intake and score second ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(67, 90, 2);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(21, 50, 2);

	pros::delay(100);

    // place goal in corner
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(180, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-35, 75, 2);

	tilter.set_value(false);

    // grab fifth goal
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(170, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(45, 75, 2);

	doinker.set_value(true);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-35, 75, 2);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-30, 90, 2);

	doinker.set_value(false);

	// touch elevation ladder
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(140, 90, 2);

    t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(52, 75, 2);
}

void Eclipse::Autonomous_Paths::blue_right(){
    // clamp goal and score ring
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-15, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-40, 50, 2);

	tilter.set_value(true);
	intake.move_voltage(-12000);

    // intake and score second ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-67, 90, 2);
	
	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(19, 50, 2);

	pros::delay(600);

    // drive to autonomous line, intake and score third ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-180, 50, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(11, 50, 2);

	pros::delay(1500);

    // turn and score last ring
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-103, 50, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(10, 50, 2);
}

void Eclipse::Autonomous_Paths::skills(){

}