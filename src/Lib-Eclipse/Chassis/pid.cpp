#include "main.h"
#include <cmath>
#include <vector>
#include <numeric>

extern void resetPosition()
{
	left_drive.set_zero_position(0);
	right_drive.set_zero_position(0);
}

int sign(double error)
{
	if (error >= 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

double turn_kP = 2.5; // 5
double turn_kI = 0;
double turn_kD = 20; // 17

double turn_error;
int turn_errorThreshold = 7.5;
double turn_prevError;
double turn_integral;
double turn_derivative;

double turn_tolerance = 5;
double turn_maxSpeed = 90;

void turn_pid(double theta)
{
	turn_prevError = 0;
	turn_integral = 0;
	turn_derivative = 0;

	int counter = 0;

	int failSafeCounter = 0;

	while (true)
	{
		double pos = (imu1.get_rotation() + imu2.get_rotation()) / 2;
		
		turn_error = theta - pos;

		turn_integral += turn_error;
		if (sign(turn_error) != sign(turn_prevError))
		{
			turn_integral = 0;
		}

		turn_derivative = turn_error - turn_prevError;
		turn_prevError = turn_error;

		if (fabs(turn_error) < turn_errorThreshold)
		{
			counter++;
		}
		if (counter > turn_tolerance)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}
		double power = turn_error * turn_kP + turn_integral * turn_kI + turn_derivative * turn_kD;

		if (power * (12000.0 / 127) > turn_maxSpeed * (12000.0 / 127))
		{
			power = turn_maxSpeed;
		}
		if (power * (12000.0 / 127) < -turn_maxSpeed * (12000.0 / 127))
		{
			power = -turn_maxSpeed;
		}

		if (fabs(turn_derivative) < 5)
		{
			failSafeCounter++;
		}
		if (failSafeCounter > 300)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}

		left_drive.move_voltage(power * (12000.0 / 127));
		right_drive.move_voltage(power * (12000.0 / 127) * (-1));
		pros::delay(10);
	}
}

double curve_kP = 2.5; //2.5
double curve_kI = 0;
double curve_kD = 23.5; // 8

double curve_error = 0;
int curve_errorThreshold = 7.5;
double curve_prevError = 0;
double curve_integral = 0;
double curve_derivative = 0;

double curve_tolerance = 10;
double curve_maxSpeed = 80;

void curve_pid(double theta, double timeout, double curve_damper, bool backwards)
{
	int counter = 0;

	int failSafeCounter = 0;
	double localtimer = 0;
	bool turn_right = false;

	while (true)
	{
		double pos = (imu1.get_rotation() + imu2.get_rotation()) / 2;
		curve_error = theta - pos;

		curve_integral += curve_error;
		if (sign(curve_error) != sign(curve_prevError))
		{
			curve_integral = 0;
		}

		curve_derivative = curve_error - curve_prevError;
		curve_prevError = curve_error;

		if (fabs(curve_error) < curve_errorThreshold)
		{
			counter++;
		}
		if (counter > curve_tolerance)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}
		double power = curve_error * curve_kP + curve_integral * curve_kI + curve_derivative * curve_kD;

		if (power * (12000.0 / 127) > curve_maxSpeed * (12000.0 / 127))
		{
			power = curve_maxSpeed;
		}
		if (power * (12000.0 / 127) < -curve_maxSpeed * (12000.0 / 127))
		{
			power = -curve_maxSpeed;
		}

		if (fabs(curve_derivative) < 5)
		{
			failSafeCounter++;
		}
		if (failSafeCounter > 300)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}

		if(timeout > 0){
			localtimer++;
		}
		if(localtimer > (timeout * 100)){
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
		}

		if(curve_error > 0){
			turn_right = true;
		}

		if(turn_right == true && backwards == false){
			left_drive.move_voltage(power * (12000.0 / 127));
			right_drive.move_voltage(power * (12000.0 / 127) * curve_damper);
		}
		else if(turn_right == false && backwards == false){
			left_drive.move_voltage(abs(power) * (12000.0 / 127) * curve_damper);
			right_drive.move_voltage(abs(power) * (12000.0 / 127));
		}
		if(turn_right == true && backwards == true){
			left_drive.move_voltage(-power * (12000.0 / 127) * curve_damper);
			right_drive.move_voltage(-power * (12000.0 / 127));
		}
		else if( turn_right == false && backwards == true){
			left_drive.move_voltage(power * (12000.0 / 127));
			right_drive.move_voltage(power * (12000.0 / 127) * curve_damper);
		}

		pros::delay(10);
	}
}

extern double vector_average(const std::vector<double> &v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double kP = 5.5; //5.5
double kI = 0;
double kD = 13; // 10-13

double error = 0;
int errorThreshold = 90; //15
double prevError = 0;
double integral = 0;
double derivative = 0;

double tolerance = 3;
double maxSpeed = 90;
double circumference = 2.75 * M_PI;

void drive_pid(double target)
{
	resetPosition();
	integral = 0;
	derivative = 0;
	prevError = 0;
	error = 0;

	double tpr = (69 * (3600 / 600) * 0.8); // tune error_thresh
	double tpi = tpr / circumference;
	target *= tpi;

	int counter = 0;

	int failSafeCounter = 0;

	while (true)
	{
		double pos = (left_drive.get_positions()[0] + left_drive.get_positions()[1] + right_drive.get_positions()[0] + right_drive.get_positions()[1]) / 4;
		error = target - pos;

		derivative = error - prevError;

		integral += error;

		if (sign(error) != sign(prevError))
		{
			integral = 0;
		}

		if (fabs(error) < errorThreshold)
		{
			counter++;
		}
		else
		{
			counter = 0;
		}
		if (counter > tolerance)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}

		double power = error * kP + integral * kI + derivative * kD;
		
		// std::cout << "average pos" << pos << std::endl;
        // std::cout << "output" << power << std::endl;
        // std::cout << "error" << target - pos << std::endl;

		if (power * (12000.0 / 127) > maxSpeed * (12000.0 / 127))
		{
			power = maxSpeed;
		}
		if (power * (12000.0 / 127) < -maxSpeed * (12000.0 / 127))
		{
			power = -maxSpeed;
		}

		if (fabs(derivative) < 5)
		{
			failSafeCounter++;
		}
		if (failSafeCounter > 150)
		{
			left_drive.move_voltage(0);
			right_drive.move_voltage(0);
			break;
		}

		left_drive.move_voltage(power * (12000.0 / 127));
		right_drive.move_voltage(power * (12000.0 / 127));

		prevError = error;

		pros::delay(10);
	}
}