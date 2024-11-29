#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motors.h"

/*
Odometry coord finder: //https://path.jerryio.com/
*/

using namespace Eclipse;

// INTEGRATE ALLIANCE STAKES ONCE BUILT

void Eclipse::Autonomous_Paths::red_awp_rush(){
	clamp.set_value(true);
	intake_lift.set_value(true); //raise the intake
	chassis.setPose(0,0,0);
	chassis.moveTo(0,-28,800); //push ring, move to 45 degree intersection with intake lift

	chassis.setPose(0,0,0);
	chassis.turnTo(-40,24,750); //face lifted ring

		intake.move_voltage(-12000);
	chassis.setPose(0,0,0);
	chassis.moveTo(0,13,700,50); //move onto lifted ring
	intake_lift.set_value(false); //move this if the ring falls out
	chassis.moveTo(0,25,600);

	chassis.setPose(0,0,0);
	intake.move_voltage(0);
	chassis.turnTo(-21,24,800); //face alliance stake
	// intake.move_voltage(12000);
	// pros::delay(250);

	//ALLIANCE-STAKE RAISE MACRO
	intake.move_voltage(-8000);
	wall_stake.move_voltage(-12000);
	pros::delay(380); //time-based
	wall_stake.move_voltage(0);

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,-13.5,700); //push first ring
	// chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-23.3,700); //move back into alliance stake

	wall_stake.move_voltage(12000); //move down
	pros::delay(800);

	//MOGO 1
	chassis.setPose(0,2.5,0);
	chassis.moveTo(0,12,500); //move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(45.2,67,750,true); //face back to mogo
	clamp.set_value(false);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-45,1000,90); //move back into mogo

	clamp.set_value(true); //clamp down

	intake.move_voltage(-12000); //intake ring (that's already in the intake)
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 2); //turn to ring 1
	// pros::delay(200);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,35,1500,200); //second ring

	chassis.turnTo(37,35,1000,true); //turn to alliance side wall
	chassis.moveTo(37,35,1000); //move to alliance side wall

	clamp.set_value(false); //drop off mogo

	chassis.setPose(0,0,0);
	chassis.moveTo(0,32,1500); //move out
	intake.move_voltage(0);
	
	chassis.turnTo(0,-100,1000); //face back to goal 2

		//TUNE TO NOT CROSS AUTO LINE!
	chassis.setPose(0,0,0);
		chassis.moveTo(0,-25.6,5000,150); //move back onto goal

	clamp.set_value(true);
	wall_stake.move_voltage(-5000);

	chassis.setPose(0,0,0);
	chassis.moveTo(28.628, 30.949, 400); //move back in
	chassis.turnTo(28.628, 30.949,300); //turn to pole middle
	chassis.moveTo(43.071, 6.964, 5000,100); //touch pole
	pros::delay(100);
	wall_stake.move_voltage(0);
}

void Eclipse::Autonomous_Paths::red_awp_left(){
	
}

