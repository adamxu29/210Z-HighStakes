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
void Eclipse::Autonomous_Paths::Red::solo_awp(){

}

void Eclipse::Autonomous_Paths::Red::left_half_awp(){
	clamp.set_value(true);
	intake_lift.set_value(true); // raise the intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 800); // push ring, move to 45 degree intersection with intake lift

	chassis.setPose(0, 0, 0);
	chassis.turnTo(-40, 24, 750); // face lifted ring

	intake.move_voltage(-12000);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 12.4, 700, 50); // move onto lifted ring
	intake_lift.set_value(false);	  // move this if the ring falls out
	chassis.moveTo(0, 25, 600);

	chassis.setPose(0, 0, 0);
	intake.move_voltage(0);
	chassis.turnTo(-21, 24, 800); // face alliance stake
	// intake.move_voltage(12000);
	// pros::delay(250);

	// ALLIANCE-STAKE RAISE MACRO
	intake.move_voltage(-8000);
	wall_stake.move_voltage(-12000);
	pros::delay(330); // time-based
	wall_stake.move_voltage(0);

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,-13.5,700); //push first ring
	// chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -26.5, 700); // move back into alliance stake

	wall_stake.move_voltage(12000); // move down
	pros::delay(800);

	// MOGO 1
	chassis.setPose(0, 2.5, 0);
	chassis.moveTo(0, 12, 500); // move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(45.2, 67, 750, true); // face back to mogo
	clamp.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -50, 1000, 80);
	pros::delay(250);

	clamp.set_value(true); // clamp down

	intake.move_voltage(-12000); // intake ring (that's already in the intake)
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 2); // turn to ring 1
	pros::delay(200);
	intake.move_voltage(8000); // intake ring (that's already in the intake)
	pros::delay(100);
	intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 34, 1500, 200); // second ring

	chassis.turnTo(37, 33.5, 1000, true); // turn to alliance side wall

	clamp.set_value(false); // drop off mogo

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(90, 90, 2); // turn to face second goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -19, 5000, 100); // move back onto goal (-21.2)

	clamp.set_value(true);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.move_voltage(-4000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(30, 33.949, 400);	 // move back in
	chassis.turnTo(30, 33.949, 300);	 // turn to pole middle
	chassis.moveTo(37.5, 10, 5000, 100); // touch pole
	pros::delay(100);
	wall_stake.move_voltage(0);
}

void Eclipse::Autonomous_Paths::Red::right_half_awp(){
	
}

void Eclipse::Autonomous_Paths::Red::goal_side_rush(){
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(21.5, 90, .55);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 55, 1000, 200);

	doinker.set_value(true);

	chassis.moveTo(0, 30, 1500, 200);

	doinker.set_value(false);
	pros::delay(600);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(125, 90, 0.75);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -14, 1000, 80);
	chassis.moveTo(0, -19.5, 1000, 50);
	pros::delay(500);

	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(-12000);

		r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 1);
	pros::delay(1000);
	clamp.set_value(false);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-110, 90, 1);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -32, 1000, 80);
	chassis.moveTo(0, -35, 1000, 50);

	clamp.set_value(true);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-200, 90, 1);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 20, 1000, 80);

	pros::delay(2000);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-185, 90, 0.6);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 35, 1000, 200);

	doinker.set_value(true);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-225, 90, 0.6);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 12, 1000, 200);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(0, 90, 2);

	doinker.set_value(true);
}

void Eclipse::Autonomous_Paths::Red::ring_side_rush(){

}

// Blue paths
void Eclipse::Autonomous_Paths::Blue::solo_awp(){

}

