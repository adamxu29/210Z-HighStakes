#include "display/lvgl.h"

namespace Eclipse{
    class GUI{
        public:
            // Define all objects
            lv_obj_t *home_screen, *team_logo, *auton_home_btn, *sensors_home_btn, *debug_home_btn;
            lv_obj_t *auton_screen, *auton_title, *alliance_color, *red_btn, *blue_btn, *autonomous_path, *rush_awp, *safe_awp,
            *goal_side_rush, *ring_side_rush, *auton_return_home;
            lv_obj_t *sensor_screen, *sensor_title, *position_readings, *drivetrain_encoders, *drivetrain_temp,
            *motor_temp, *sensor_return_home;
            lv_obj_t *debug_screen, *debug_title, *debug_line_1, *debug_line_2, *debug_line_3, *debug_line_4, *debug_line_5,
            *debug_line_6, *debug_line_7, *debug_line_8, *debug_line_9, *debug_return_home;

            // Define all styles
            static lv_style_t style_screen_bg;

            static lv_style_t style_title; static lv_style_t style_text;
            
            static lv_style_t style_button_base;

            static lv_style_t style_blue_btn;
            static lv_style_t style_pressed_blue_btn;

            static lv_style_t style_red_btn;
            static lv_style_t style_pressed_red_btn;

            static lv_style_t style_purple_btn;
            static lv_style_t style_pressed_purple_btn;

            static lv_style_t style_home_icon;

            static lv_res_t return_home_click(lv_obj_t *btn);
            static lv_res_t auton_selector_click(lv_obj_t *btn);
            static lv_res_t sensors_click(lv_obj_t *btn);
            static lv_res_t debug_terminal_click(lv_obj_t *btn);

            lv_obj_t *current_selected_color = nullptr;
            static lv_res_t alliance_color_callback(lv_obj_t *btn);

            lv_obj_t *current_selected_path = nullptr;
            static lv_res_t autonomous_path_callback(lv_obj_t *btn);
                    
            void initialize_styles();
            void initialize_objects();
            void display_home();
            void display_auton_selector();
            void display_sensors();
            void display_debug_terminal();
            void return_to_home();
    };
} 

extern Eclipse::GUI gui;