#include "main.h"

using namespace Eclipse;

bool tilter_tilting = false;

void Eclipse::OPControl::drivetrain_control(){
    int32_t rightXjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int32_t rightYjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    int32_t leftYjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int32_t leftXjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
    if(abs(leftYjoystick) < 10) leftYjoystick = 0;
    if(abs(rightYjoystick) < 10) rightYjoystick = 0;

    int32_t left_power = (rightXjoystick + leftYjoystick) * (12000.0 / 127);
    int32_t right_power = (leftYjoystick - rightXjoystick) * (12000.0 / 127);

    util.move_left_drive(left_power);
    util.move_right_drive(right_power);
}

void Eclipse::OPControl::power_intake(int speed){ // speed in percent
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ util.move_intake(12000 * speed / 100); }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ util.move_intake(-12000 * speed / 100); }
    else{ util.move_intake(0); }
}

void Eclipse::OPControl::wall_stake(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){ util.move_tilter(); }
}

void Eclipse::OPControl::activate_tilter(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){ util.move_tilter(); }
}

void Eclipse::OPControl::activate_doinker(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){ util.move_doinker(); }
}

void Eclipse::OPControl::driver_control(){
    driver.drivetrain_control();
    driver.power_intake(100);
    driver.wall_stake();
    driver.activate_tilter();
    driver.activate_doinker();
}