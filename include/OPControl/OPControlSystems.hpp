namespace Eclipse{
    class OPControl{
        private:
            bool clamping = false;
            bool right_doinker_down = false;
            bool left_doinker_down = false;
            bool climb_clamping = false;
            bool wall_stake_boost_activated = false;

            bool loading_lb = false;
        public:
            bool endgame = false;
            bool skills = false;
            bool color_sorting = false;

            void exponential_curve_accelerator();
            void drivetrain_control();
            void power_intake(int speed);
            void manual_wall_stake();

            bool wall_stake_on = true;
            static const int num_states = 4;
            double states[num_states] = {6, -19.4, -55, -143}; 
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
            void activate_climb_claw_pto();
            void activate_climb_release();
            void activate_wall_stake_boost();

            void driver_control();
            void skills_control();
    };
}