void Eclipse::Autonomous_Paths::blue_awp_rush(){
	clamp.set_value(true);
	intake_lift.set_value(true); //raise the intake
	chassis.setPose(0,0,0);
	chassis.moveTo(0,-28,800); //push ring, move to 45 degree intersection with intake lift

	chassis.setPose(0,0,0);
	chassis.turnTo(40,24,750); //face lifted ring

		intake.move_voltage(-12000);
	chassis.setPose(0,0,0);
	chassis.moveTo(0,13,700,45); //move onto lifted ring
	intake_lift.set_value(false); //move this if the ring falls out
	chassis.moveTo(0,25,600);

	chassis.setPose(0,0,0);
	pros::delay(50);
	intake.move_voltage(0);
	chassis.turnTo(14.2,24,800); //face alliance stake
	// intake.move_voltage(12000);
	// pros::delay(250);
	//chibber

	//ALLIANCE-STAKE RAISE MACRO
	intake.move_voltage(-8000);
	wall_stake.move_voltage(-12000);
	pros::delay(380); //time-based
	wall_stake.move_voltage(0);

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,-13.5,700); //push first ring
	// chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-26.5,700); //move back into alliance stake

	wall_stake.move_voltage(12000); //move down
	pros::delay(800);

	//MOGO 1
	chassis.setPose(0,2.5,0);
	chassis.moveTo(0,12,500); //move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(-45.2,100,750,true); //face back to mogo
	clamp.set_value(false);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-60.5,1000,90); //move back into mogo

	clamp.set_value(true); //clamp down

	intake.move_voltage(-12000); //intake ring (that's already in the intake)
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 2); //turn to ring 1
	// pros::delay(200);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,30,1500,200); //second ring

	chassis.turnTo(-37,30,1000,true); //turn to alliance side wall
	// chassis.moveTo(-37,35,1000); //move to alliance side wall

	clamp.set_value(false); //drop off mogo
	chassis.turnTo(-37,30,1000); //turn to face second goal

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,32,1500); //move out
	intake.move_voltage(0);
	
	// chassis.turnTo(0,-100,1000); //face back to goal 2

		//TUNE TO NOT CROSS AUTO LINE!
	chassis.setPose(0,0,0);
		chassis.moveTo(0,-21.2,5000,150); //move back onto goal (-25.6)

	clamp.set_value(true);
	wall_stake.move_voltage(-2600);

	chassis.setPose(0,0,0);
	chassis.moveTo(-28.628, 30.949, 400); //move back in
	chassis.turnTo(-28.628, 30.949,300); //turn to pole middle
	chassis.moveTo(-43.071, 6.964, 5000,100); //touch pole
	pros::delay(100);
	wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.move_voltage(0);
}

void Eclipse::Autonomous_Paths::blue_awp_right(){
}

void Eclipse::Autonomous_Paths::elims_rush(){
	intake.move_voltage(-8000);
	clamp.set_value(true);
	wall_stake.move_voltage(-12000);
	pros::delay(430); //time-based
	wall_stake.move_voltage(0);
	
	chassis.setPose(0,0,0);
	chassis.moveTo(0,-13.5,700); //push first ring
	chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);
	
	chassis.setPose(0,0,0);
	chassis.moveTo(0,-5,700); //move back into alliance stake

	wall_stake.move_voltage(12000); //move down
	pros::delay(900);

	chassis.moveTo(0,12,500); //move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(45.2,67,800,true); //face back to mogo
	clamp.set_value(false);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-40,1000,90); //move back into mogo

	clamp.set_value(true); //clamp down

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 2); //turn to ring 1
	intake.move_voltage(-12000);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,32,1500,200);

	chassis.turnTo(45,33.5,800,true); //turn to alliance side wall
	chassis.moveTo(45,33.5,800); //move to alliance side wall

	clamp.set_value(false); //drop off mogo

	chassis.setPose(0,0,0);
	chassis.moveTo(0,24,2000,100); //move out
	intake.move_voltage(0);
	
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(90, 90, 2);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-39.6,5000,70); //move back onto goal

	clamp.set_value(true);
}

