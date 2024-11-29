#include "main.h"

using namespace Eclipse;

void Eclipse::PID_Tuner::print_constants(){
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "Kp: " << tuner.kp << std::endl;
    std::cout << "Ki: " << tuner.ki << std::endl;
    std::cout << "Kd: " << tuner.kd << std::endl;
    std::cout << "Kp increment: " << tuner.kp_increment << std::endl;
    std::cout << "Ki_increment: " << tuner.ki_increment << std::endl;
    std::cout << "Kd_increment: " << tuner.kd_increment << std::endl;
    std::cout << "Current constant: " << tuner.current_constant << std::endl;
    std::cout << "Current movement: " << tuner.current_movement << std::endl;
}

void Eclipse::PID_Tuner::change_constant(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
        if(tuner.current_constant < 2){
            tuner.current_constant++;
            tuner.print_constants();
        }
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
        if(tuner.current_constant > 0){
            tuner.current_constant--;
            tuner.print_constants();
        }
    }
}

void Eclipse::PID_Tuner::change_movement(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        if(tuner.current_movement < 2){
            tuner.current_movement++;
            tuner.print_constants();
        }
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
        if(tuner.current_movement > 0){
            tuner.current_movement--;
            tuner.print_constants();
        }
    }
}

void Eclipse::PID_Tuner::update_constants(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
        if(tuner.current_constant == 0){
            tuner.kp += tuner.kp_increment;
            tuner.print_constants();
        }
        else if(tuner.current_constant == 1){
            tuner.ki += tuner.ki_increment;
            tuner.print_constants();
        }
        else if(tuner.current_constant == 2){
            tuner.kd += tuner.kd_increment;
            tuner.print_constants();
        }
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        if (tuner.current_constant == 0){
            tuner.kp -= tuner.kp_increment;
            tuner.print_constants();
        }
        else if (tuner.current_constant == 1){
            tuner.ki -= tuner.ki_increment;
            tuner.print_constants();
        }
        else if (tuner.current_constant == 2){
            tuner.kd -= tuner.kd_increment;
            tuner.print_constants();
        }
    }
}

void Eclipse::PID_Tuner::set_brake_coast(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
        left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	    right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        std::cout << "brake mode set to coast" << std::endl;
    }
}

void Eclipse::PID_Tuner::set_brake_hold(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
        left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	    right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        std::cout << "brake mode set to hold" << std::endl;
    }
}

void Eclipse::PID_Tuner::move(){
    if(tuner.current_movement == 0){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
            t_pid.set_t_constants(tuner.kp, tuner.ki, tuner.kd, 600);
            t_pid.translation_pid(24, 75, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            t_pid.set_t_constants(tuner.kp, tuner.ki, tuner.kd, 600);
            t_pid.translation_pid(-24, 90, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
            t_pid.set_t_constants(tuner.kp, tuner.ki, tuner.kd, 600);
            t_pid.translation_pid(48, 90, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            t_pid.set_t_constants(tuner.kp, tuner.ki, tuner.kd, 600);
            t_pid.translation_pid(-48, 90, 2);
        }
    }
    else if(tuner.current_movement == 1){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
            r_pid.set_r_constants(tuner.kp, tuner.ki, tuner.kd);
            r_pid.rotation_pid(90, 90, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            r_pid.set_r_constants(tuner.kp, tuner.ki, tuner.kd);
            r_pid.rotation_pid(180, 90, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
            r_pid.set_r_constants(tuner.kp, tuner.ki, tuner.kd);
            r_pid.rotation_pid(270, 90, 2);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            r_pid.set_r_constants(tuner.kp, tuner.ki, tuner.kd);
            r_pid.rotation_pid(360, 90, 2);
        }
    }
    else if(tuner.current_movement == 2){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
            c_pid.set_c_constants(tuner.kp, tuner.ki, tuner.kd);
            c_pid.curve_pid(90, 90, 3, 0.5, false);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            c_pid.set_c_constants(tuner.kp, tuner.ki, tuner.kd);
            c_pid.curve_pid(90, 90, 3, 0.5, true);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
            c_pid.set_c_constants(tuner.kp, tuner.ki, tuner.kd);
            c_pid.curve_pid(-90, 90, 3, 0.5, false);
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            c_pid.set_c_constants(tuner.kp, tuner.ki, tuner.kd);
            c_pid.curve_pid(-90, 90, 3, 0.5, true);
        }
    }
}

void Eclipse::PID_Tuner::driver_tuner(){
    tuner.change_constant();
    tuner.change_movement();
    tuner.update_constants();
    tuner.set_brake_coast();
    tuner.set_brake_hold();
    tuner.move();
}
