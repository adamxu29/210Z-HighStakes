namespace Eclipse
{
    class Utility
    {
        private:
            double wheel_diameter = 0;
            double gear_ratio = 0;
            double motor_cartridge = 0;
            double circumference = 0;
            double tpr = 0;
            double tpi = 0;

            int red_max = 16;
            int red_min = 10;
            int blue_max = 215;
            int blue_min = 210;
            int sort_delay = 105;
            
        public:
            // motion
            void move_left_drive(int voltage);
            void move_right_drive(int voltage);
            void move_intake(int voltage);
            void move_wall_stake(int voltage);
            void move_tilter();
            void move_doinker();
            void move_intake_lift();

            // odom
            double get_robot_x();
            double get_robot_y();
            void set_robot_position(double x, double y);
            void set_drive_constants(const double dt_wheel_diameter, const double dt_gear_ratio, const double dt_motor_cartridge);
            
            double get_angular_error(double x, double y, bool robot_relative);
            // sensors
            double get_position();
            void reset_position();

            void set_tpi();
            double get_tpi(){ return tpi; }

            double get_drive_temp();
            double get_wall_stake_position();
            double get_heading();
            
            // color sorting

            bool sorting = true;
            bool stop_on_color = false;

            void sort_red();
            void sort_blue();
            void stop_on_red();
            void stop_on_blue();

            // misc
            bool is_reversed(int port);
            int sign(double num);
            double get_min_angle(float angle);
            double get_min_error(float angle1, float angle2);
    };
}