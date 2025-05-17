#include "main.h"
#include "pros/motors.h"
#include "map"

/*
Odometry coord finder: //https://path.jerryio.com/
*/

using namespace Eclipse;

// Translation PID constants: 5, 0.0025, 35, 600
// Rotation PID constants: 4.5, 0, (27 (θ = 45), 30 (θ = 90), 31 (θ = 180))
// Curve PID constants: 5, 0, 30

// Red paths
void Eclipse::Autonomous_Paths::Red::solo_awp()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-48, 127, .7);

    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-10, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-27, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(7.3, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(23, 127, .7);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-16, 127, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-50, 90, 2, -.1, false);

    intake.move_voltage(9000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(37, 90, 1);

    r_pid.set_r_constants(4.5, 0, 29);
    r_pid.rotation_pid(-90, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(20, 90, .7);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(28, 90, 1);

    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-135, 127, .7);

    clamp.set_value(false);

    util.stop_on_color = true;
    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(32, 90, 1);

    intake.move_voltage(9000);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-90, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-26, 75, 1);

    wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    clamp.set_value(true);
    pros::delay(100);
    util.stop_on_color = false;
    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(135, 127, 1, -.5, false);

    util.sorting = false;
    driver.alliance_stake();

    pros::delay(250);

    intake.move_voltage(12000);
}

void Eclipse::Autonomous_Paths::Red::left_half_awp()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-48, 127, .7);

    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-10, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-27, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(7.3, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(23, 127, .7);

    intake.move_voltage(120000);
    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-16, 127, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-45, 90, .7, -.05, false);

    intake.move_voltage(12000);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-15, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(19, 90, .7);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(40, 127, .7);

    driver.alliance_stake();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(39, 90, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-18, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(16, 90, .7);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(30, 90, .7);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600); 
    t_pid.translation_pid(-50, 90, 1.2);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-135, 90, 2, -.5, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(7, 90, 1);

    util.sorting = false;
    driver.alliance_stake();
}

void Eclipse::Autonomous_Paths::Red::right_half_awp()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(46, 90, 1);

    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(12, 90, 1, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-26, 75, 1);

    clamp.set_value(true);
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-90, 90, 1);

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(22, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(27, 90, 1);

    pros::delay(250);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-45, 90, 1); //-42

    driver.alliance_stake();
    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(20, 90, 1);

    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-12, 50, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(12, 75, 1);

    driver.next_state();
    pros::delay(250);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-30, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-50, 127, 1);

    intake.move_voltage(0);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(135, 127, 2, -.35, false);

    driver.alliance_stake();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(5, 50, 1);
}

void Eclipse::Autonomous_Paths::Red::goal_side_rush()
{
    left_doinker.set_value(true);
    util.stop_on_color = true;
    intake.move_voltage(9000);

	t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(35, 127, 1);

    
}

void Eclipse::Autonomous_Paths::Red::ring_side_rush()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-48, 127, .7);

    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-10, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-27, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(7.3, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(23, 127, .7);

    intake.move_voltage(120000);
    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-16, 127, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-45, 90, .7, -.05, false);

    intake.move_voltage(12000);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-15, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(19, 90, .7);

    driver.alliance_stake();

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(40, 127, .7);

    driver.alliance_stake();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(39, 90, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-18, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(16, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-14, 90, .7);

    driver.next_state();

    r_pid.set_r_constants(4.5, 0, 33);
    r_pid.rotation_pid(-90, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(36, 90, 1.5);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 90, .7);
}

// Blue paths
void Eclipse::Autonomous_Paths::Blue::solo_awp()
{
	r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(48, 127, .7);

    util.sorting = false;
    intake.move_voltage(0); //alliance stake
    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(12, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-25, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(9.8, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 127, .7);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-17, 127, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(50, 90, 2, -.1, false);

    intake.move_voltage(9000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(37, 90, 1);

    intake.move_voltage(12000);

    r_pid.set_r_constants(4.5, 0, 29);
    r_pid.rotation_pid(90, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(20, 90, .7);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(28, 90, 1);

    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(135, 127, .7);

    clamp.set_value(false);

    util.stop_on_color = true;
    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 90, 1);

    intake.move_voltage(9000);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-27, 75, 1);

    wall_stake.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    clamp.set_value(true);
    pros::delay(100);
    util.stop_on_color = false;

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-135, 127, 1, -.4, false);

    util.sorting = false;
    driver.alliance_stake();

    pros::delay(250);

    intake.move_voltage(12000);
}

