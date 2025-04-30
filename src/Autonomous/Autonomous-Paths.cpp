#include "main.h"
#include "pros/motors.h"
#include "map"

/*
Odometry coord finder: //https://path.jerryio.com/
*/

using namespace Eclipse;

// Rotation PID constants: 4.5, 0, (27 (θ = 45), 30 (θ = 90), 31 (θ = 180))

// Red paths
void Eclipse::Autonomous_Paths::Red::solo_awp()
{
    util.sort_red(); //sort for red rings

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-44, 90, 1); //face alliance stake from ring side
    intake.move_voltage(0);

    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-14, 90, 1, 0.29, true); //face goal backwards
    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-26.3, 75, 1); //move onto goal

    intake.move_voltage(0);

    clamp.set_value(true); //clamp goal 1 on ring side
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, 1); //turn to ring 1

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(27, 90, 1); //intake ring <- 24

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(180,90, 1); //turn to ring stake left side

    // t_pid.set_t_constants(5, 0.0025, 35, 600);
    // t_pid.translation_pid(16, 90, 1); //intake ring 2 (left side of ring stack)

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-90, 70, 3, 0.24, false); //curve into ring 2 & 3 (right side of ring stack)

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-32,90, 1); //turn to middle stack thing

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(80, 90, 1); //move back to mid

    pros::delay(500); //acceptable intake delay?

    clamp.set_value(false);

    util.stop_on_color = true;
    intake.move_voltage(6000);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-90,90, 1); //turn to mid face -intake

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(46, 90, 1); //intake ring 5 - load into index
    pros::delay(200);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(0,90, 1); //turn to goal
    util.stop_on_color = false;

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-24, 90, 1); //intake ring 2 (left side of ring stack)

    clamp.set_value(true); //second goal
    intake.move_voltage(12000);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-90,90, 1); //turn to last ring

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(26, 90, 1); //intake last ring

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-80, 90, 1); //touch bar

    intake.move_voltage(0);
}

void Eclipse::Autonomous_Paths::Red::left_half_awp()
{
	
}

void Eclipse::Autonomous_Paths::Red::right_half_awp()
{

}

void Eclipse::Autonomous_Paths::Red::goal_side_rush()
{
	
}

void Eclipse::Autonomous_Paths::Red::ring_side_rush()
{

}

// Blue paths
void Eclipse::Autonomous_Paths::Blue::solo_awp()
{
	
}

void Eclipse::Autonomous_Paths::Blue::left_half_awp()
{
    util.sort_blue();
    
    // t_pid.set_t_constants(5, 0.0025, 35, 600);
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-44, 90, 1);
    intake.move_voltage(0);

    // score wall stake
    driver.alliance_stake();
    pros::delay(450);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-14, 90, 2, 0.4, true);
    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-26.5, 75, 1.5);

    intake.move_voltage(0);

    clamp.set_value(true); //clamp
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, 1); //turn to ring

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(22.5, 90, 1); //intake ring

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 90, 1); //turn to wrong color ring

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, 1); //intake wrong color ring

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(45, 90, 1); //turn to corner

    pros::delay(300);

    t_pid.set_t_constants(5.5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 127, 2.5);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-23, 100, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 100, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600); //again
    t_pid.translation_pid(-20, 100, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 100, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600); //again
    t_pid.translation_pid(-20, 100, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(30, 100, 1); //yet again

    pros::delay(250);
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(45, 90, 1); //face bar

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-40, 90, 2); //move back

    // move lb up if necessary
    intake.move_voltage(0);
    driver.next_state();
    
    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-29, 50, 5); //touch bar

    driver.prev_state();
    // c_pid.set_c_constants(5, 0, 30);
    // c_pid.curve_pid(-135, 90, 1.5, 0.2, false);
}

void Eclipse::Autonomous_Paths::Blue::right_half_awp()
{
	
}

void Eclipse::Autonomous_Paths::Blue::goal_side_rush()
{
	
}

void Eclipse::Autonomous_Paths::Blue::ring_side_rush()
{

}

// Misc paths
void Eclipse::Autonomous_Paths::skills()
{
	
}

void Eclipse::Autonomous_Paths::test()
{   

}