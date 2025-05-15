#include "main.h"
#include <cmath>
#include <vector>
#include <numeric>

using namespace Eclipse;

// maybe add slew

void Eclipse::Translation_PID::set_t_constants(const double kp, const double ki, const double kd, const double heading_kp)
{
    t_pid.t_kp = kp;
    t_pid.t_ki = ki;
    t_pid.t_kd = kd;
    t_pid.t_heading_kp = heading_kp;
}

void Eclipse::Rotation_PID::set_r_constants(const double kp, const double ki, const double kd)
{
    r_pid.r_kp = kp;
    r_pid.r_ki = ki;
    r_pid.r_kd = kd;
}

void Eclipse::Curve_PID::set_c_constants(const double kp, const double ki, const double kd)
{
    c_pid.c_kp = kp;
    c_pid.c_ki = ki;
    c_pid.c_kd = kd;
}

Eclipse::Translation_PID::Translation_PID()
{
    t_pid.t_tolerance = 4;
    t_pid.t_error_threshold = 5;
}

Eclipse::Rotation_PID::Rotation_PID()
{
    r_pid.r_tolerance = 4;
    r_pid.r_error_threshold = 3;
}

Eclipse::Curve_PID::Curve_PID()
{
    c_pid.c_tolerance = 4;
    c_pid.c_error_threshold = 7;
}

void Eclipse::Translation_PID::reset_t_variables()
{
    t_pid.t_error = 0;
    t_pid.t_integral = 0;
    t_pid.t_derivative = 0;
    t_pid.t_prev_error = 0;
    t_pid.t_counter = 0;
    t_pid.t_failsafe = 0;
}

void Eclipse::Rotation_PID::reset_r_variables()
{
    r_pid.r_error = 0;
    r_pid.r_integral = 0;
    r_pid.r_derivative = 0;
    r_pid.r_prev_error = 0;
    r_pid.r_counter = 0;
    r_pid.r_failsafe = 0;
}

void Eclipse::Curve_PID::reset_c_variables()
{
    c_pid.c_error = 0;
    c_pid.c_integral = 0;
    c_pid.c_derivative = 0;
    c_pid.c_prev_error = 0;
    c_pid.c_counter = 0;
    c_pid.c_failsafe = 0;
    c_pid.c_turn_right = false;
}

double Eclipse::Translation_PID::compute_t(double current_pos, double target)
{
    t_pid.t_error = target - current_pos;
    t_pid.t_derivative = t_pid.t_error - t_pid.t_prev_error;

    if (t_pid.t_ki != 0){ t_pid.t_integral += t_pid.t_error; }

    if (util.sign(t_pid.t_error) != util.sign(t_pid.t_prev_error)){ t_pid.t_integral = 0; }

    double power = (t_pid.t_error * t_pid.t_kp) + (t_pid.t_integral * t_pid.t_ki) + (t_pid.t_derivative * t_pid.t_kd);

    // std::cout << "output" << power << std::endl;

    if (power * (12000.0 / 127) > t_pid.t_max_speed * (12000.0 / 127)){ power = t_pid.t_max_speed; }
    if (power * (12000.0 / 127) < -t_pid.t_max_speed * (12000.0 / 127)){ power = -t_pid.t_max_speed; }

    t_pid.t_prev_error = t_pid.t_error;

    return power;
}


double Eclipse::Rotation_PID::compute_r(double current_pos, double theta)
{
    r_pid.r_error = util.get_min_error(current_pos, theta);
    r_pid.r_derivative = r_pid.r_error - r_pid.r_prev_error;

    if (r_pid.r_ki != 0)
    {
        r_pid.r_integral += r_pid.r_error;
    }

    if (util.sign(r_pid.r_error) != util.sign(r_pid.r_prev_error))
    {
        r_pid.r_integral = 0;
    }

    double power = (r_pid.r_error * r_pid.r_kp) + (r_pid.r_integral * r_pid.r_ki) + (r_pid.r_derivative * r_pid.r_kd);

    // std::cout << "output" << power << std::endl;

    if (power * (12000.0 / 127) > r_pid.r_max_speed * (12000.0 / 127)){ power = r_pid.r_max_speed; }
    if (power * (12000.0 / 127) < -r_pid.r_max_speed * (12000.0 / 127)){ power = -r_pid.r_max_speed;}

    r_pid.r_prev_error = r_pid.r_error;

    return power;
}

double Eclipse::Curve_PID::compute_c(double current_pos, double theta)
{
    c_pid.c_error = util.get_min_error(current_pos, theta);
    c_pid.c_derivative = c_pid.c_error - c_pid.c_prev_error;

    if (c_pid.c_ki != 0){ c_pid.c_integral += c_pid.c_error; }

    if (util.sign(c_pid.c_error) != util.sign(c_pid.c_prev_error)){ c_pid.c_integral = 0; }

    double power = (c_pid.c_error * c_pid.c_kp) + (c_pid.c_integral * c_pid.c_ki) + (c_pid.c_derivative * c_pid.c_kd);

    // std::cout << "error" << c_pid.c_error << std::endl;

    if (power * (12000.0 / 127) > c_pid.c_max_speed * (12000.0 / 127)){
        // std::cout << "max: " << c_pid.c_max_speed << std::endl;
        power = c_pid.c_max_speed;
         
    }
    if (power * (12000.0 / 127) < -c_pid.c_max_speed * (12000.0 / 127)){ power = -c_pid.c_max_speed; }
    
    // std::cout << "power" << power << std::endl;
    c_pid.c_prev_error = c_pid.c_error;

    return power;
}