void Eclipse::Autonomous_Paths::Blue::left_half_awp()
{   
    pros::delay(2000);
    // pros::delay(500);
    // driver.next_state();
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-47, 90, 1);
    // intake.move_voltage(12000);
    // pros::delay(250);
    // score wall stake

    driver.alliance_stake();
    // intake.move_voltage(0);
    pros::delay(500);
    

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-12, 90, 1, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-24, 75, 1);

    pros::delay(250); // can remove later
    clamp.set_value(true);
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, 1);

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(22, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, 1);

    pros::delay(250);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(42, 90, 1);

    driver.prev_state();
    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(17, 75, 1);

    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-12, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(12, 75, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-12, 90, 1);
    right_doinker.set_value(true);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(10, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 127, 2);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-20, 127, 1);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(180, 127, .7);

    clamp.set_value(false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(15, 127, 1);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(0, 127, .7);
}

void Eclipse::Autonomous_Paths::Blue::right_half_awp()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(48, 127, .7);

    intake.move_voltage(0); //alliance stake
    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(12, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-25, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(9.8, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 60, 3); //24, 90, .7

    pros::delay(350);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-18, 90, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(45, 90, .7, -.04, false);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(15, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(21, 90, .7);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-38, 127, .7);

    driver.alliance_stake();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(39, 80, 1.2);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-20, 50, .7);

    pros::delay(350);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(20, 75, .7);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-30, 90, .7);

    driver.prev_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600); 
    t_pid.translation_pid(-50, 90, 1.2);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(135, 90, 2, -.5, false);

    driver.alliance_stake();
}

void Eclipse::Autonomous_Paths::Blue::goal_side_rush()
{
	left_doinker.set_value(true);
    util.stop_on_color = true;
    intake.move_voltage(9000);

	t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(35, 127, 1);
}

void Eclipse::Autonomous_Paths::Blue::ring_side_rush()
{
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(48, 127, .7);

    intake.move_voltage(0); //alliance stake
    // score wall stake
    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(12, 90, .7, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-25, 60, 1);

    clamp.set_value(true);
    pros::delay(150);

    // try driving directly to the first ring instead of curving from the side

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-152, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(9.8, 90, .5);

    intake.move_voltage(12000);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-89, 90, 1, 0.09, false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 60, 3); //24, 90, .7

    pros::delay(350);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-18, 90, .5);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(45, 90, .7, -.04, false);

    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(15, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(21, 90, .7);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(-38, 127, .7);

    driver.alliance_stake();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(39, 80, 1.2);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-20, 50, .7);

    pros::delay(350);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(20, 75, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-14, 90, .7);

    driver.next_state();

    r_pid.set_r_constants(4.5, 0, 33);
    r_pid.rotation_pid(90, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(36, 90, 1.5);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(25, 90, .7);
}

