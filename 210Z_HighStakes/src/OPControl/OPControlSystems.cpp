bool prime = false;
int score_position = 2300;
int prime_position = 700;
int color_sort_position = 650;
int down_position = 50;
int start_time = 0;

// MAXWELL VERSION
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
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ intake.move_voltage(-12000 * speed / 100); }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ intake.move_voltage(12000 * speed / 100); }
    else{ intake.move_voltage(0); }
}

// void Eclipse::OPControl::manual_wall_stake(int speed){
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ wall_stake.move_voltage(-12000 * speed / 100); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(12000 * speed / 100); }
//     else{ wall_stake.move_voltage(0); }
// }


void Eclipse::OPControl::activate_tilter(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
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


void Eclipse::OPControl::power_wall_stake(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
        prime = false;
        wall_stake.move_voltage(12000);
    }
    else{
        wall_stake.move_velocity(0);
    }

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){ 
        start_time = pros::millis();
        if (!prime){
            prime =! prime;
            while (util.get_wall_stake_position() < (prime_position - 10) || util.get_wall_stake_position() > (prime_position + 10)) {    // failsafe
                if((pros::millis() - start_time) > 1500){
                    break;
                }
                wall_stake.move_absolute(prime_position, 150);
            }
        }
        else if(prime){
            prime = !prime;
            while (util.get_wall_stake_position() > (down_position + 10)) {
                if((pros::millis() - start_time) > 1500){
                    break;
                }    // failsafe
                wall_stake.move_absolute(down_position + 5, 200);
            }
        } 
        else{
            wall_stake.move_velocity(0);
        }
    }
}

void Eclipse::OPControl::driver_control(){
    driver.drivetrain_control();
    driver.power_intake(100);
    // driver.manual_wall_stake(100);
    driver.power_wall_stake();
    driver.activate_tilter();
    driver.activate_doinker();
    driver.lift_intake();
}





































// KEVIN SKILLSVERSION
// #include "main.h"

// using namespace Eclipse;

// bool tilting = false;
// bool doinker_down = false;
// bool intake_up = false;

// void Eclipse::OPControl::drivetrain_control(){
//     int32_t rightXjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
//     int32_t rightYjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
//     int32_t leftYjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
//     int32_t leftXjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
//     if(abs(leftYjoystick) < 10) leftYjoystick = 0;
//     if(abs(rightYjoystick) < 10) rightYjoystick = 0;

//     int32_t left_power = (rightXjoystick + leftYjoystick) * (12000.0 / 127);
//     int32_t right_power = (leftYjoystick - rightXjoystick) * (12000.0 / 127);

//     left_drive.move_voltage(left_power);
//     right_drive.move_voltage(right_power);
// }

// void Eclipse::OPControl::power_intake(int speed){ // speed in percent
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ intake.move_voltage(-12000 * speed / 100); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ intake.move_voltage(12000 * speed / 100); }
//     else{ intake.move_voltage(0); }
// }

// void Eclipse::OPControl::manual_wall_stake(int speed){
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ wall_stake.move_voltage(12000 * speed / 100); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(-12000 * speed / 100); }
//     else{ wall_stake.move_voltage(0); }
// }

// void Eclipse::OPControl::prime_wall_stake(){
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
//         // start_time = pros::millis();
//         while (util.get_wall_stake_position() < (prime_position - 5) || util.get_wall_stake_position() > (prime_position + 5)) {    // failsafe
//             // if(start_time - pros::millis() > 1500){
//             //     break;
//             // }
//             std::cout << "macro" << std::endl;
//             wall_stake.move_absolute(prime_position, 200);
            
//         }
//     }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ wall_stake.move_voltage(12000); }
//     else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(-12000); }

//     else{
//         wall_stake.move_velocity(0);
//     }
// }

// void Eclipse::OPControl::activate_tilter(){
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
//         tilting = !tilting;
//         tilter.set_value(tilting);
//     }
// }

// void Eclipse::OPControl::activate_doinker(){
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
//         doinker_down = !doinker_down;
//         doinker.set_value(doinker_down);
//     }
// }

// void Eclipse::OPControl::lift_intake(){
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
//         intake_up = !intake_up;
//         intake_lift.set_value(intake_up);
//     }
// }

// void Eclipse::OPControl::driver_control(){
//     driver.drivetrain_control();
//     driver.power_intake(100);
//     // driver.manual_wall_stake(100);
//     driver.prime_wall_stake();
//     driver.activate_tilter();
//     driver.activate_doinker();
//     driver.lift_intake();
// }