#include "main.h"
#include <cmath>
#include <vector>
#include <numeric>

using namespace Eclipse;

// maybe add slew

void Eclipse::Translation_PID::set_drive_constants(const double n_wheel_diameter, const double n_gear_ratio, const double n_motor_cartridge)
{
    wheel_diameter = n_wheel_diameter;
    gear_ratio = n_gear_ratio;
    motor_cartridge = n_motor_cartridge;
}

void Eclipse::Translation_PID::set_t_constants(const double kp, const double ki, const double kd, const double heading_kp)
{
    t_kp = kp;
    t_ki = ki;
    t_kd = kd;
    t_heading_kp = heading_kp;
}

void Eclipse::Rotation_PID::set_r_constants(const double kp, const double ki, const double kd)
{
    r_kp = kp;
    r_ki = ki;
    r_kd = kd;
}

void Eclipse::Curve_PID::set_c_constants(const double kp, const double ki, const double kd)
{
    c_kp = kp;
    c_ki = ki;
    c_kd = kd;
}

Eclipse::Translation_PID::Translation_PID()
{
    // tune later
    t_tolerance = 0;
    t_error_threshold = 0;
}

Eclipse::Rotation_PID::Rotation_PID()
{
    // tune later
    r_tolerance = 0;
    r_error_threshold = 0;
}

Eclipse::Curve_PID::Curve_PID()
{
    // tune later
    c_tolerance = 0;
    c_error_threshold = 0;
}

void Eclipse::Translation_PID::reset_t_variables()
{
    t_error = 0;
    t_integral = 0;
    t_derivative = 0;
    t_prev_error = 0;
    t_counter = 0;
    t_failsafe = 0;
}

void Eclipse::Rotation_PID::reset_r_variables()
{
    r_error = 0;
    r_integral = 0;
    r_derivative = 0;
    r_prev_error = 0;
    r_counter = 0;
    r_failsafe = 0;
}

void Eclipse::Curve_PID::reset_c_variables()
{
    c_error = 0;
    c_integral = 0;
    c_derivative = 0;
    c_prev_error = 0;
    c_counter = 0;
    c_failsafe = 0;
    c_turn_right = false;
}

double Eclipse::Translation_PID::compute_t(double current_pos, double target)
{
    t_pid.t_error = target - current_pos;
    t_pid.t_derivative = t_pid.t_error - t_pid.t_prev_error;

    if (t_pid.t_ki != 0){ t_pid.t_integral += t_pid.t_error; }

    if (util.sign(t_pid.t_error) != util.sign(t_pid.t_prev_error)){ t_pid.t_integral = 0; }

    double power = (t_pid.t_error * t_pid.t_kp) + (t_pid.t_integral * t_pid.t_ki) + (t_pid.t_derivative * t_pid.t_kd);

    if (power * (12000.0 / 127) > t_pid.t_max_speed * (12000.0 / 127)){ power = t_pid.t_max_speed; }
    if (power * (12000.0 / 127) < t_pid.t_max_speed * (12000.0 / 127)){ power = t_pid.t_max_speed; }

    t_pid.t_prev_error = t_pid.t_error;

    return power;
}


double Eclipse::Rotation_PID::compute_r(double current_pos, double theta)
{
    r_pid.r_error = theta - util.get_min_angle(current_pos, theta);
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
    if (power * (12000.0 / 127) > r_pid.r_max_speed * (12000.0 / 127))
    {
        power = r_pid.r_max_speed;
    }
    if (power * (12000.0 / 127) < -r_pid.r_max_speed * (12000.0 / 127))
    {
        power = -r_pid.r_max_speed;
    }

    r_pid.r_prev_error = r_pid.r_error;

    return power;
}

double Eclipse::Curve_PID::compute_c(double current_pos, double theta)
{
    c_pid.c_error = theta - util.get_min_angle(current_pos, theta);
    c_pid.c_derivative = c_pid.c_error - c_pid.c_prev_error;

    if (c_pid.c_ki != 0)
    {
        c_pid.c_integral += c_pid.c_error;
    }

    if (util.sign(c_pid.c_error) != util.sign(c_pid.c_prev_error))
    {
        c_pid.c_integral = 0;
    }

    double power = (c_pid.c_error * c_pid.c_kp) + (c_pid.c_integral * c_pid.c_ki) + (c_pid.c_derivative * c_pid.c_kd);
    if (power * (12000.0 / 127) > c_pid.c_max_speed * (12000.0 / 127))
    {
        power = c_pid.c_max_speed;
    }
    if (power * (12000.0 / 127) < -c_pid.c_max_speed * (12000.0 / 127))
    {
        power = -c_pid.c_max_speed;
    }

    c_pid.c_prev_error = c_pid.c_error;

    return power;
}

