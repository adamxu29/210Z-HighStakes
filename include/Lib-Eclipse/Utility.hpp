namespace Eclipse
{
    class Utility
    {
        private:

            
        public:
            // motion
            void move_left_drive(int voltage);
            void move_right_drive(int voltage);
            void move_intake(int voltage);
            void move_wall_stake(int voltage);
            void move_tilter();
            void move_doinker();
            void move_intake_lift();

            // sensing
            double get_robot_x();
            double get_robot_y();
            void set_robot_position(double x, double y);

            double get_position();
            double get_drive_temp();
            double get_wall_stake_position();
            double get_heading();

            int red_max = 20;
            int red_min = 0;
            int blue_max = 225;
            int blue_min = 190;
            int sort_delay = 110;

            bool sorting = true;
            bool stop_on_color = false;

            void sort_red();
            void sort_blue();
            void stop_on_red();
            void stop_on_blue();

            void reset_position();

            // misc
            bool is_reversed(int port);
            int sign(double num);
            double get_min_angle(float angle1, float angle2);
    };
}