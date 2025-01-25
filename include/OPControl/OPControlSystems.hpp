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

            void exponential_curve_accelerator();
            void drivetrain_control();
            void power_intake(int speed);
            void prime_wall_stake();
            void power_wall_stake();
            void manual_wall_stake(int speed);
            bool primed;
            void activate_clamp();
            void activate_doinker();
            void activate_ring_rush();
            void lift_intake();
            void ratchet_mech();

            void driver_control();
            void skills_control();
    };
}
