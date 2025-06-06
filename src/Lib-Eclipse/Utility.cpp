#include "main.h"
#include <cmath>

using namespace Eclipse;

// motion

// void Utility::move_left_drive(int voltage)
// {
//     for (auto i : left_drive)
//     {
//         i.move_voltage(voltage);
//     }
// }

// void Utility::move_right_drive(int voltage)
// {
//     for (auto i : right_drive)
//     {
//         i.move_voltage(voltage);
//     }
// }

// void Utility::move_intake(int voltage)
// {
//     intake.at(0).move_voltage(voltage);

//     // use if multiple motors

//     // for(auto i : intake){
//     //     i.move_voltage(voltage);
//     // }
// }

// void Utility::move_wall_stake(int voltage)
// {
//     wall_stake.at(0).move_voltage(voltage);

//     // use if multiple motors

//     // for(auto i : wall_stake){
//     //     i.move_voltage(voltage);
//     // }
// }

// void Utility::move_tilter()
// {

//     tilting = !tilting;
//     tilter.at(0).set_value(tilting);

//     // use loop if multiple soleniods
// }

// void Utility::move_doinker()
// {
//     doinker_down = !doinker_down;
//     doinker.at(0).set_value(doinker_down);
// }

// void Utility::move_intake_lift()
// {
//     intake_up = !intake_up;
//     intake_lift.at(0).set_value(intake_up);
// }

// sensing

double Utility::get_robot_x(){ return robot_x; }
double Utility::get_robot_y(){ return robot_y; }
void Utility::set_robot_position(double x, double y){
    robot_x = x;
    robot_y = y;
}

void Eclipse::Utility::set_drive_constants(const double dt_wheel_diameter, const double dt_gear_ratio, const double dt_motor_cartridge)
{
    this->wheel_diameter = dt_wheel_diameter;
    this->gear_ratio = dt_gear_ratio;
    this->motor_cartridge = dt_motor_cartridge;
}

double Utility::get_angular_error(double x, double y, bool robot_relative)
{   
    // angular error relative to robot
    double delta_x = x - util.get_robot_x();
    double delta_y = y - util.get_robot_y();

    double delta_theta = atan2(delta_y, delta_x) - (robot_relative ? 90 + robot_theta : 0);

    // normalize angle to be between -pi and pi
    while(fabs(delta_theta) > M_PI){
        (delta_theta > 0) ? delta_theta -= 2 * M_PI : delta_theta += 2 * M_PI;
    }

    return M_PI_2 - delta_theta; // convert to standard angle
}

double Utility::get_lateral_error(double x, double y)
{
    double delta_x = x - util.get_robot_x();
    double delta_y = y - util.get_robot_y();

    return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

double Utility::get_position()
{
    // use motors that disconnect the least
    double left_position = left_drive.get_positions()[1];
    double right_position = right_drive.get_positions()[1];

    // std::cout << "left" << left_position << " right" << right_position << std::endl;
    
    return (left_position + right_position) / 2;
}

double Utility::get_drive_temp(){
    return (left_drive.get_temperatures()[0] + left_drive.get_temperatures()[1] + left_drive.get_temperatures()[2] + right_drive.get_temperatures()[0] + right_drive.get_temperatures()[1] + right_drive.get_temperatures()[2]) / 6.0;
}

void Utility::set_tpi(){
    this->circumference = this->wheel_diameter * M_PI;
    
    this->tpi = 87.86 * (3600 / this->motor_cartridge) * this->gear_ratio / this->circumference;
}

// double Utility::get_wall_stake_position(){
//     double left_position = wall_stake.get_positions()[0];
//     double right_position = wall_stake.get_positions()[1];
    
//     return (left_position + right_position) / 2;
// }

double Utility::get_heading()
{
    double heading = (imu1.get_rotation() + imu2.get_rotation()) / 2;
    // for (auto i : imus)
    // {
    //     heading += i.get_rotation();
    // }

    // return heading / imus.size();
    return util.get_min_angle(heading);
}

void Utility::reset_position()
{
    // choose most connective ports
    // for (auto i : left_drive)
    // {
    //     left_drive.at(0).set_zero_position(0);
    // }
    // for (auto i : right_drive)
    // {
    //     right_drive.at(0).set_zero_position(0);
    // }

    left_drive.set_zero_position(0);
    right_drive.set_zero_position(0);
}
// Sort blue rings on red side
void Utility::sort_red(){
    if(color.get_hue() > this->blue_min && color.get_hue() < this->blue_max){
        char buffer[300];   
        sprintf(buffer, "Hue: %.1f", color.get_hue());
        lv_label_set_text(gui.debug_line_1, buffer);

        sprintf(buffer, "Blue Detected");
        lv_label_set_text(gui.debug_line_2, buffer);

        pros::delay(sort_delay);
        driver.color_sorting = true;

        intake.move_voltage(-1000);
        pros::delay(100);
        intake.move_voltage(12000);

        driver.color_sorting = false;
        util.sorting = false;
    }
}
// Sort red rings on blue side
void Utility::sort_blue(){
    if(color.get_hue() > this->red_min && color.get_hue() < this->red_max){
        char buffer[300];
        sprintf(buffer, "Hue: %.1f", color.get_hue());
        lv_label_set_text(gui.debug_line_1, buffer);

        sprintf(buffer, "Red Detected");
        lv_label_set_text(gui.debug_line_2, buffer);

        pros::delay(sort_delay);
        driver.color_sorting = true;

        intake.move_voltage(-1000);
        pros::delay(100);
        intake.move_voltage(12000);

        driver.color_sorting = false;
        util.sorting = false;
    }
}

void Utility::stop_on_red(){
    if(color.get_hue() > this->red_min && color.get_hue() < this->red_max){
        char buffer[300];
        sprintf(buffer, "Red Ring Stopped");
        lv_label_set_text(gui.debug_line_4, buffer);
        
        intake.move_voltage(-1000);
        pros::delay(150);
        intake.brake();
    }
}

void Utility::stop_on_blue(){
    if((color.get_hue() > this->blue_min) && (color.get_hue() < this->blue_max)){
        char buffer[300];
        sprintf(buffer, "Blue Ring Stopped");
        lv_label_set_text(gui.debug_line_4, buffer);

        intake.move_voltage(-1000);
        pros::delay(150);
        intake.brake();
    }
}

// misc
bool Eclipse::Utility::is_reversed(int port)
{
    return (port < 0) ? true : false;
}

int Utility::sign(double num)
{
    return (num > 0) ? 1 : ((num < 0) ? 0 : -1);
}

double Eclipse::Utility::get_min_angle(float angle) {
    float theta = fmod(angle, 360);

    if (theta < -180) {
        theta += 360;
    } else if (theta > 180) {
        theta -= 360;
    }

    return theta;
}

double Eclipse::Utility::get_min_error(float angle1, float angle2)
{
    angle1 = fmod(angle1, 360);
    angle2 = fmod(angle2, 360);
    float error = angle2 - angle1;
    if (error > 180)
        error -= 360;
    else if (error < -180)
        error += 360;
    return error;
}