void Eclipse::Autonomous_Paths::Blue::left_half_awp(){
	clamp.set_value(true);
	intake_lift.set_value(true); // raise the intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 800); // push ring, move to 45 degree intersection with intake lift

	chassis.setPose(0, 0, 0);
	chassis.turnTo(40, 24, 750); // face lifted ring

	intake.move_voltage(-12000);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 11.5, 700, 40); // move onto lifted ring
	intake_lift.set_value(false);	  // move this if the ring falls out
	chassis.moveTo(0, 25, 600);

	chassis.setPose(0, 0, 0);
	pros::delay(50);
	intake.move_voltage(0);
	chassis.turnTo(14.2, 24, 800); // face alliance stake
	// intake.move_voltage(12000);
	// pros::delay(250);
	// chibber

	// ALLIANCE-STAKE RAISE MACRO
	intake.move_voltage(-8000);
	wall_stake.move_voltage(-12000);
	pros::delay(330); // time-based
	wall_stake.move_voltage(0);

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,-13.5,700); //push first ring
	// chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -26.5, 700); // move back into alliance stake

	wall_stake.move_voltage(12000); // move down
	pros::delay(300);

	// MOGO 1
	chassis.setPose(0, 2.5, 0);
	chassis.moveTo(0, 12, 500); // move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(-45.2, 100, 750, true); // face back to mogo
	clamp.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -57, 1000, 90); // move back into mogo
	clamp.set_value(true);			  // clamp down
	chassis.moveTo(0, -50, 1000, 100);

	intake.move_voltage(-12000); // intake ring (that's already in the intake)
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-5, 90, 2); // turn to ring 1
	pros::delay(200);
	intake.move_voltage(8000); // intake ring (that's already in the intake)
	pros::delay(100);
	intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 1500, 200); // second ring

	chassis.turnTo(-37, 30, 1000, true); // turn to alliance side wall
	// chassis.moveTo(-37,35,1000); //move to alliance side wall

	clamp.set_value(false); // drop off mogo
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-90, 90, 2); // turn to face second goal

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,32,1500); //move out
	// intake.move_voltage(0);

	// chassis.turnTo(0,-100,1000); //face back to goal 2

	// TUNE TO NOT CROSS AUTO LINE!
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -22.0, 5000, 100); // move back onto goal (-21.2)

	clamp.set_value(true);
	wall_stake.move_voltage(-4000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(-28.628, 30.949, 400);	   // move back in
	chassis.turnTo(-28.628, 30.949, 300);	   // turn to pole middle
	chassis.moveTo(-43.071, 6.964, 5000, 100); // touch pole
	pros::delay(100);
	wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	wall_stake.move_voltage(0);
}

void Eclipse::Autonomous_Paths::Blue::right_half_awp(){

}

void Eclipse::Autonomous_Paths::Blue::goal_side_rush(){
	clamp.set_value(true);
	intake_lift.set_value(true); // raise the intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -28, 800); // push ring, move to 45 degree intersection with intake lift

	chassis.setPose(0, 0, 0);
	chassis.turnTo(40, 24, 750); // face lifted ring

	intake.move_voltage(-12000);
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 11.5, 700, 40); // move onto lifted ring
	intake_lift.set_value(false);	  // move this if the ring falls out
	chassis.moveTo(0, 25, 600);

	chassis.setPose(0, 0, 0);
	pros::delay(50);
	intake.move_voltage(0);
	chassis.turnTo(14.2, 24, 800); // face alliance stake
	// intake.move_voltage(12000);
	// pros::delay(250);
	// chibber

	// ALLIANCE-STAKE RAISE MACRO
	intake.move_voltage(-8000);
	wall_stake.move_voltage(-12000);
	pros::delay(330); // time-based
	wall_stake.move_voltage(0);

	// chassis.setPose(0,0,0);
	// chassis.moveTo(0,-13.5,700); //push first ring
	// chassis.turnTo(-100,-13.5,800); //turn to alliance stake
	intake.move_voltage(0);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -26.5, 700); // move back into alliance stake

	wall_stake.move_voltage(12000); // move down
	pros::delay(300);

	// MOGO 1
	chassis.setPose(0, 2.5, 0);
	chassis.moveTo(0, 12, 500); // move out a bit (important to determine y-value of mogo fixed)
	wall_stake.move_voltage(0);
	chassis.turnTo(-45.2, 100, 750, true); // face back to mogo
	clamp.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -55, 1000, 90); // move back into mogo
	clamp.set_value(true);			  // clamp down
	chassis.moveTo(0, -50, 1000, 100);

	intake.move_voltage(-12000); // intake ring (that's already in the intake)
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-5, 90, 2); // turn to ring 1
	// pros::delay(200);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 1500, 200); // second ring

	chassis.turnTo(-37, 30, 1000, true); // turn to alliance side wall
	// chassis.moveTo(-37,35,1000); //move to alliance side wall

	clamp.set_value(false); // drop off mogo
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-90, 90, 2); // turn to face second goal
}

