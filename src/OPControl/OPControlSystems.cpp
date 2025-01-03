int score_position = 2300;
int prime_position = -520;

bool clamping = false;
bool doinker_down = false;
bool intake_up = false;
bool ratchet_used = false;

bool skills = false;

#include "main.h"

using namespace Eclipse;

const u_int16_t forwardCurve       = 10;
const u_int16_t turnCurve          = 3;
const double euler                 = 2.71828;
static bool toggleRedCurve         = false; // toggle red curve
static bool turningRed             = false; // turning curve
static bool forwardRed             = false; // linear curve

int32_t joystick_accelerator(bool red, int8_t input, const double t){
    int16_t value = 0;
    // exponential formula
    if (red) { value = (std::exp(-t / 10) + std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) * input; } 
    else { value = std::exp(((std::abs(input) - 100) * t) / 1000) * input; }
    return value;
}

void Eclipse::OPControl::exponential_curve_accelerator(){
    int32_t rightXjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)); // Axis 1
    int32_t rightYjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)); // Axis 2
    int32_t leftYjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)); // Axis 3
    int32_t leftXjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)); // Axis 4
    if(abs(leftYjoystick) < 10) leftYjoystick = 0;
    if(abs(rightYjoystick) < 10) rightYjoystick = 0;

    double turn_val = joystick_accelerator(turningRed, rightXjoystick, turnCurve);
    double forward_val = joystick_accelerator(forwardRed, leftYjoystick, forwardCurve);
    double turnVoltage = turn_val * (12000.0 / 127); 
    double forwardVoltage = forward_val * (12000.0 / 127);
    std:: cout << turnVoltage << std::endl;
    std:: cout <<"linear: " << forwardVoltage << std::endl;
    double left =  forwardVoltage + turnVoltage;
    double right = forwardVoltage - turnVoltage;
    left_drive.move_voltage(left);
    right_drive.move_voltage(right);
}

void Eclipse::OPControl::drivetrain_control(){
    int32_t rightXjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int32_t rightYjoystick = (controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    int32_t leftYjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int32_t leftXjoystick  = (controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));

    int32_t left_power = (rightXjoystick + leftYjoystick);
    int32_t right_power = (leftYjoystick - rightXjoystick);

    left_drive.move(left_power);
    right_drive.move(right_power);
}

void Eclipse::OPControl::power_intake(int speed){ // speed in percent
    if(controller.get_digital(skills ? pros::E_CONTROLLER_DIGITAL_L2 : pros::E_CONTROLLER_DIGITAL_R1 /**Skills: L2 */ )){ intake.move_voltage(-12000 * speed / 100); }
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
    if(controller.get_digital_new_press( skills ? pros::E_CONTROLLER_DIGITAL_Y : pros::E_CONTROLLER_DIGITAL_B/**Skills: RIGHT */)){
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
    if((line.get_value() < prime_lighting)){
        wall_stake.move_velocity(0);
    }
    else if(util.get_wall_stake_position() > (prime_position - 10)){
        if((line.get_value() > base_lighting) && scoring){
            wall_stake.move_voltage(-3000);
        }
    }
    else if(util.get_wall_stake_position() < (prime_position)){
        if((line.get_value() > base_lighting) && scoring){
            wall_stake.move_voltage(3000);
        }
    }
}

void Eclipse::OPControl::power_wall_stake(){
    if((controller.get_digital(skills ? pros::E_CONTROLLER_DIGITAL_L1 : pros::E_CONTROLLER_DIGITAL_L2/**Skills: L1 */))){
        scoring = false;
        wall_stake.move_voltage(12000);
    }
    else if(controller.get_digital(skills ? pros::E_CONTROLLER_DIGITAL_R1 : pros::E_CONTROLLER_DIGITAL_L1)){
        scoring = false;
        wall_stake.move_voltage(-12000);
    }
    else if(controller.get_digital_new_press(skills ? pros::E_CONTROLLER_DIGITAL_B : pros::E_CONTROLLER_DIGITAL_RIGHT/**Skills: B */)){
        scoring = true;
    }
    else if (scoring == false){
        wall_stake.move_velocity(0);
    }
}

void Eclipse::OPControl::ratchet_mech(){
    if((controller.get_digital_new_press(skills ? pros::E_CONTROLLER_DIGITAL_RIGHT : pros::E_CONTROLLER_DIGITAL_UP))){
        ratchet_used = !ratchet_used;
        ratchet.set_value(ratchet_used);
    }
}

void Eclipse::OPControl::driver_control(){
    skills ? driver.exponential_curve_accelerator() : driver.drivetrain_control();
    driver.power_intake(100);
    driver.prime_wall_stake();
    driver.power_wall_stake();
    driver.activate_clamp();
    driver.activate_doinker();
    driver.lift_intake();
    driver.ratchet_mech();
}