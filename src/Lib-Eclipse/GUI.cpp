#include "main.h"

using namespace Eclipse;

lv_style_t GUI::style_screen_bg;
lv_style_t GUI::style_title;
lv_style_t GUI::style_text;
lv_style_t GUI::style_button_base;
lv_style_t GUI::style_blue_btn;
lv_style_t GUI::style_pressed_blue_btn;
lv_style_t GUI::style_red_btn;
lv_style_t GUI::style_pressed_red_btn;
lv_style_t GUI::style_purple_btn;
lv_style_t GUI::style_pressed_purple_btn;


// vrc brain: 480 x 240
void GUI::initialize_styles() {
    lv_style_copy(&style_screen_bg, &lv_style_plain);
    style_screen_bg.body.main_color = LV_COLOR_BLACK;
    style_screen_bg.body.grad_color = LV_COLOR_BLACK;
    style_screen_bg.body.opa = LV_OPA_COVER;

    lv_style_copy(&style_title, &lv_style_plain);
    style_title.text.color = LV_COLOR_MAKE(0xF5, 0xF5, 0xF5);
    style_title.text.font = &lv_font_dejavu_20;

    lv_style_copy(&style_text, &lv_style_plain);
    style_text.text.color = LV_COLOR_MAKE(0xF5, 0xF5, 0xF5);
    style_text.text.font = &lv_font_dejavu_20;

    lv_style_copy(&style_button_base, &lv_style_plain);
    style_button_base.body.radius = 8;
    style_button_base.body.opa = LV_OPA_COVER;
    style_button_base.text.color = LV_COLOR_MAKE(0xF5, 0xF5, 0xF5);
    style_button_base.text.font = &lv_font_dejavu_10;

    lv_style_copy(&style_blue_btn, &style_button_base);
    style_blue_btn.body.main_color = LV_COLOR_MAKE(0x00, 0x7A, 0xFF);
    style_blue_btn.body.grad_color = LV_COLOR_MAKE(0x00, 0x7A, 0xFF);

    lv_style_copy(&style_pressed_blue_btn, &style_button_base);
    style_pressed_blue_btn.body.main_color = LV_COLOR_MAKE(0x00, 0x7A, 0xFF);
    style_pressed_blue_btn.body.grad_color = LV_COLOR_MAKE(0x00, 0x7A, 0xFF);
    style_pressed_blue_btn.body.opa = LV_OPA_60;

    lv_style_copy(&style_red_btn, &style_button_base);
    style_red_btn.body.main_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_red_btn.body.grad_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);

    lv_style_copy(&style_pressed_red_btn, &style_button_base);
    style_pressed_red_btn.body.main_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_pressed_red_btn.body.grad_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_pressed_red_btn.body.opa = LV_OPA_60;

    lv_style_copy(&style_purple_btn, &style_button_base);
    style_purple_btn.body.main_color = LV_COLOR_MAKE(0x3F, 0x1D, 0x7A);
    style_purple_btn.body.grad_color = LV_COLOR_MAKE(0x3F, 0x1D, 0x7A);

    lv_style_copy(&style_pressed_purple_btn, &style_button_base);
    style_pressed_purple_btn.body.main_color = LV_COLOR_MAKE(0x2F, 0x0D, 0x6A);
    style_pressed_purple_btn.body.grad_color = LV_COLOR_MAKE(0x2F, 0x0D, 0x6A);
    style_pressed_purple_btn.body.opa = LV_OPA_70;
}

// Initialize actions
lv_res_t GUI::return_home_click(lv_obj_t *btn) {
    gui.display_home();
    return LV_RES_OK; // Indicate the event was handled successfully
}

lv_res_t GUI::auton_selector_click(lv_obj_t *btn) {
    gui.display_auton_selector();
    return LV_RES_OK;
}

lv_res_t GUI::sensors_click(lv_obj_t *btn) {
    gui.display_sensors();
    return LV_RES_OK;
}

lv_res_t GUI::debug_terminal_click(lv_obj_t *btn) {
    gui.display_debug_terminal();
    return LV_RES_OK;
}

lv_res_t GUI::alliance_color_callback(lv_obj_t *btn) {
    if (gui.current_selected_color != btn) {
        // Turn off the previously selected button
        if (gui.current_selected_color) {
            lv_btn_set_state(gui.current_selected_color, LV_BTN_STATE_REL);
        }
        // Set the new button as selected
        gui.current_selected_color = btn;
        lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
    }
    return LV_RES_OK; // Indicate that the event was handled
}

