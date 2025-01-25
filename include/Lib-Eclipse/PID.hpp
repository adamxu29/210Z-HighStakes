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
            int failsfe_threshold;
            int failsafe_tolerance;
            int counter;
            int failsafe;
            int max_speed;

            PID();

            void set_constants(const double kp, const double ki, const double kd, const double tolerance, const double error_threshold, const double failsafe_tolerance, const double failsafe_threshold, const double max_speed);

            void reset_variables();

            double compute(double current_pos, double target);

            void motor_pid(pros::Motor &motor, pros::Rotation &rotation, double target, double maxSpeed, double timeOut);
    };
}