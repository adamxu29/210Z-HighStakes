#include "vector"

namespace Eclipse{
    class Translation_PID{
        public:
            double t_kp;
            double t_ki;
            double t_kd;
            double t_heading_kp;
            double t_error;
            double t_integral;
            double t_derivative;
            double t_prev_error;
            int t_error_threshold; 
            int t_tolerance;
            int t_counter;
            int t_failsafe;
            int t_max_speed;

            Translation_PID();

            void set_t_constants(const double kp, const double ki, const double kd, const double heading_kp);

            void reset_t_variables();

            double compute_t(double current_pos, double target);

            double get_min_angle(float angle1, float angle2);

            void translation_pid(double target, double maxSpeed, double timeOut);
    };

    class Rotation_PID{
        public:
            double r_kp;
            double r_ki;
            double r_kd;
            double r_error;
            double r_integral;
            double r_derivative;
            double r_prev_error;
            int r_error_threshold;
            int r_tolerance;
            int r_counter;
            int r_failsafe;
            int r_max_speed;

            Rotation_PID();

            void set_r_constants(const double kp, const double ki, const double kd);

            void reset_r_variables();

            double compute_r(double current_pos, double theta);

            void rotation_pid(double theta, double maxSpeed, double timeOut);
    };

    class Curve_PID{
        public:
            double c_kp;
            double c_ki;
            double c_kd;
            double c_error;
            double c_integral;
            double c_derivative;
            double c_prev_error;
            int c_error_threshold;
            int c_tolerance;
            int c_counter;
            int c_failsafe;
            int c_max_speed;
            bool c_turn_right;

            Curve_PID();

            void set_c_constants(const double kp, const double ki, const double kd);

            void reset_c_variables();

            double compute_c(double current_pos, double theta);

            void curve_pid(double theta, double maxSpeed, double timeOut, double curve_damper, bool backwards);
    };
}

