#include "main.h"
#include "cmath"

using namespace Eclipse;

// global position variables
double robot_x = 0;
double robot_y = 0;
double robot_theta;

// helper functions
void Odom::set_horizontal_tracker_specs(double diameter, double offset){
    odom.horizontal_wheel_diameter = diameter;
    odom.horizontal_wheel_offset = offset;
}

void Odom::set_vertical_tracker_specs(double diameter, double offset){
    odom.vertical_wheel_diameter = diameter;
    odom.vertical_wheel_offset = offset;
}

float Odom::get_horizontal_displacement(){
    return  (((float)horizontal_rotation_sensor.get_position() / 100) * odom.horizontal_wheel_diameter * M_PI / 360);
}

float Odom::get_left_displacement(){
    return (float) (left_drive.get_positions()[2]) * odom.vertical_wheel_diameter * M_PI / 360;
}

float Odom::get_right_displacement(){
    return (float) (right_drive.get_positions()[2] * odom.vertical_wheel_diameter * M_PI / 360);
}

double heading;

double prev_horizontal_displacement = 0;
double prev_vertical_displacement = 0;
double prev_heading = 0;

// Pilons odom implementation: https://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
void Odom::update_position(){
    double horizontal_pos = get_horizontal_displacement();
    double vertical_pos = get_right_displacement();

    double delta_horizontal = horizontal_pos - prev_horizontal_displacement;
    double delta_vertical = vertical_pos - prev_vertical_displacement;

    heading = -util.get_min_angle(util.get_heading()) * M_PI / 180.0; // convert to radians
    double delta_heading = heading - prev_heading;
    
    prev_horizontal_displacement = horizontal_pos;
    prev_vertical_displacement = vertical_pos;

    double local_x;
    double local_y;

    if(delta_heading == 0){
        local_x = delta_horizontal;
        local_y = delta_vertical;
    }
    else{
        local_x = (2 * sin(delta_heading / 2) * (delta_horizontal / delta_heading + horizontal_wheel_offset));
        local_y = (2 * sin(delta_heading / 2) * (delta_vertical / delta_heading + vertical_wheel_offset));
    }

    double avg_heading = prev_heading + (delta_heading / 2);
    prev_heading = heading;

    odom.x += local_x * cos(avg_heading) - local_y * sin(avg_heading);
    odom.y += local_x * sin(avg_heading) + local_y * cos(avg_heading);

    util.set_robot_position(odom.x, odom.y);

    robot_theta = heading;

    gui.update_sensors();
    gui.update_temps();
    gui.update_match_checklist();
}