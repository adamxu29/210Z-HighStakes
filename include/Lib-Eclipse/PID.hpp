namespace Eclipse{
    class PID
    {
        public:
            double kp;
            double ki;
            double kd;
            double error;
            double integral;
            double derivative;
            double prev_error;
            int error_threshold; 
            int tolerance;
            int failsafe_threshold;
            int failsafe_tolerance;
            int counter;
            int failsafe;
            double max_speed;

            void set_constants(const double kp, const double ki, const double kd, const double tolerance, const double error_threshold, const double failsafe_tolerance, const double failsafe_threshold, const double max_speed);

            void reset_variables();

            double compute(double current_pos, double target);

            void motor_pid(pros::Motor &motor, pros::Rotation &rotation, double target);

            void wall_stake_pid(pros::Motor_Group &motor, pros::Rotation &rotation, double target);
    };
}