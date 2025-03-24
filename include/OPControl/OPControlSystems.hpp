namespace Eclipse{
    class OPControl{
        private:
            bool clamping = false;
            bool right_doinker_down = false;
            bool left_doinker_down = false;
            bool intake_up = false;
        public:
            bool skills = false;
            bool color_sorting = false;

            void exponential_curve_accelerator();
            void drivetrain_control();
            void power_intake(int speed);
            void manual_wall_stake();
            
            bool wall_stake_on = true;
            static const int num_states = 5;
            double states[num_states] = {-13.5, 18, 32, 145, 230}; 
            int current_state = 0;
            double target = states[current_state];

            void next_state();
            void prev_state();
            void power_wall_stake();
            void control_wall_stake();
            void alliance_stake();
            void score_alliance_stake();

            void activate_clamp();
            void activate_right_doinker();
            void activate_left_doinker();
            void activate_ring_rush();
            void lift_intake();

            void driver_control();
            void skills_control();
    };
}