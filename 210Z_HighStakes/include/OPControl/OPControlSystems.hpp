namespace Eclipse{
    class OPControl{
        public:
            void drivetrain_control();
            void power_intake(int speed);
            void prime_wall_stake();
            void power_wall_stake(); // match
            void manual_wall_stake(int speed); // skills
            bool primed;
            void activate_tilter();
            void activate_doinker();
            void lift_intake();
            void driver_control();
    };
}
