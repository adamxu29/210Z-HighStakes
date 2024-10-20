namespace Eclipse
{
    class Utility
    {
    private:
        bool tilting = false;
        bool doinker_down = false;

    public:
        void move_left_drive(int voltage);
        void move_right_drive(int voltage);
        void move_intake(int voltage);
        void move_wall_stake(int voltage);
        void move_tilter();
        void move_doinker();

        double get_position();
        double get_heading();
        void reset_position();

        bool is_reversed(int port);
        int sign(double num);
        double get_min_angle(float angle1, float angle2);
    };
}