namespace Eclipse{
    class OPControl{
        public:
            void drivetrain_control();
            void power_intake(int speed);
            void prime_wall_stake();
            void power_wall_stake(); // match
            void manual_wall_stake(int speed); // skills
            bool primed;
            void activate_clamp();
            void activate_doinker();
            void lift_intake();
            void release_ratched();

            void activate_clamp_skills();
            void activate_doinker_skills();
            void lift_intake_skills();
            void prime_wall_stake_skills();
            void power_wall_stake_skills();

            void driver_control();
            void skills_control();
    };
}
