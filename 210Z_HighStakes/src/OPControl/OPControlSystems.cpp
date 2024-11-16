int score_position = 2300;
int prime_position = 760;
int color_sort_position = 650;
int down_position = 50;
int start_time = 0;

bool clamping = false;
bool doinker_down = false;
bool intake_up = false;

bool skills = false;

#include "main.h"

using namespace Eclipse;

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
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1 /**Skills: L2 */ )){ intake.move_voltage(-12000 * speed / 100); }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ intake.move_voltage(12000 * speed / 100); }
    else{ intake.move_voltage(0); }
}

// void Eclipse::OPControl::manual_wall_stake(int speed){
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ wall_stake.move_voltage(-12000 * speed / 100); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(12000 * speed / 100); }
//     else{ wall_stake.move_voltage(0); }
// }


void Eclipse::OPControl::activate_clamp(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        clamping = !clamping;
        clamp.set_value(clamping);
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

int base_lighting = 2700;
int prime_lighting = 200; // base: 2900
bool primed = false;
bool scoring = false;
bool reset = true;

void Eclipse::OPControl::prime_wall_stake(){
    if((line.get_value() < prime_lighting) && (reset == false)){
        primed = true;
        wall_stake.move_velocity(0);
    }
    if((line.get_value() > base_lighting) && (scoring == false) && (reset == false)){
        if(util.get_wall_stake_position() > prime_position){
            wall_stake.move_voltage(-3000);
        }
        else if(util.get_wall_stake_position() < prime_position){
            wall_stake.move_voltage(3000);
        }
    }
    else if(reset == true){
        primed = false;
        wall_stake.move_absolute(0, 100);
    }
}

void Eclipse::OPControl::power_wall_stake(){
    if((controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2/**Skills: R1 */ ))){
        scoring = true;
        if(scoring){
            wall_stake.move_voltage(12000);
        }
        primed = false;
        reset = false;
    }
    else{
        scoring = false;
    }

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        reset = !reset;
    }

}

void Eclipse::OPControl::driver_control(){
    driver.drivetrain_control();
    driver.power_intake(100);
    driver.prime_wall_stake();
    driver.power_wall_stake();
    driver.activate_clamp();
    driver.activate_doinker();
    driver.lift_intake();
}

void Eclipse::OPControl::activate_clamp_skills(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        clamping = !clamping;
        clamp.set_value(clamping);
    }
}

void Eclipse::OPControl::activate_doinker_skills(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        doinker_down = !doinker_down;
        doinker.set_value(doinker_down);
    }
}

void Eclipse::OPControl::lift_intake_skills(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        intake_up = !intake_up;
        intake_lift.set_value(intake_up);
    }
}

void Eclipse::OPControl::prime_wall_stake_skills(){
    if((line.get_value() < prime_lighting)){
        wall_stake.move_velocity(0);
    }
    else if(util.get_wall_stake_position() > (740)){
        if((line.get_value() > base_lighting)&&scoring){
            wall_stake.move_voltage(-3000);
        }
    }
    else if(util.get_wall_stake_position() < (prime_position)){
        if((line.get_value() > base_lighting)&&scoring){
            wall_stake.move_voltage(3000);
        }
    }
}
void Eclipse::OPControl::power_wall_stake_skills(){
    if((controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1/**Skills: R1 */ ))){
        scoring = false;
        wall_stake.move_voltage(12000);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        scoring = false;
        wall_stake.move_voltage(-12000);
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        scoring = true;
    }
    else if (scoring == false){
        wall_stake.move_velocity(0);
    }
}

void Eclipse::OPControl::skills_control(){
    driver.drivetrain_control();
    driver.power_intake(100);
    driver.prime_wall_stake_skills();
    driver.power_wall_stake_skills();
    driver.activate_clamp_skills();
    driver.activate_doinker_skills();
    driver.lift_intake_skills();
}