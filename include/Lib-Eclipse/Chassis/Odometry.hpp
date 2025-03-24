extern double robot_x;
extern double robot_y;
extern double robot_theta;

namespace Eclipse{
    class Odom{
        public:

            float horizontal_wheel_diameter;
            float horizontal_wheel_offset;
            float vertical_wheel_diameter;
            float vertical_wheel_offset;

            void set_horizontal_tracker_specs(double diameter, double offset);
            void set_vertical_tracker_specs(double diameter, double offset);

            float get_horizontal_displacement();
            float get_left_displacement();
            float get_right_displacement();

            double x = 0;
            double y = 0;


            void update_position();
    };
}