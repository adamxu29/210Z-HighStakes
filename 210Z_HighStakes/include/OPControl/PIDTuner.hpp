namespace Eclipse{
    class PID_Tuner{
        public:
            double kp = 5;
            double ki = 0;
            double kd = 0;

            double kp_increment = 1.0;
            double ki_increment = 0.1;
            double kd_increment = 1.0;

            int current_constant = 0; // 0: kp 1: ki 2: k2
            int current_movement = 0; // 0: translation 1: rotation 2: curve
            
            void print_constants();
            void change_constant();
            void change_movement();
            void update_constants();
            void move();

            void driver_tuner();
    };
}