void Eclipse::Autonomous_Paths::Blue::ring_side_rush(){

}

void Eclipse::Autonomous_Paths::skills()
{
	// ALLIANCE STAKE SECTION
	intake.move_voltage(-8000);
	clamp.set_value(true);
	wall_stake.move_voltage(-12000);
	pros::delay(330); // time-based
	wall_stake.move_voltage(0);
	intake.move_voltage(0);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -7, 700); // move back into alliance stake

	wall_stake.move_voltage(12000); // move down
	pros::delay(250);

	// FIRST MOGO SECTION
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 20.5, 900, 90);	  // move forward to align with goal flat side
	clamp.set_value(false);				  // open clamp
	chassis.turnTo(100, 18.5, 800, true); // turn to face flat side of goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -35, 1000, 90); // clamp goal
	clamp.set_value(true);			  // clamp
	chassis.turnTo(100, -33, 800);	  // turn to first ring

	intake.move_voltage(-12000); // intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 900, 120); // intake first ring
	chassis.turnTo(100, 32, 800);	 // slow turn to second ring
									 // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 900, 120); // intake second ring
	pros::delay(250);
	chassis.turnTo(100, 35, 800); // slow turn to third ring
								  // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 900, 120); // intake third ring !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pros::delay(250);
	// intake.move_voltage(12000); pros::delay(100); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0, 46, 1000, 120); // intake fourth ring
	pros::delay(250);
	chassis.moveTo(0, 18, 800);	   // move to fifth ring intersection
	chassis.turnTo(-100, 80, 800); // turn to fifth ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 21.5, 1000, 120); // intake fifth ring
	pros::delay(250);
	chassis.moveTo(0, 0, 0); // move back to intersection of corner
							 // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-25, 90, 2);	   // turn to face mid (back faces corner 1)
	intake.move_voltage(0);			   // stop intake

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -37, 1000); // move back into corner 1
	clamp.set_value(false);		  // deposit goal in corner 1
	/////////////
	chassis.moveTo(0, -27, 500); // move back to intersection with goal 2 (this y-value changes the alignment with the second mogo)

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(90, 90, 0.75);  // turn back to face goal 2 @ intersection

	// SECOND MOGO SECTION
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 45, 900, 50); // POSITION RESET WALL ALIGN

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -100, 5000, 100);
	chassis.moveTo(0, -120, 5000, 90);	// move back to goal 2
	clamp.set_value(true);				// clamp goal 2
	chassis.moveTo(0, -115, 5000, 100); // move to ring alignment

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(0, 90, 2);	   // turn to face mid (back faces corner 1)

	intake.move_voltage(-12000); // intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 900, 120); // intake first ring
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-90, 90, 2);	   // turn to face second ring (absolute)

	// intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 1000, 200); // intake second ring
	pros::delay(250);
	intake.move_voltage(12000);
	pros::delay(100);
	intake.move_voltage(-12000);

	// test: remove if not useful

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-180, 90, 2);   // turn to face second ring (absolute)

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 900, 120); // intake third ring
	pros::delay(250);
	// intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0, 45, 1000, 120); // intake fourth ring
	pros::delay(250);
	chassis.moveTo(0, 20, 800);	  // move to fifth ring intersection
	chassis.turnTo(100, 80, 800); // turn to fifth ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 21.5, 1000, 120); // intake fifth ring
	pros::delay(250);
	chassis.moveTo(0, 0, 0); // move back to intersection of corner
							 // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(25, 90, 2);	   // turn to face mid (back faces corner 1)
	intake.move_voltage(0);			   // stop intake

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -35, 1000); // move back into corner 1
	clamp.set_value(false);		  // deposit goal in corner 1

	// optional for now
	chassis.moveTo(0, -18, 0); // move out of corner'

	// WALLSTAKE SECTION
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(16, 90, 2); // turn to face wall_stake ring intersection

	wall_stake.move_absolute(-520, 200);
	// pros::delay(500); //wait for wallstake to move into prime pos
	chassis.setPose(0, 0, 0);
	intake.move_voltage(-12000);
	chassis.moveTo(0, 73, 2000);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-90, 90, 2); // turn to face wall_stake ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000); // intake ring
	pros::delay(800);			 // wallstake intake delay (prime position) *NOTE: decrease if ready before-hand

	intake.move_voltage(0);				  // intake to keep ring in
	wall_stake.move_absolute(-3000, 200); // score wallstake
	pros::delay(1200);
	wall_stake.move_absolute(0, 200); // move wall stake back down

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -22, 1000); // pull out of wall stake

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(40, 90, 2); // turn to ring

	intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 46, 1000, 100); // intake ring and hold it

	pros::delay(150);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-140, 90, 2); // turn to face goal #3

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -72, 1000, 90);

	pros::delay(250);
	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(-12000); // clamp and score ring #1

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-70, 90, 2);

	pros::delay(250);

	// old
	clamp.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 90, 2000, 200);

	pros::delay(250);

	chassis.moveTo(0, 50, 1000, 200);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(80, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 250, 1000, 200);
	chassis.moveTo(0, 180, 1000, 200);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(35, 90, 2);

	wall_stake.move_absolute(-2000, 200);
	pros::delay(500);
	ratchet.set_value(true);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -90, 1000, 200);

	wall_stake.move_voltage(12000);
}

