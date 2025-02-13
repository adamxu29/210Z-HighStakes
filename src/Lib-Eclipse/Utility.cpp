#include "main.h"

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

// double Utility::get_robot_x(){ return robot_x; }
// double Utility::get_robot_y(){ return robot_y; }
// void Utility::set_robot_position(double x, double y){
//     robot_x = x;
//     robot_y = y;
// }

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
    return heading;
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

double Eclipse::Utility::get_min_angle(float angle1, float angle2)
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