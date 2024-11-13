namespace Eclipse
{
    class Utility
    {
    public:
        void move_left_drive(int voltage);
        void move_right_drive(int voltage);
        void move_intake(int voltage);
        void move_wall_stake(int voltage);
        void move_tilter();
        void move_doinker();
        void move_intake_lift();

        double get_position();
        double get_wall_stake_position();
        double get_heading();
        void reset_position();

        bool is_reversed(int port);
        int sign(double num);
        double get_min_angle(float angle1, float angle2);
    };
}