void Eclipse::Autonomous_Paths::test()
{
	// ALLIANCE STAKE SECTION
	intake.move_voltage(-8000);
	clamp.set_value(true);
	wall_stake.move_voltage(-12000);
	pros::delay(330); // time-based
	wall_stake.move_voltage(0);
	intake.move_voltage(0);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -7, 700); // move back into alliance stake

	wall_stake.move_voltage(12000); // move down
	pros::delay(250);

	// FIRST MOGO SECTION
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 20.5, 900, 90);	  // move forward to align with goal flat side
	clamp.set_value(false);				  // open clamp
	chassis.turnTo(100, 18.5, 800, true); // turn to face flat side of goal

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -35, 1000, 90); // clamp goal
	clamp.set_value(true);			  // clamp
	chassis.turnTo(100, -33, 800);	  // turn to first ring

	intake.move_voltage(-12000); // intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 900, 120); // intake first ring
	pros::delay(250);
	chassis.turnTo(100, 32, 800); // slow turn to second ring
								  // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 900, 120); // intake second ring
	pros::delay(250);
	chassis.turnTo(100, 35, 800); // slow turn to third ring
								  // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 30, 900, 120); // intake third ring !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pros::delay(250);
	// intake.move_voltage(12000); pros::delay(100); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0, 46, 1000, 120); // intake fourth ring
	pros::delay(250);
	chassis.moveTo(0, 18, 800);	   // move to fifth ring intersection
	chassis.turnTo(-100, 80, 800); // turn to fifth ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 21.5, 1000, 120); // intake fifth ring
	pros::delay(250);
	chassis.moveTo(0, 0, 0); // move back to intersection of corner
							 // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-25, 90, 2);	   // turn to face mid (back faces corner 1)
	intake.move_voltage(0);			   // stop intake

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -37, 1000); // move back into corner 1
	clamp.set_value(false);		  // deposit goal in corner 1
	/////////////
	chassis.moveTo(0, -27, 500); // move back to intersection with goal 2 (this y-value changes the alignment with the second mogo)

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(90, 90, 0.75);  // turn back to face goal 2 @ intersection

	// SECOND MOGO SECTION
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 45, 900, 50); // POSITION RESET WALL ALIGN

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -100, 5000, 100);
	chassis.moveTo(0, -120, 5000, 90);	// move back to goal 2
	clamp.set_value(true);				// clamp goal 2
	chassis.moveTo(0, -115, 5000, 100); // move to ring alignment

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(0, 90, 2);	   // turn to face mid (back faces corner 1)

	intake.move_voltage(-12000); // intake
	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 32, 900, 120); // intake first ring
	pros::delay(250);

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-90, 90, 2);	   // turn to face second ring (absolute)

	// intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 33, 1000, 200); // intake second ring
	pros::delay(250);
	intake.move_voltage(12000);
	pros::delay(100);
	intake.move_voltage(-12000);

	// test: remove if not useful

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(-180, 90, 2);   // turn to face second ring (absolute)

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 900, 120); // intake third ring
	pros::delay(250);
	// intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	chassis.moveTo(0, 45, 1000, 120); // intake fourth ring
	pros::delay(250);
	chassis.moveTo(0, 20, 800);	  // move to fifth ring intersection
	chassis.turnTo(100, 80, 800); // turn to fifth ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 21.5, 1000, 120); // intake fifth ring
	pros::delay(250);
	chassis.moveTo(0, 0, 0); // move back to intersection of corner
							 // intake.move_voltage(12000); pros::delay(300); intake.move_voltage(-12000); //reverse spin to get rid of ring jam

	r_pid.set_r_constants(2.5, 0, 15); // inertial and position reset
	r_pid.rotation_pid(25, 90, 2);	   // turn to face mid (back faces corner 1)
	intake.move_voltage(0);			   // stop intake

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -35, 1000); // move back into corner 1
	clamp.set_value(false);		  // deposit goal in corner 1

	// optional for now
	chassis.moveTo(0, -18, 0); // move out of corner'

	// WALLSTAKE SECTION
	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(16, 90, 2); // turn to face wall_stake ring intersection

	wall_stake.move_absolute(-520, 200);
	// pros::delay(500); //wait for wallstake to move into prime pos
	chassis.setPose(0, 0, 0);
	intake.move_voltage(-12000);
	chassis.moveTo(0, 73, 2000);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-88, 90, 2); // turn to face wall_stake ring

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 28, 1000); // intake ring
	pros::delay(800);			 // wallstake intake delay (prime position) *NOTE: decrease if ready before-hand

	intake.move_voltage(0);				  // intake to keep ring in
	wall_stake.move_absolute(-3000, 200); // score wallstake
	pros::delay(1200);
	wall_stake.move_absolute(0, 200); // move wall stake back down

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -22, 1000); // pull out of wall stake

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(40, 90, 2); // turn to ring

	intake.move_voltage(-12000);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 46, 1000, 100); // intake ring and hold it

	pros::delay(150);
	intake.move_voltage(0);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-140, 90, 2); // turn to face goal #3

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -72, 1000, 90);

	pros::delay(250);
	clamp.set_value(true);
	pros::delay(250);
	intake.move_voltage(-12000); // clamp and score ring #1

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(-70, 90, 2);

	// old
	clamp.set_value(false);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 90, 2000, 200);

	pros::delay(250);

	chassis.moveTo(0, 50, 1000, 200);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(80, 90, 2);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 250, 1000, 200);
	chassis.moveTo(0, 180, 1000, 200);

	r_pid.set_r_constants(2.5, 0, 15);
	r_pid.rotation_pid(30, 90, 2);

	wall_stake.move_absolute(-2000, 200);
	pros::delay(500);
	ratchet.set_value(true);

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, -80, 1500, 200);

	pros::delay(250);

	wall_stake.move_absolute(0, 200);
}