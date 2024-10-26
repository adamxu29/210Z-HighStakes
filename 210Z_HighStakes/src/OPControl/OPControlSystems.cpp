#include "main.h"

using namespace Eclipse;

bool tilting = false;
bool doinker_down = false;
bool intake_up = false;

void Eclipse::OPControl::drivetrain_control(){
    int32_t rightXjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int32_t rightYjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    int32_t leftYjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int32_t leftXjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
    if(abs(leftYjoystick) < 10) leftYjoystick = 0;
    if(abs(rightYjoystick) < 10) rightYjoystick = 0;

    int32_t left_power = (rightXjoystick + leftYjoystick) * (12000.0 / 127);
    int32_t right_power = (leftYjoystick - rightXjoystick) * (12000.0 / 127);

    left_drive.move_voltage(left_power);
    right_drive.move_voltage(right_power);
}

void Eclipse::OPControl::power_intake(int speed){ // speed in percent
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ intake.move_voltage(-12000 * speed / 100); }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ intake.move_voltage(12000 * speed / 100); }
    else{ intake.move_voltage(0); }
}

// void Eclipse::OPControl::power_wall_stake(int speed){
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ wall_stake.move_voltage(-12000 * speed / 100); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ wall_stake.move_voltage(12000 * speed / 100); }
//     else{ wall_stake.move_voltage(0); }
// }


void Eclipse::OPControl::activate_tilter(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        tilting = !tilting;
        tilter.set_value(tilting);
    }
}

void Eclipse::OPControl::activate_doinker(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        doinker_down = !doinker_down;
        doinker.set_value(doinker_down);
    }
}

void Eclipse::OPControl::lift_intake(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        intake_up = !intake_up;
        intake_lift.set_value(intake_up);
    }
}

bool prime = false;
int score_position = -1800;
int prime_position = -200;
int down_position = 0;

void Eclipse::OPControl::power_wall_stake(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        prime = true;
        while (!(wall_stake.get_position() < (score_position + 5))) {
            wall_stake.move_absolute(score_position, 200);
        }
        wall_stake.move_absolute(prime_position, 200);
    }

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
        if(prime){
            prime = !prime;
            wall_stake.move_absolute(down_position, 200);
        }
        else{
            prime =! prime;
            wall_stake.move_absolute(prime_position, 100);
        }
    }
}

void Eclipse::OPControl::driver_control(){
    driver.drivetrain_control();
    driver.power_intake(100);
    wall_stake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    driver.power_wall_stake();
    driver.activate_tilter();
    driver.activate_doinker();
    driver.lift_intake();
}