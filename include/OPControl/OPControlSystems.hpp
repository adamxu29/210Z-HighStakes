namespace Eclipse{
    class OPControl{
        private:
            bool clamping = false;
            bool doinker_down = false;
            bool ring_rush_down = false;
            bool intake_up = false;
            bool ratchet_used = false;
        public:
            bool skills = false;
            bool color_sorting = false;

            void exponential_curve_accelerator();
            void drivetrain_control();
            void power_intake(int speed);

            static const int num_states = 5;
            double states[num_states] = {-13.5, 15, 31, 145, 185}; 
            int current_state = 0;
            double target = states[current_state];

            void next_state();
            void prev_state();
            void power_wall_stake();
            void control_wall_stake();
            void alliance_stake();

            void manual_wall_stake(int speed);

            void activate_clamp();
            void activate_doinker();
            void activate_ring_rush();
            void lift_intake();

            void driver_control();
            void skills_control();
    };
}