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
    double turnVoltage = turn_val * (12000.0 / 127) * .9; 
    double forwardVoltage = forward_val * (12000.0 / 127);
    // std:: cout << turnVoltage << std::endl;
    // std:: cout <<"linear: " << forwardVoltage << std::endl;
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

    int32_t left_power = (leftYjoystick + (rightXjoystick * 0.9));
    int32_t right_power = (leftYjoystick - (rightXjoystick * 0.9));

    left_drive.move(left_power);
    right_drive.move(right_power);
}

void Eclipse::OPControl::power_intake(int speed){ // speed in percent
    if(!driver.color_sorting){
        if(controller.get_digital(this->skills ? pros::E_CONTROLLER_DIGITAL_L2 : pros::E_CONTROLLER_DIGITAL_R1 /**Skills: L2 */ )){
            intake.move_voltage(12000 * (speed / 100));
            color.set_led_pwm(100);
        }
        else if(controller.get_digital(this->skills ? pros::E_CONTROLLER_DIGITAL_L1 : pros::E_CONTROLLER_DIGITAL_R2 /**Skills: L2 */ )){
            intake.move_voltage(-12000 * (speed / 100));
            color.set_led_pwm(100);
        }
        else{
            intake.move_voltage(0);
            color.set_led_pwm(0);
        }
    }
}

void Eclipse::OPControl::manual_wall_stake(){
    // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ wall_stake.move_voltage(12000 * speed / 100); }
    // else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(-12000 * speed / 100); }
    // else{ wall_stake.move_velocity(0); }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ wall_stake.move_voltage(12000); }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ wall_stake.move_voltage(-12000); }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){ 
        this->loading_lb = true;
    }
    else{ wall_stake.move_velocity(0); }

}

void Eclipse::OPControl::activate_clamp(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        this->clamping = !this->clamping;
        clamp.set_value(this->clamping);
    }
}

void Eclipse::OPControl::activate_right_doinker(){
    if(controller.get_digital_new_press( this->skills ? pros::E_CONTROLLER_DIGITAL_RIGHT : pros::E_CONTROLLER_DIGITAL_B/**Skills: RIGHT */)){
        this->right_doinker_down = !this->right_doinker_down;
        right_doinker.set_value(this->right_doinker_down);
    }
}

void Eclipse::OPControl::activate_left_doinker(){
    if(controller.get_digital_new_press( this->skills ? pros::E_CONTROLLER_DIGITAL_UP : pros::E_CONTROLLER_DIGITAL_RIGHT/**Skills: RIGHT */)){
        this->left_doinker_down = !this->left_doinker_down;
        left_doinker.set_value(this->left_doinker_down);
    }
}

void Eclipse::OPControl::activate_climb_claw_pto(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        this->climb_clamping = !this->climb_clamping;
        climb_claw_pto.set_value(this->climb_clamping);
    }
}

void Eclipse::OPControl::activate_climb_release(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
        climb_release.set_value(true);
    }
}

void Eclipse::OPControl::activate_wall_stake_boost(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        this->wall_stake_boost_activated = !this->wall_stake_boost_activated;
        wall_stake_boost.set_value(this->wall_stake_boost_activated);
    }
}

void Eclipse::OPControl::next_state() {
    if(this-> current_state == 1){
        this->color_sorting = true;

        intake.move_voltage(-6000);
        pros::delay(35);
        intake.move_voltage(0);

        this->color_sorting = false;
    }
    this->current_state++;
    if (this->skills ? this->current_state > this->num_states - 2 : this->current_state > this->num_states - 1) {
        this->current_state = 0;
    }
    this->target = states[this->current_state];
}

void Eclipse::OPControl::prev_state() {
	this->current_state--;
	if (this->current_state < 0) {
		this->skills ? this->current_state = this->num_states - 2 : this->current_state = this->num_states - 1;
	}
	this->target = states[this->current_state];
}

void Eclipse::OPControl::power_wall_stake(){
    // macro control
    m_pid.set_constants(.78, 0.0, 0, 3, 1, 5, 200, 127); //0.8
	m_pid.wall_stake_pid(wall_stake, wall_stake_rotation_sensor, this->target);

    // manual control
    // if(this->loading_lb){
    //     m_pid.set_constants(4, 0.0, 35, 5, 1.5, 5, 200, 100);
	//     m_pid.wall_stake_pid(wall_stake, wall_stake_rotation_sensor, -20);
    //     this->loading_lb = false;
    // }
}

void Eclipse::OPControl::control_wall_stake(){
    if (controller.get_digital_new_press(this->skills ? pros::E_CONTROLLER_DIGITAL_R2 : pros::E_CONTROLLER_DIGITAL_L1)) {
        driver.next_state();
    } else if (controller.get_digital_new_press(this->skills ? pros::E_CONTROLLER_DIGITAL_R1 : pros::E_CONTROLLER_DIGITAL_L2)) {
        driver.prev_state();
    }
}

void Eclipse::OPControl::alliance_stake(){
    this->current_state = this->num_states - 1;
    this->target = -180;

    m_pid.set_constants(4, 0.0, 15, 5, 1.5, 5, 200, 100);
    m_pid.wall_stake_pid(wall_stake, wall_stake_rotation_sensor, -180);
}


void Eclipse::OPControl::score_alliance_stake(){
    if(controller.get_digital_new_press(this->skills ? pros::E_CONTROLLER_DIGITAL_B : pros::E_CONTROLLER_DIGITAL_UP)){
        driver.alliance_stake();
    }
}

void Eclipse::OPControl::driver_control(){
    odom.update_position();
    
    this->skills ? driver.exponential_curve_accelerator() : driver.drivetrain_control();
    driver.power_intake(100);
    driver.score_alliance_stake();

    driver.activate_clamp();
    driver.activate_right_doinker();
    driver.activate_left_doinker();
    driver.activate_climb_claw_pto();
    driver.activate_climb_release();
    driver.activate_wall_stake_boost();
}