void Eclipse::Autonomous_Paths::skills(){
  //ALLIANCE STAKE SECTION
	intake.move_voltage(-8000);
	clamp.set_value(true);
	wall_stake.move_voltage(-12000);
	pros::delay(430); //time-based
	wall_stake.move_voltage(0);
	intake.move_voltage(0);
	
	chassis.setPose(0,0,0);
	chassis.moveTo(0,-5,700); //move back into alliance stake

	wall_stake.move_voltage(12000); //move down
	pros::delay(800);


  //FIRST MOGO SECTION
	chassis.setPose(0,0,0);
	chassis.moveTo(0,18.5,900); //move forward to align with goal flat side
	clamp.set_value(false); //open clamp
	chassis.turnTo(100,18.5,800,true); //turn to face flat side of goal

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-33,1000,120); //clamp goal
	clamp.set_value(true); //clamp
	chassis.turnTo(100,-33,800); //turn to first ring

	intake.move_voltage(-12000); //intake
	chassis.setPose(0,0,0);
	chassis.moveTo(0,32,900,120); //intake first ring
	chassis.turnTo(100,32,800); //slow turn to second ring
		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,33,900,120); //intake second ring
	pros::delay(500);
	chassis.turnTo(100,35,800); //slow turn to third ring
		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,30,900,120); //intake third ring !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pros::delay(1000);
		//intake.move_voltage(12000); pros::delay(100); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0,46,1000,120); //intake fourth ring
	pros::delay(1500);
	chassis.moveTo(0,20,800); //move to fifth ring intersection
	chassis.turnTo(-100,80,800); //turn to fifth ring

	chassis.setPose(0,0,0);
	chassis.moveTo(0,21.5,1000,120); //intake fifth ring
	pros::delay(1000);
	chassis.moveTo(0,0,0); //move back to intersection of corner
		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(-25, 90, 2); //turn to face mid (back faces corner 1)
	intake.move_voltage(0); //stop intake

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-32,1000); //move back into corner 1
	clamp.set_value(false); //deposit goal in corner 1
   /////////////
		chassis.moveTo(0,-24,0); //move back to intersection with goal 2 (this y-value changes the alignment with the second mogo)

	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(90, 90, 2); //turn back to face goal 2 @ intersection


  //SECOND MOGO SECTION
	chassis.setPose(0,0,0);
	chassis.moveTo(0,45,900,50); //POSITION RESET WALL ALIGN

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-100,5000);
	chassis.moveTo(0,-120,5000,100); //move back to goal 2
	clamp.set_value(true); //clamp goal 2
	chassis.moveTo(0,-115,5000,100); //move to ring alignment

	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(0, 90, 2); //turn to face mid (back faces corner 1)

	intake.move_voltage(-12000); //intake
	chassis.setPose(0,0,0);
	chassis.moveTo(0,32,900,120); //intake first ring

	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(-90, 90, 2); //turn to face second ring (absolute)

		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0,0,0);
	chassis.moveTo(0,33,900,120); //intake second ring
	pros::delay(500);
		intake.move_voltage(12000); pros::delay(100); intake.move_voltage(-12000);
	
	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(-180, 90, 2); //turn to face second ring (absolute)

	chassis.setPose(0,0,0);
	chassis.moveTo(0,27,900,120); //intake third ring
	pros::delay(1000);
		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0,45,1000,120); //intake fourth ring
	pros::delay(1500);
	chassis.moveTo(0,20,800); //move to fifth ring intersection
	chassis.turnTo(100,80,800); //turn to fifth ring

	chassis.setPose(0,0,0);
	chassis.moveTo(0,21.5,1000,120); //intake fifth ring
	pros::delay(1000);
	chassis.moveTo(0,0,0); //move back to intersection of corner
		//intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); //inertial and position reset
	r_pid.rotation_pid(25, 90, 2); //turn to face mid (back faces corner 1)
	intake.move_voltage(0); //stop intake

	chassis.setPose(0,0,0);
	chassis.moveTo(0,-34,1000); //move back into corner 1
	clamp.set_value(false); //deposit goal in corner 1

	//optional for now
	chassis.moveTo(0,-18,0); //move out of corner'

  //WALLSTAKE SECTION
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(16, 90, 2); //turn to face wall_stake ring intersection

	wall_stake.move_absolute(-525,200);
	//pros::delay(500); //wait for wallstake to move into prime pos
	chassis.setPose(0,0,0);
	intake.move_voltage(-12000);
	chassis.moveTo(0,72,2000);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-90.2, 90, 2); //turn to face wall_stake ring

	chassis.setPose(0,0,0);
	chassis.moveTo(0,22.5,1000); //intake ring
	pros::delay(2500); //wallstake intake delay (prime position) *NOTE: decrease if ready before-hand

	intake.move_voltage(-5000); //intake to keep ring in
	wall_stake.move_absolute(-3000,200); //score wallstake

	chassis.setPose(0,0,0);
	chassis.moveTo(0,4,1000); //move out of wallstake
	pros::delay(1500);
	chassis.moveTo(0,-20,1000);
}

void Eclipse::Autonomous_Paths::red_left(){
    // clamp goal and score ring
    r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(15, 90, 2);

	t_pid.set_t_constants(5, 0, 15, 600);
	t_pid.translation_pid(-40, 50, 2);

	clamp.set_value(true);
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

	clamp.set_value(true);
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

	clamp.set_value(false);

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

	clamp.set_value(true);
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

	clamp.set_value(false);

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

	clamp.set_value(true);
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

//7
void Eclipse::Autonomous_Paths::test(){
}