void Eclipse::Translation_PID::translation_pid(double target, double max_speed, double time_out)
{
    util.reset_position();
    t_pid.reset_t_variables();

    double theta = util.get_heading();
    target = target *= 3;
    t_pid.t_max_speed = max_speed;
    double local_timer = 0;

    while (true)
    {
        odom.update_position();
        double current_position = util.get_position() * 3 / util.get_tpi();
 
        double voltage = t_pid.compute_t(current_position, target);
        double heading_correction = util.get_min_error(util.get_heading(), theta) * t_pid.t_heading_kp;

        // std::cout << "average pos" << current_position << std::endl;
        // std::cout << "output" << voltage << std::endl;
        // std::cout << "error" << target - current_position << std::endl;

        left_drive.move_voltage((voltage * (12000.0 / 127.0)) + heading_correction);
        right_drive.move_voltage((voltage * (12000.0 / 127.0)) - heading_correction);

        if (fabs(t_pid.t_error) < t_pid.t_error_threshold)
        {
            t_pid.t_counter++;
        }
        else
        {
            t_pid.t_counter = 0;
        }

        if (t_pid.t_counter >= t_pid.t_tolerance)
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            break;
        }

        if (fabs(t_pid.t_derivative) < 5 && time_out == -1)
        {
            t_pid.t_failsafe++;
        }

        if (t_pid.t_failsafe > 50)
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            break;
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

        // left_drive.move_voltage((voltage * (12000.0 / 127.0)) + heading_correction);
        // right_drive.move_voltage((voltage * (12000.0 / 127.0)) - heading_correction);

        pros::delay(10);
    }
}

void Eclipse::Rotation_PID::rotation_pid(double theta, double max_speed, double time_out)
{
    r_pid.reset_r_variables();

    double local_timer = 0;
    r_pid.r_max_speed = max_speed;

    while (true)
    {
        // odom.update_position();
        double current_position = util.get_heading();
        double voltage = r_pid.compute_r(current_position, theta);

        // char buffer[300];
        // sprintf(buffer, "rotation pid: %.2f", this->r_error);
        // lv_label_set_text(gui.debug_line_1, buffer);

        // std::cout << "average pos" << current_position << std::endl;
        // std::cout << "error" << r_pid.r_error << std::endl;

        left_drive.move_voltage(voltage * (12000.0 / 127.0));
        right_drive.move_voltage(-voltage * (12000.0 / 127.0));
        
        if (fabs(r_pid.r_error) < r_pid.r_error_threshold)
        {
             r_pid.r_counter++;
        }
         else
        {
             r_pid.r_counter = 0;
        }

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

void Eclipse::Curve_PID::curve_pid(double theta, double max_speed, double time_out, double curve_damper, bool backwards)
{
    c_pid.reset_c_variables();

    double local_timer = 0;
    c_pid.c_max_speed = max_speed;
    c_turn_right = false;

    while (true)
    {   
        odom.update_position();
        double current_position = util.get_heading();
        double voltage = c_pid.compute_c(current_position, theta);

        if (c_pid.c_error > 0){
            c_pid.c_turn_right = true;
        }

        if(!c_pid.c_turn_right && !backwards){
            left_drive.move_voltage(abs(voltage) * (12000.0 / 127.0) * curve_damper);
            right_drive.move_voltage(abs(voltage) * (12000.0 / 127.0));
        }
        else if(!c_pid.c_turn_right && backwards){
            left_drive.move_voltage(voltage * (12000.0 / 127.0));
            right_drive.move_voltage(voltage * (12000.0 / 127.0) * curve_damper);
        }
        else if(c_pid.c_turn_right && !backwards){
            left_drive.move_voltage(voltage * (12000.0 / 127.0));
            right_drive.move_voltage(voltage * (12000.0 / 127.0) * curve_damper);
        }
        else if(c_pid.c_turn_right && backwards){
            left_drive.move_voltage(-voltage * (12000.0 / 127.0) * curve_damper);
            right_drive.move_voltage(-voltage * (12000.0 / 127.0));
        }

        if (fabs(c_pid.c_error) < c_pid.c_error_threshold)
        {
            r_pid.r_counter++;
        }
        else
        {
            r_pid.r_counter = 0;
        }

        if (r_pid.r_counter >= r_pid.r_tolerance)
        {
            left_drive.move_voltage(0);
            right_drive.move_voltage(0);
            break;
        }

        if (fabs(r_pid.r_error - r_pid.r_prev_error) < 0.1)
        {
            r_pid.r_failsafe++;
        }

        if (r_pid.r_failsafe > 300)
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