#include "main.h"
#include "pros/motors.h"
#include "map"

/*
Odometry coord finder: //https://path.jerryio.com/
*/

using namespace Eclipse;

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
    util.set_robot_position(0, 0);
	drive.set_constants(5, 0, 15, 2.5, 0, 18, 90, 75);
    drive.turn_to_point(-24, 0, 2);

    // pros::delay(1000);
    // drive.set_constants(5, 0, 15, 4, 0, 18, 90, 75);
    // drive.turn_to_point(-24, 0, 1);

    // pros::delay(1000);
    // t_pid.set_t_constants(5, 0, 15, 600);
    // t_pid.translation_pid(24, 75, 2);

    // pros::delay(1000);
    // drive.set_constants(5, 0, 15, 2.5, 0, 18, 90, 75);
    // drive.turn_to_point(24, 24, 2.0);

    // r_pid.set_r_constants(2.5, 0, 18);
    // r_pid.rotation_pid(90, 90, 2);

}