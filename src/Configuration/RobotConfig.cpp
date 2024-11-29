// #include "main.h"
// #include "vector"

// using namespace Eclipse;

// // add more soleniods if needed
// std::vector<pros::Motor> left_drive;
// std::vector<pros::Motor> right_drive;
// std::vector<pros::Motor> intake;
// std::vector<pros::Motor> wall_stake;
// std::vector<pros::ADIDigitalOut> tilter;
// std::vector<pros::ADIDigitalOut> doinker;
// std::vector<pros::ADIDigitalOut> intake_lift;
// std::vector<pros::IMU> imus;

// Eclipse::RobotConfig::RobotConfig(std::vector<int> left_ports, std::vector<int> right_ports, std::vector<int> intake_ports,
//                          std::vector<int> wall_stake_ports, std::vector<char> tilter_ports, std::vector<char> doinker_ports,
//                          std::vector<char> intake_lift_ports,  std::vector<int> imu_ports)
// {
//     for (auto i : left_ports)
//     {
//         pros::Motor temp(abs(i), util.is_reversed(i));
//         left_drive.push_back(temp);
//     }

//     for (auto i : right_ports)
//     {
//         pros::Motor temp(abs(i), util.is_reversed(i));
//         right_drive.push_back(temp);
//     }

//     for (auto i : intake_ports)
//     {
//         pros::Motor temp(abs(i), util.is_reversed(i));
//         intake.push_back(temp);
//     }

//     for (auto i : wall_stake_ports)
//     {
//         pros::Motor temp(abs(i), util.is_reversed(i));
//         wall_stake.push_back(temp);
//     }

//     for (auto i : tilter_ports)
//     {
//         pros::ADIDigitalOut temp(i);
//         tilter.push_back(temp);
//     }

//     for (auto i : imu_ports)
//     {
//         pros::IMU temp(i);
//         imus.push_back(temp);
//     }

//     for (auto i : doinker_ports)
//     {
//         pros::ADIDigitalOut temp(i);
//         doinker.push_back(temp);
//     }
// }