void Eclipse::Translation_PID::translation_pid(double target, double maxSpeed, double timeOut)
{
    util.reset_position();
    t_pid.reset_t_variables();

    double theta = util.get_heading();
    double target_position = target;

    t_pid.circumference = wheel_diameter * M_PI;
    t_pid.t_max_speed = maxSpeed;
    t_pid.circumference = wheel_diameter * M_PI;
    t_pid.tpr = (50.0 * (3600.0 / t_pid.motor_cartridge) * t_pid.gear_ratio);
    t_pid.tpi = (t_pid.tpr / t_pid.circumference);
    target *= t_pid.tpi;

    double local_timer = 0;

    while (true)
    {
        double current_position = util.get_position();
        double voltage = t_pid.compute_t(current_position, target);
        double heading_correction = util.get_min_angle(target_position, theta * t_pid.t_heading_kp);

        util.move_left_drive((voltage * (12000.0 / 127.0)) + heading_correction);
        util.move_right_drive((voltage * (12000.0 / 127.0)) - heading_correction);

        if (fabs(t_pid.t_error) > t_pid.t_error_threshold)
        {
            t_pid.t_counter++;
        }
        else
        {
            t_pid.t_counter = 0;
        }

        if (t_pid.t_counter >= t_pid.t_tolerance)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        if (fabs(t_pid.t_derivative) < 5 && timeOut == 1)
        {
            t_pid.t_failsafe++;
        }

        if (t_pid.t_failsafe > 50)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        if (timeOut > 0)
        {
            local_timer++;
        }

        if (local_timer > (timeOut * 100))
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }
        pros::delay(10);
    }
}

void Eclipse::Rotation_PID::rotation_pid(double theta, double maxSpeed, double timeOut)
{
    util.reset_position();
    r_pid.reset_r_variables();

    double target_position = theta;
    double local_timer = 0;

    while (true)
    {
        double current_position = util.get_heading();
        double voltage = r_pid.compute_r(current_position, theta);
        r_pid.r_max_speed = maxSpeed;

        util.move_left_drive(voltage * (12000.0 / 127.0));
        util.move_right_drive(-voltage * (12000.0 / 127.0));
        
        if (fabs(r_pid.r_error) > r_pid.r_error_threshold)
        {
            r_pid.r_counter++;
        }
        else
        {
            r_pid.r_counter = 0;
        }

        if (r_pid.r_counter >= r_pid.r_tolerance)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        if (fabs(r_pid.r_error - r_pid.r_prev_error) < 3)
        {
            r_pid.r_failsafe++;
        }
        if (r_pid.r_failsafe > 100)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
        }

        if (timeOut > 0)
        {
            local_timer++;
        }

        if (local_timer > (timeOut * 100))
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        pros::delay(10);
    }
}

void Eclipse::Curve_PID::curve_pid(double theta, double maxSpeed, double timeOut, double curve_damper, bool backwards)
{
    util.reset_position();
    c_pid.reset_c_variables();

    double target_position = theta;
    double local_timer = 0;
    r_pid.r_max_speed = maxSpeed;

    while (true)
    {
        double current_position = util.get_heading();
        double voltage = c_pid.compute_c(current_position, theta);

        if (c_pid.c_error < 0){
            c_pid.c_turn_right = true;
        }

        if(!c_pid.c_turn_right && !backwards){
            util.move_left_drive(abs(voltage) * (12000.0 / 127.0) * curve_damper);
            util.move_right_drive(abs(voltage) * (12000.0 / 127.0));
        }
        else if(!c_pid.c_turn_right && backwards){
            util.move_left_drive(voltage * (12000.0 / 127.0));
            util.move_right_drive(voltage * (12000.0 / 127.0) * curve_damper);
        }
        else if(c_pid.c_turn_right && !backwards){
            util.move_left_drive(voltage * (12000.0 / 127.0));
            util.move_right_drive(voltage * (12000.0 / 127.0) * curve_damper);
        }
        else if(c_pid.c_turn_right && backwards){
            util.move_left_drive(-voltage * (12000.0 / 127.0) * curve_damper);
            util.move_right_drive(-voltage * (12000.0 / 127.0));
        }

        if (fabs(c_pid.c_error) > c_pid.c_error_threshold)
        {
            r_pid.r_counter++;
        }
        else
        {
            r_pid.r_counter = 0;
        }

        if (r_pid.r_counter >= r_pid.r_tolerance)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        if (fabs(r_pid.r_error - r_pid.r_prev_error) < 0.1)
        {
            r_pid.r_failsafe++;
        }

        if (r_pid.r_failsafe > 300)
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
        }

        if (timeOut > 0)
        {
            local_timer++;
        }

        if (local_timer > (timeOut * 100))
        {
            util.move_left_drive(0);
            util.move_right_drive(0);
            break;
        }

        pros::delay(10);
    }
}