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

double Utility::get_position()
{
    // use motors that disconnect the least
    double left_position = left_drive.get_positions()[1];
    double right_position = right_drive.get_positions()[1];

    // std::cout << "left" << left_position << " right" << right_position << std::endl;
    
    return (left_position + right_position) / 2;
}

double Utility::get_wall_stake_position(){
    double left_position = wall_stake.get_positions()[0];
    double right_position = wall_stake.get_positions()[1];
    
    return (left_position + right_position) / 2;
}

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