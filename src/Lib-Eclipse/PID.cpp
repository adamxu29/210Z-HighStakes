#include "main.h"

using namespace Eclipse;

void Eclipse::PID::set_constants(const double kp, const double ki, const double kd, const double tolerance, const double error_threshold, const double failsafe_tolerance, const double failsafe_threshold, const double max_speed)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->tolerance = tolerance;
    this->error_threshold = error_threshold;
    this->failsafe_tolerance = failsafe_tolerance;
    this->failsafe_threshold = failsafe_threshold;
    this->max_speed = max_speed;
}

void Eclipse::PID::reset_variables()
{
    this->error = 0;
    this->integral = 0;
    this->derivative = 0;
    this->prev_error = 0;
    this->counter = 0;
    this->failsafe = 0;
}

double Eclipse::PID::compute(double current_pos, double target)
{
    this->error = target - current_pos;
    
    this->derivative = this->error - this->prev_error;

    if (this->ki != 0){
        this->integral += this->error;
    }

    if (util.sign(this->error) != util.sign(this->prev_error)){
        this->integral = 0;
    }

    double power = (this->error * this->kp) + (this->integral * this->ki) + (this->derivative * this->kd);

    if (power * (12000.0 / 127) > this->max_speed * (12000.0 / 127)){
        power = this->max_speed;

    }
    if (power * (12000.0 / 127) < -this->max_speed * (12000.0 / 127)){
        power = -this->max_speed;
    }

    this->prev_error = this->error;
    return power;
}

void Eclipse::PID::motor_pid(pros::Motor &motor, pros::Rotation &rotation, double target){
    reset_variables();

    double local_timer = 0;
    this->max_speed = maxSpeed;

    while(true){
        double current_position;
        &rotation == nullptr ? current_position = motor.get_position() : current_position = rotation.get_position() / 100.0;

        double voltage = compute(current_position, target);

        motor.move_voltage(voltage);

        fabs(this->error) < this->error_threshold ? this->counter++; : this->counter = 0;

        if(this->counter >= this->tolerance){ 
            motor.move_voltage(0);
            break;
        }

        fabs(this->derivative) < this->failsafe_threshold ? this->failsafe++;

        if(this->failsafe > this->failsafe_tolerance){
            motor.move_voltage(0);
            break;
        }
    }
}