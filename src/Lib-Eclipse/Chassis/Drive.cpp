#include "main.h"


using namespace Eclipse;

void Eclipse::Drive::set_constants(const double t_kp, const double t_ki, const double t_kd, const double r_kp, const double r_ki, const double r_kd, const double max_translation_speed, const double max_rotation_speed){
    this->t_kp = t_kp;
    this->t_ki = t_ki;
    this->t_kd = t_kd;
    this->r_kp = r_kp;
    this->r_ki = r_ki;
    this->r_kd = r_kd;
    this->max_translation_speed = max_translation_speed;
    this->max_rotation_speed = max_rotation_speed;
}

Eclipse::Drive::Drive(){
    this->t_error_threshold = 0;
    this->t_tolerance = 0;
    this->r_error_threshold = 3;
    this->r_tolerance = 0;
}

void Eclipse::Drive::reset_variables(){
    this->t_error = 0;
    this->t_integral = 0;
    this->t_derivative = 0;
    this->t_prev_error = 0;
    this->t_counter = 0;
    this->t_failsafe = 0;

    this->r_error = 0;
    this->r_integral = 0;
    this->r_derivative = 0;
    this->r_prev_error = 0;
    this->r_counter = 0;
    this->r_failsafe = 0;
}

void Eclipse::Drive::turn_to_point(double x, double y, double time_out){
    // this->reset_variables();
    r_pid.reset_r_variables();
    r_pid.set_r_constants(this->r_kp, this->r_ki, this->r_kd);

    double local_timer = 0;
    r_pid.r_max_speed = this->max_rotation_speed;
    
    while(true){
        odom.update_position();
        double current_position = util.get_heading();
        double theta = util.get_min_angle(util.get_angular_error(x, y, false)) * 180 / M_PI;
        
        double voltage = r_pid.compute_r(current_position, theta);

        left_drive.move_voltage(voltage * (12000.0 / 127.0));
        right_drive.move_voltage(-voltage * (12000.0 / 127.0));
        
        fabs(r_pid.r_error) < r_pid.r_error_threshold ? r_pid.r_counter++ : r_pid.r_counter = 0;

        if (r_pid.r_counter >= r_pid.r_tolerance)
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            break;
        }

        if (fabs(r_pid.r_error - r_pid.r_prev_error) < 3)
        {
            r_pid.r_failsafe++;
        }
        if (r_pid.r_failsafe > 100)
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
        }

        if (time_out > 0)
        {
            local_timer++;
        }

        if (local_timer > (time_out * 100))
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            break;
        }
        pros::delay(10);
    }
}

void Eclipse::Drive::move_to_point(double x, double y, bool turn_first, bool backwards, double time_out){
    this->reset_variables();
    double local_timer = 0;

    while(true){
        odom.update_position();
        r_error = backwards ? util.get_min_angle(util.get_angular_error(-x, -y, false)) * 180 / M_PI : util.get_min_angle(util.get_angular_error(x, y, false)) * 180 / M_PI;
        t_error = backwards ? -util.get_lateral_error(x, y) : util.get_lateral_error(x, y);

        if(fabs(t_error) < 5){
            t_counter++;
        } else {
            t_counter = 0;
        }
        
        r_derivative = r_error - r_prev_error;
        t_derivative = t_error - t_prev_error;

        if(r_ki != 0){ r_integral += r_error; }
        if(t_ki != 0){ t_integral += t_error; }

        if(util.sign(r_error) != util.sign(r_prev_error)){ r_integral = 0; }
        if(util.sign(t_error) != util.sign(t_prev_error)){ t_integral = 0; }

        double r_power = (r_error * r_kp) + (r_integral * r_ki) + (r_derivative * r_kd);
        double t_power = (t_error * t_kp) + (t_integral * t_ki) + (t_derivative * t_kd);

        double adjustment_factor = r_error * (M_PI / 180.0);
        t_power *= std::cos(adjustment_factor);

        if((t_power * (12000.0 / 127)) > max_translation_speed * (12000.0 / 127)){
            t_power = max_translation_speed;
        }
        if((t_power * (12000.0 / 127)) < -max_translation_speed * (12000.0 / 127)){
            t_power = -max_translation_speed;
        }
        if((r_power * (12000.0 / 127)) > max_rotation_speed * (12000.0 / 127)){
            r_power = max_rotation_speed;
        }
        if((r_power * (12000.0 / 127)) < -max_rotation_speed * (12000.0 / 127)){
            r_power = -max_rotation_speed;
        }

        if(local_timer < 20 && turn_first){
            t_power = 0;
        }

        double left_voltage = t_power - r_power;
        double right_voltage = t_power + r_power;
        left_drive.move_voltage(left_voltage * (12000.0 / 127.0));
        right_drive.move_voltage(right_voltage * (12000.0 / 127.0));

        if(fabs(t_error) < t_error_threshold){
            t_counter++;
        } else {
            t_counter = 0;
        }

        if(t_counter >= t_tolerance){
            r_power = 0;
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            local_timer = 0;
            break;
        }

        if(local_timer > time_out * 100){
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            local_timer = 0;
            break;
        }

        r_prev_error = r_error;
        t_prev_error = t_error;

        pros::delay(10);
    }
}