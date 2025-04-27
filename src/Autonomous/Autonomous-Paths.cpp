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
    gui.selected_color = 1;
    // t_pid.set_t_constants(5, 0.0025, 35, 600);
    r_pid.set_r_constants(4.5, 0, 27);
    r_pid.rotation_pid(-47, 90, 1);

    // score wall stake
    pros::delay(500);

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-15, 90, 1, 0.4, true);
    
    intake.move_voltage(0);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-24, 75, 1);

    intake.move_voltage(0);

    clamp.set_value(true);
    pros::delay(100);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(90, 90, 1);

    // intake.move_voltage(12000);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(23, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(0, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(26, 90, 1);

    r_pid.set_r_constants(4.5, 0, 30);
    r_pid.rotation_pid(42, 90, 1);

    pros::delay(500);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(15, 75, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-15, 90, 1);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(10, 75, 1);

    pros::delay(250);

    t_pid.set_t_constants(5, 0.0025, 35, 600);
    t_pid.translation_pid(-60, 90, 1);

    // move lb up

    c_pid.set_c_constants(5, 0, 30);
    c_pid.curve_pid(-135, 90, 1.5, 0.2, false);
}