// Misc paths
void Eclipse::Autonomous_Paths::skills()
{
    driver.color_sorting = false;
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intake.move_voltage(12000); //alliance stake
    pros::delay(500);
    intake.move_voltage(0);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(11.2, 90, .9);

    r_pid.set_r_constants(4.5, 0, 31); //face goal 1
    r_pid.rotation_pid(-90, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-14, 90, 1.5);
    t_pid.translation_pid(-8.5, 50, 2); //back up a bit

    clamp.set_value(true);
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 31); //face ring 1 up
    r_pid.rotation_pid(0, 90, .9);

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, 1.5);
    t_pid.translation_pid(-2, 90, 0.9); //back up a bit

    r_pid.set_r_constants(4.5, 0, 31); //face ring 2
    r_pid.rotation_pid(26.6, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(54, 90, 2); //53.7

    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31); //move back theta (bisect truss and wallstake)
    r_pid.rotation_pid(10, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-23.3, 90,2); //<- align with wallstake 1
    
    //pros::delay(100); //not rly needed

    r_pid.set_r_constants(4.5, 0, 29);
    r_pid.rotation_pid(86.4, 90, .7); //face wallstake 1

    driver.next_state();
    pros::delay(500);
    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(15, 80, 2); //move into wall ring
    pros::delay(700); //index delay
    intake.move_voltage(0);
    t_pid.translation_pid(3,80,.7); //move into wallstake 1

    driver.next_state();
    driver.next_state();
    pros::delay(800); //score delay

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-10.5, 90, .7); //move out of wallstake 1
    driver.next_state(); //lb down

    r_pid.set_r_constants(4.5, 0, 30); //face ring chain left side
    r_pid.rotation_pid(178, 90, .8);
    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(36, 70, 4); //move to ring chain

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(32, 30, 4); //slow push through

    r_pid.set_r_constants(4.5, 0, 31); //last ring
    r_pid.rotation_pid(50, 90, .9);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(16, 90, 1); //move to last ring
    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(-20, 90, .7); //corner face

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-15, 90, 1); //move into corner
    pros::delay(150);
    clamp.set_value(false);
    intake.move_voltage(-12000); //hits goal away, prevents jamming
    pros::delay(100);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(6, 90, .7); //move out of corner

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(90, 90, .7); //face wall to align

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, .6); //push into wall

    //second goal <-> half switch

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-70, 90, 3); //move to goal 2

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-23, 50, 3); //slow reverse to clamp

    clamp.set_value(true);
    pros::delay(200);

    ////////////////////////////////paste here


    r_pid.set_r_constants(4.5, 0, 31); //face ring 1 up [FOR GOAL 2 KEEP IN MIND]
    r_pid.rotation_pid(0, 90, .9);

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, 1.5);
    t_pid.translation_pid(-2, 90, 0.9); //back up a bit

    r_pid.set_r_constants(4.5, 0, 31); //face ring 2
    r_pid.rotation_pid(-26.6, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(54, 90, 2); //53.7

    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31); //move back theta (bisect truss and wallstake)
    r_pid.rotation_pid(-14, 90, .7);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-24.8, 90,2); //<- align with wallstake 2
    
    //pros::delay(100); //not rly needed

    r_pid.set_r_constants(4.5, 0, 29);
    r_pid.rotation_pid(-86.4, 90, .7); //face wallstake 2

    driver.next_state();
    pros::delay(500);
    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(15, 80, 2); //move into wall ring
    pros::delay(700); //index delay
    intake.move_voltage(0);
    t_pid.translation_pid(3,80,.7); //move into wallstake 2

    driver.next_state();
    driver.next_state();
    pros::delay(1000); //score delay

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-9.8, 90, .7); //move out of wallstake 2
    driver.next_state(); //lb down

    r_pid.set_r_constants(4.5, 0, 30); //face ring chain right side
    r_pid.rotation_pid(-178, 90, .8);
    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(36, 70, 4); //move to ring chain

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(32, 30, 4); //slow push through

    r_pid.set_r_constants(4.5, 0, 31); //last ring
    r_pid.rotation_pid(-50, 90, .9);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(16, 90, 1); //move to last ring
    pros::delay(300);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(20, 90, .7); //corner face

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-15, 90, 1); //move into corner
    pros::delay(150);
    clamp.set_value(false);
    intake.move_voltage(-12000); //hits goal away, prevents jamming
    pros::delay(100);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(6, 90, .7); //move out of corner

}

void Eclipse::Autonomous_Paths::test()
{   

	// t_pid.set_t_constants(5, 0.0025, 35, 600);
    // t_pid.translation_pid(10, 127, 1);
    // driver.alliance_stake();

    gui.selected_color = 1;
    pros::delay(2000);
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-47, 90, 1);

    // score wall stake

    driver.alliance_stake();
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-12, 90, 1, 0.4, true);

    driver.next_state();

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-24, 75, 1);

    pros::delay(250); // can remove later
    clamp.set_value(true);
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, 1);

    intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(22, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(24, 90, 1);

    pros::delay(250);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(42, 90, 1);

    driver.prev_state();
    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(17, 75, 1);

    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-12, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(12, 75, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-12, 90, 1);
    right_doinker.set_value(true);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(12, 75, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 127, 2);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-20, 127, 1);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(180, 127, .7);

    clamp.set_value(false);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(15, 127, 1);

    r_pid.set_r_constants(4.5, 0, 31);
    r_pid.rotation_pid(0, 127, .7);
}