lv_res_t GUI::autonomous_path_callback(lv_obj_t *btn) {
    if (gui.current_selected_path != btn) {
        // Turn off the previously selected button
        if (gui.current_selected_path) {
            lv_btn_set_state(gui.current_selected_path, LV_BTN_STATE_REL);
        }
        // Set the new button as selected
        gui.current_selected_path = btn;
        lv_btn_set_state(btn, LV_BTN_STATE_TGL_REL);
    }
    return LV_RES_OK; // Indicate that the event was handled
}

void GUI::initialize_objects() {
    // Initialize Home Screen and its objects
    gui.home_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(home_screen, &style_screen_bg);

    // Configure the team logo
    // lv_img_set_src(gui.team_logo, &_210Z_logo); // Replace with your actual image
    // fix later
    // gui.team_logo = lv_img_create(gui.home_screen, NULL);
    //     lv_obj_align(gui.team_logo, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 52);

    gui.auton_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.auton_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.auton_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.auton_home_btn, LV_BTN_ACTION_CLICK, gui.auton_selector_click);
        lv_obj_set_size(gui.auton_home_btn, 140, 30);
        lv_obj_align(gui.auton_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 50);
        lv_label_set_text(lv_label_create(gui.auton_home_btn, NULL), "Auton Selector");
    
    gui.sensors_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.sensors_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.sensors_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.sensors_home_btn, LV_BTN_ACTION_CLICK, gui.sensors_click);
        lv_obj_set_size(gui.sensors_home_btn, 140, 30);
        lv_obj_align(gui.sensors_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 105);
        lv_label_set_text(lv_label_create(gui.sensors_home_btn, NULL), "Sensors");
    
    gui.debug_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.debug_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.debug_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.debug_home_btn, LV_BTN_ACTION_CLICK, gui.debug_terminal_click);
        lv_obj_set_size(gui.debug_home_btn, 140, 30);
        lv_obj_align(gui.debug_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 160);
        lv_label_set_text(lv_label_create(gui.debug_home_btn, NULL), "Debug Terminal");

    // Initialize Autonomous Selector Screen and its objects
    gui.auton_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(auton_screen, &style_screen_bg);

    gui.auton_title = lv_label_create(gui.auton_screen, NULL);
        lv_label_set_style(gui.auton_title, &gui.style_title);
        lv_obj_align(gui.auton_title, NULL, LV_ALIGN_IN_TOP_LEFT, 137, 10);
        lv_label_set_text(gui.auton_title, "Autonomous Selector");

    gui.alliance_color = lv_label_create(gui.auton_screen, NULL);
        lv_label_set_style(gui.alliance_color, &gui.style_text);
        lv_obj_align(gui.alliance_color, NULL, LV_ALIGN_IN_TOP_LEFT, 175, 39);
        lv_label_set_text(gui.alliance_color, "Alliance Color");

    gui.red_btn = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.red_btn, true);
        lv_btn_set_style(gui.red_btn, LV_BTN_STYLE_REL, &gui.style_red_btn);
        lv_btn_set_style(gui.red_btn, LV_BTN_STYLE_PR, &gui.style_pressed_red_btn);
        lv_btn_set_style(gui.red_btn, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_red_btn);
        lv_btn_set_style(gui.red_btn, LV_BTN_STYLE_TGL_PR, &gui.style_red_btn);
        lv_btn_set_action(gui.red_btn, LV_BTN_ACTION_CLICK, gui.alliance_color_callback);
        lv_obj_set_size(gui.red_btn, 200, 30);
        lv_obj_align(gui.red_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 62);
        lv_label_set_text(lv_label_create(gui.red_btn, NULL), "Red");

    gui.blue_btn = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.blue_btn, true);
        lv_btn_set_style(gui.blue_btn, LV_BTN_STYLE_REL, &gui.style_blue_btn);
        lv_btn_set_style(gui.blue_btn, LV_BTN_STYLE_PR, &gui.style_pressed_blue_btn);
        lv_btn_set_style(gui.blue_btn, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_blue_btn);
        lv_btn_set_style(gui.blue_btn, LV_BTN_STYLE_TGL_PR, &gui.style_blue_btn);
        lv_btn_set_action(gui.blue_btn, LV_BTN_ACTION_CLICK, gui.alliance_color_callback);
        lv_label_set_text(lv_label_create(gui.blue_btn, NULL), "Blue");
        lv_obj_set_size(gui.blue_btn, 200, 30);
        lv_obj_align(gui.blue_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 260, 62);

    // Initialize the current selected button
    gui.current_selected_color = nullptr; 
    gui.current_selected_path = nullptr;
    // Initially, no button is selected
    
    gui.autonomous_path = lv_label_create(gui.auton_screen, NULL);
        lv_label_set_style(gui.autonomous_path, &gui.style_text);
        lv_obj_align(gui.autonomous_path, NULL, LV_ALIGN_IN_TOP_LEFT, 156, 96);
        lv_label_set_text(gui.autonomous_path, "Autonomous Path");
    
    gui.rush_awp = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.rush_awp, true);
        lv_btn_set_style(gui.rush_awp, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.rush_awp, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.rush_awp, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.rush_awp, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.rush_awp, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.rush_awp, 140, 30);
        lv_obj_align(gui.rush_awp, NULL, LV_ALIGN_IN_TOP_LEFT, 76, 121);
        lv_label_set_text(lv_label_create(gui.rush_awp, NULL), "Rush AWP");
    
    gui.safe_awp = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.safe_awp, true);
        lv_btn_set_style(gui.safe_awp, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.safe_awp, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.safe_awp, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.safe_awp, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.safe_awp, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.safe_awp, 140, 30);
        lv_obj_align(gui.safe_awp, NULL, LV_ALIGN_IN_TOP_LEFT, 263, 121);
        lv_label_set_text(lv_label_create(gui.safe_awp, NULL), "Safe AWP");
    
    gui.goal_side_rush = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.goal_side_rush, true);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.goal_side_rush, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.goal_side_rush, 140, 30);
        lv_obj_align(gui.goal_side_rush, NULL, LV_ALIGN_IN_TOP_LEFT, 76, 161);        
        lv_label_set_text(lv_label_create(gui.goal_side_rush, NULL), "Goal Side Rush");
    
    gui.ring_side_rush = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.ring_side_rush, true);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.ring_side_rush, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.ring_side_rush, 140, 30);
        lv_obj_align(gui.ring_side_rush, NULL, LV_ALIGN_IN_TOP_LEFT, 263, 161);
        lv_label_set_text(lv_label_create(gui.ring_side_rush, NULL), "Ring Side Rush");
    
    gui.auton_return_home = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_style(gui.auton_return_home, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.auton_return_home, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.auton_return_home, LV_BTN_ACTION_CLICK, gui.return_home_click);
        lv_obj_set_size(gui.auton_return_home, 30, 30);
        lv_obj_align(gui.auton_return_home, NULL, LV_ALIGN_IN_TOP_LEFT, 440, 10);
        lv_label_set_text(lv_label_create(gui.auton_return_home, NULL), SYMBOL_HOME);

    // Initialize Sensor Screen and its objects
    gui.sensor_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(sensor_screen, &style_screen_bg);

    gui.sensor_title = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.sensor_title, &gui.style_title);
        lv_obj_align(gui.sensor_title, NULL, LV_ALIGN_IN_TOP_LEFT, 208, 15);
        // Set screen title
        lv_label_set_text(gui.sensor_title, "Sensors");

    gui.position_readings = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.position_readings, &gui.style_text);
        lv_obj_align(gui.position_readings, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 50);
        lv_label_set_text(gui.position_readings, "X: 0.0 Y: 0.0 Heading: 0.0°");

    gui.drivetrain_encoders = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.drivetrain_encoders, &gui.style_text);
        lv_obj_align(gui.drivetrain_encoders, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 67);
        // Drivetrain encoders and temperature
        lv_label_set_text(gui.drivetrain_encoders, "FL: 0.0 ML: 0.0 BL: 0.0 FR: 0.0 MR: 0.0 BR: 0.0");

    gui.drivetrain_temp = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.drivetrain_temp, &gui.style_text);
        lv_obj_align(gui.drivetrain_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 84);
        lv_label_set_text(gui.drivetrain_temp, "FL: 0.0°C ML: 0.0°C BL: 0.0°C FR: 0.0°C MR: 0.0°C BR: 0.0°C");

    gui.motor_temp = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.motor_temp, &gui.style_text);
        lv_obj_align(gui.motor_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 101);
        lv_label_set_text(gui.motor_temp, "Intake: 0.0°C LBL: 0.0°C LBR: 0.0°C");

    gui.sensor_return_home = lv_btn_create(gui.sensor_screen, NULL);
        lv_btn_set_style(gui.sensor_return_home, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.sensor_return_home, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.sensor_return_home, LV_BTN_ACTION_CLICK, gui.return_home_click);
        lv_obj_set_size(gui.sensor_return_home, 30, 30);
        lv_obj_align(gui.sensor_return_home, NULL, LV_ALIGN_IN_TOP_LEFT, 440, 10);
        lv_label_set_text(lv_label_create(gui.sensor_return_home, NULL), SYMBOL_HOME);

    // Initialize Debug Terminal Screen and its objects
    gui.debug_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(debug_screen, &style_screen_bg);
    
    gui.debug_title = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_title, &gui.style_text);
        lv_obj_align(gui.debug_title, NULL, LV_ALIGN_IN_TOP_LEFT, 180, 15);
        // Set title
        lv_label_set_text(gui.debug_title, "Debug Terminal");

    gui.debug_line_1 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_1, &gui.style_text);
        lv_obj_align(gui.debug_line_1, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 50);
        lv_label_set_text(gui.debug_line_1, "Debug Line 1: ");

    gui.debug_line_2 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_2, &gui.style_text);
        lv_obj_align(gui.debug_line_2, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 67);
        lv_label_set_text(gui.debug_line_2, "Debug Line 2: ");

    gui.debug_line_3 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_3, &gui.style_text);
        lv_obj_align(gui.debug_line_3, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 84);
        lv_label_set_text(gui.debug_line_3, "Debug Line 3: ");

    gui.debug_line_4 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_4, &gui.style_text);
        lv_obj_align(gui.debug_line_4, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 101);
        lv_label_set_text(gui.debug_line_4, "Debug Line 4: ");

    gui.debug_line_5 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_5, &gui.style_text);
        lv_obj_align(gui.debug_line_5, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 118);
        lv_label_set_text(gui.debug_line_5, "Debug Line 5: ");

    gui.debug_line_6 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_6, &gui.style_text);
        lv_obj_align(gui.debug_line_6, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 135);    
        lv_label_set_text(gui.debug_line_6, "Debug Line 6: ");

    gui.debug_line_7 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_7, &gui.style_text);
        lv_obj_align(gui.debug_line_7, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 152);
        lv_label_set_text(gui.debug_line_7, "Debug Line 7: ");

    gui.debug_line_8 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_8, &gui.style_text);
        lv_obj_align(gui.debug_line_8, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 169);
        lv_label_set_text(gui.debug_line_8, "Debug Line 8: ");

    gui.debug_line_9 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_9, &gui.style_text);
        lv_obj_align(gui.debug_line_9, NULL, LV_ALIGN_IN_TOP_LEFT, 50, 186);
        lv_label_set_text(gui.debug_line_9, "Debug Line 9: ");

    gui.debug_return_home = lv_btn_create(gui.debug_screen, NULL);
        lv_btn_set_style(gui.debug_return_home, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.debug_return_home, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.debug_return_home, LV_BTN_ACTION_CLICK, gui.return_home_click);
        lv_obj_set_size(gui.debug_return_home, 30, 30);
        lv_obj_align(gui.debug_return_home, NULL, LV_ALIGN_IN_TOP_LEFT, 440, 10);
        // Return Home Button
        lv_label_set_text(lv_label_create(gui.debug_return_home, NULL), SYMBOL_HOME);
}

void GUI::display_home() {
    // Load the Home Screen
    lv_scr_load(gui.home_screen);
}

void GUI::display_auton_selector() {
    // Load the Autonomous Selector Screen
    lv_scr_load(gui.auton_screen);
}

void GUI::display_sensors() {
    // Load the Sensor Screen
    lv_scr_load(gui.sensor_screen);
}

void GUI::display_debug_terminal() {
    // Load the Debug Terminal Screen
    lv_scr_load(gui.debug_screen);
}

