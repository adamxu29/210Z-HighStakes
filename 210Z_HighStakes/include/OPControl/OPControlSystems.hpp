namespace Eclipse{
    class OPControl{
        public:
            void drivetrain_control();
            void power_intake(int speed);
            void power_wall_stake();
            bool prime;
            void activate_tilter();
            void activate_doinker();
            void lift_intake();
            void driver_control();
    };
}
