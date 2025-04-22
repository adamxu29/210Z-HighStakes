namespace Eclipse {
    class Drive {
        public:
            double t_kp;
            double t_ki;
            double t_kd;
            double t_error;
            double t_integral;
            double t_derivative;
            double t_prev_error;
            int t_error_threshold;
            int t_tolerance;
            int t_counter;
            int t_failsafe;


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

            double max_translation_speed;
            double max_rotation_speed;

            Drive();

            void set_constants(const double t_kp, const double t_ki, const double t_kd, const double r_kp, const double r_ki, const double r_kd, const double max_translation_speed, const double max_rotation_speed);
            void reset_variables();
            void turn_to_point(double x, double y, double time_out);
            void move_to_point(double x, double y, bool turn_first, bool backwards, double time_out);
    };
}