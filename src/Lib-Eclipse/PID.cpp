#include "main.h"
#include "cmath"

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

    while(true){
        double current_position = rotation.get_position() / 100.0;
        double voltage = compute(current_position, target);
        motor.move_voltage(voltage * (12000.0 / 127.0));
        
        if(fabs(this->error) < this->error_threshold){
            this->counter++;
        }
        else{
            this->counter = 0;
        }

        if(this->counter > this->tolerance){ 
            motor.brake();
            std::cout << "PID loop completed" << std::endl;
            break;
        }

        if(fabs(this->derivative) > this->failsafe_threshold){
            this->failsafe++;
        }

        if(this->failsafe > this->failsafe_tolerance){
            motor.brake();
            std::cout << "failsafe" << std::endl;
            break;
        }
        pros::delay(10);
    }
}

void Eclipse::PID::wall_stake_pid(pros::Motor_Group &motor, pros::Rotation &rotation, double target){
    double current_position = wall_stake_rotation_sensor.get_position() / 100.0;
    double voltage = this->compute(current_position, driver.target);
    wall_stake.move_voltage(voltage * (12000.0 / 127.0));

    // Check if the target has been reached
    if (fabs(this->error) < this->error_threshold) {
        this->counter++;
    } else {
        this->counter = 0;
    }

    // If the target is reached for the required tolerance duration
    if (this->counter > this->tolerance) {
        wall_stake.brake();
        this->reset_variables();
    }

    // Handle failsafe logic
    if (fabs(this->derivative) > this->failsafe_threshold) {
        this->failsafe++;
    }

    if (this->failsafe > this->failsafe_tolerance) {
        driver.current_state = 0;
        driver.target = driver.states[driver.current_state];
        this->reset_variables();
    }
}