#include "main.h"
#include "cmath"
// #include "210Z-logo.c"

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

LV_IMG_DECLARE(logo_210z); // Declare the image

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
    style_pressed_blue_btn.body.opa = LV_OPA_40;

    lv_style_copy(&style_red_btn, &style_button_base);
    style_red_btn.body.main_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_red_btn.body.grad_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);

    lv_style_copy(&style_pressed_red_btn, &style_button_base);
    style_pressed_red_btn.body.main_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_pressed_red_btn.body.grad_color = LV_COLOR_MAKE(0xFF, 0x3B, 0x30);
    style_pressed_red_btn.body.opa = LV_OPA_40;

    lv_style_copy(&style_purple_btn, &style_button_base);
    style_purple_btn.body.main_color = LV_COLOR_MAKE(0x3F, 0x1D, 0x7A);
    style_purple_btn.body.grad_color = LV_COLOR_MAKE(0x3F, 0x1D, 0x7A);

    lv_style_copy(&style_pressed_purple_btn, &style_button_base);
    style_pressed_purple_btn.body.main_color = LV_COLOR_MAKE(0x2F, 0x0D, 0x6A);
    style_pressed_purple_btn.body.grad_color = LV_COLOR_MAKE(0x2F, 0x0D, 0x6A);
    style_pressed_purple_btn.body.opa = LV_OPA_30;
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

lv_res_t GUI::match_checklist_click(lv_obj_t *btn) {
    gui.display_match_checklist();
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
    if (gui.current_selected_color == gui.red_btn){
        gui.selected_color = 0;
    }
    else if (gui.current_selected_color == gui.blue_btn){
        gui.selected_color = 1;
    }
    else{
        gui.selected_color = -1;
    }
    return LV_RES_OK;
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
    if (gui.current_selected_path == gui.solo_awp){
            gui.selected_path = 0;
        }
        else if(gui.current_selected_path == gui.left_half_awp){
            gui.selected_path = 1;
        }
        else if(gui.current_selected_path == gui.right_half_awp){
            gui.selected_path = 2;
        }
        else if(gui.current_selected_path == gui.goal_side_rush){
            gui.selected_path = 3;
        }
        else if(gui.current_selected_path == gui.ring_side_rush){
            gui.selected_path = 4;
        }
        else{
            gui.selected_path = -1;
    }
    return LV_RES_OK;
}

lv_res_t GUI::skills_toggle_callback(lv_obj_t *btn) {
    if(driver.skills){
        lv_btn_set_state(btn, LV_BTN_STATE_REL);
        driver.skills = false;
    }
    else{
        lv_btn_set_state(btn, LV_BTN_STATE_PR);
        driver.skills = true;
    }
    return LV_RES_OK;
}

void GUI::initialize_objects() {
    // Initialize Home Screen and its objects
    gui.home_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(home_screen, &style_screen_bg);

    // Configure the team logo
    // team_logo = lv_img_create(gui.home_screen, NULL);
    //     lv_img_set_src(gui.team_logo, &logo_210z); 
    //     lv_obj_align(gui.team_logo, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 52);

    gui.auton_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.auton_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.auton_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.auton_home_btn, LV_BTN_ACTION_CLICK, gui.auton_selector_click);
        lv_obj_set_size(gui.auton_home_btn, 140, 30);
        lv_obj_align(gui.auton_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 22);
        lv_label_set_text(lv_label_create(gui.auton_home_btn, NULL), "Auton Selector");
    
    gui.sensors_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.sensors_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.sensors_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.sensors_home_btn, LV_BTN_ACTION_CLICK, gui.sensors_click);
        lv_obj_set_size(gui.sensors_home_btn, 140, 30);
        lv_obj_align(gui.sensors_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 77);
        lv_label_set_text(lv_label_create(gui.sensors_home_btn, NULL), "Sensors");
    
    gui.match_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.match_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.match_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.match_home_btn, LV_BTN_ACTION_CLICK, gui.match_checklist_click);
        lv_obj_set_size(gui.match_home_btn, 140, 30);
        lv_obj_align(gui.match_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 132);
        lv_label_set_text(lv_label_create(gui.match_home_btn, NULL), "Match Checklist");

    gui.debug_home_btn = lv_btn_create(gui.home_screen, NULL);
        lv_btn_set_style(gui.debug_home_btn, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.debug_home_btn, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.debug_home_btn, LV_BTN_ACTION_CLICK, gui.debug_terminal_click);
        lv_obj_set_size(gui.debug_home_btn, 140, 30);
        lv_obj_align(gui.debug_home_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 290, 187);
        lv_label_set_text(lv_label_create(gui.debug_home_btn, NULL), "Debug Terminal");

    // Initialize Autonomous Selector Screen and its objects
    gui.auton_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(auton_screen, &style_screen_bg);

    gui.auton_title = lv_label_create(gui.auton_screen, NULL);
        lv_label_set_style(gui.auton_title, &gui.style_title);
        lv_obj_align(gui.auton_title, NULL, LV_ALIGN_IN_TOP_LEFT, 137, 12);
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

    // Initialize the current selected buttons
    gui.current_selected_color = nullptr; 
    gui.current_selected_path = nullptr;
    
    gui.autonomous_path = lv_label_create(gui.auton_screen, NULL);
        lv_label_set_style(gui.autonomous_path, &gui.style_text);
        lv_obj_align(gui.autonomous_path, NULL, LV_ALIGN_IN_TOP_LEFT, 156, 96);
        lv_label_set_text(gui.autonomous_path, "Autonomous Path");
    
    gui.solo_awp = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.solo_awp, true);
        lv_btn_set_style(gui.solo_awp, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.solo_awp, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.solo_awp, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.solo_awp, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.solo_awp, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.solo_awp, 140, 30);
        lv_obj_align(gui.solo_awp, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 121);
        lv_label_set_text(lv_label_create(gui.solo_awp, NULL), "Solo AWP");
    
    gui.left_half_awp = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.left_half_awp, true);
        lv_btn_set_style(gui.left_half_awp, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.left_half_awp, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.left_half_awp, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.left_half_awp, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.left_half_awp, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.left_half_awp, 140, 30);
        lv_obj_align(gui.left_half_awp, NULL, LV_ALIGN_IN_TOP_LEFT, 76, 161);
        lv_label_set_text(lv_label_create(gui.left_half_awp, NULL), "Left Half AWP");
    
    gui.right_half_awp = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.right_half_awp, true);
        lv_btn_set_style(gui.right_half_awp, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.right_half_awp, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.right_half_awp, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.right_half_awp, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.right_half_awp, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.right_half_awp, 140, 30);
        lv_obj_align(gui.right_half_awp, NULL, LV_ALIGN_IN_TOP_LEFT, 263, 161);
        lv_label_set_text(lv_label_create(gui.right_half_awp, NULL), "Right Half AWP");

    gui.goal_side_rush = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.goal_side_rush, true);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.goal_side_rush, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.goal_side_rush, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.goal_side_rush, 140, 30);
        lv_obj_align(gui.goal_side_rush, NULL, LV_ALIGN_IN_TOP_LEFT, 76, 201);        
        lv_label_set_text(lv_label_create(gui.goal_side_rush, NULL), "Goal Side Rush");

    gui.ring_side_rush = lv_btn_create(gui.auton_screen, NULL);
        lv_btn_set_toggle(gui.ring_side_rush, true);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_TGL_REL, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.ring_side_rush, LV_BTN_STYLE_TGL_PR, &gui.style_purple_btn);
        lv_btn_set_action(gui.ring_side_rush, LV_BTN_ACTION_CLICK, gui.autonomous_path_callback);
        lv_obj_set_size(gui.ring_side_rush, 140, 30);
        lv_obj_align(gui.ring_side_rush, NULL, LV_ALIGN_IN_TOP_LEFT, 263, 201);
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
        lv_obj_align(gui.position_readings, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 50);
        lv_label_set_text(gui.position_readings, "X: 0.0 Y: 0.0 Heading: 0.0°");

    gui.left_drivetrain_encoders = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.left_drivetrain_encoders, &gui.style_text);
        lv_obj_align(gui.left_drivetrain_encoders, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 67);
        lv_label_set_text(gui.left_drivetrain_encoders, "FL: 0.0 ML: 0.0 BL: 0.0");

    gui.right_drivetrain_encoders = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.right_drivetrain_encoders, &gui.style_text);
        lv_obj_align(gui.right_drivetrain_encoders, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 84);
        lv_label_set_text(gui.right_drivetrain_encoders, "FR: 0.0 MR: 0.0 BR: 0.0");

    gui.misc_sensors = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.misc_sensors, &gui.style_text);
        lv_obj_align(gui.misc_sensors, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 101);
        lv_label_set_text(gui.misc_sensors, "Wall Stake: 0.0 Color Sensor: 0.0");

    gui.drivetrain_temp = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.drivetrain_temp, &gui.style_text);
        lv_obj_align(gui.drivetrain_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 118);
        lv_label_set_text(gui.drivetrain_temp, "Drivetrain Temperature: 0.0°C");

    gui.motor_temp = lv_label_create(gui.sensor_screen, NULL);
        lv_label_set_style(gui.motor_temp, &gui.style_text);
        lv_obj_align(gui.motor_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 135);
        lv_label_set_text(gui.motor_temp, "Intake: 0.0°C LB: 0.0°C");

    gui.sensor_return_home = lv_btn_create(gui.sensor_screen, NULL);
        lv_btn_set_style(gui.sensor_return_home, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.sensor_return_home, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.sensor_return_home, LV_BTN_ACTION_CLICK, gui.return_home_click);
        lv_obj_set_size(gui.sensor_return_home, 30, 30);
        lv_obj_align(gui.sensor_return_home, NULL, LV_ALIGN_IN_TOP_LEFT, 440, 10);
        lv_label_set_text(lv_label_create(gui.sensor_return_home, NULL), SYMBOL_HOME);

    // Initialize Match Screen and its objects
    gui.match_screen = lv_obj_create(NULL, NULL);
    lv_obj_set_style(match_screen, &style_screen_bg);

    gui.match_title = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.match_title, &gui.style_title);
        lv_obj_align(gui.match_title, NULL, LV_ALIGN_IN_TOP_LEFT, 178, 15);
        lv_label_set_text(gui.match_title, "Match Checklist");
    gui.match_position_readings = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.match_position_readings, &gui.style_text);
        lv_obj_align(gui.match_position_readings, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 50);
        lv_label_set_text(gui.match_position_readings, "X: 0.0 Y: 0.0 Heading: 0.0°");
    gui.battery_level = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.battery_level, &gui.style_text);
        lv_obj_align(gui.battery_level, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 67);
        lv_label_set_text(gui.battery_level, "Battery Level: 0.0%");
    gui.elapsed_time = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.elapsed_time, &gui.style_text);
        lv_obj_align(gui.elapsed_time, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 84);
        lv_label_set_text(gui.elapsed_time, "Startup Time: 0ms");
    gui.selected_auton = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.selected_auton, &gui.style_text);
        lv_obj_align(gui.selected_auton, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 101);
        lv_label_set_text(gui.selected_auton, "Selected Auton: None None");
    gui.radio_status = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.radio_status, &gui.style_text);
        lv_obj_align(gui.radio_status, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 118);
        lv_label_set_text(gui.radio_status, "Radio Status: Hawk Tuah");
    gui.competition_status = lv_label_create(gui.match_screen, NULL);
        lv_label_set_style(gui.competition_status, &gui.style_text);
        lv_obj_align(gui.competition_status, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 135);
        lv_label_set_text(gui.competition_status, "Competition Status: Hawk Tuah");
    gui.skills_toggle = lv_btn_create(gui.match_screen, NULL);
        lv_btn_set_toggle(gui.blue_btn, true);
        lv_btn_set_style(gui.skills_toggle, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.skills_toggle, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_style(gui.skills_toggle, LV_BTN_STYLE_TGL_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.skills_toggle, LV_BTN_STYLE_TGL_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.skills_toggle, LV_BTN_ACTION_CLICK, gui.skills_toggle_callback);
        lv_obj_set_size(gui.skills_toggle, 140, 30);
        lv_obj_align(gui.skills_toggle, NULL, LV_ALIGN_IN_TOP_LEFT, 169, 152);
        lv_label_set_text(lv_label_create(gui.skills_toggle, NULL), "Skills Toggle");
    gui.match_return_home = lv_btn_create(gui.match_screen, NULL);
        lv_btn_set_style(gui.match_return_home, LV_BTN_STYLE_REL, &gui.style_purple_btn);
        lv_btn_set_style(gui.match_return_home, LV_BTN_STYLE_PR, &gui.style_pressed_purple_btn);
        lv_btn_set_action(gui.match_return_home, LV_BTN_ACTION_CLICK, gui.return_home_click);
        lv_obj_set_size(gui.match_return_home, 30, 30);
        lv_obj_align(gui.match_return_home, NULL, LV_ALIGN_IN_TOP_LEFT, 440, 10);
        // Return Home Button
        lv_label_set_text(lv_label_create(gui.match_return_home, NULL), SYMBOL_HOME);

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
        lv_obj_align(gui.debug_line_1, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 50);
        lv_label_set_text(gui.debug_line_1, "Debug Line 1: ");

    gui.debug_line_2 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_2, &gui.style_text);
        lv_obj_align(gui.debug_line_2, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 67);
        lv_label_set_text(gui.debug_line_2, "Debug Line 2: ");

    gui.debug_line_3 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_3, &gui.style_text);
        lv_obj_align(gui.debug_line_3, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 84);
        lv_label_set_text(gui.debug_line_3, "Debug Line 3: ");

    gui.debug_line_4 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_4, &gui.style_text);
        lv_obj_align(gui.debug_line_4, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 101);
        lv_label_set_text(gui.debug_line_4, "Debug Line 4: ");

    gui.debug_line_5 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_5, &gui.style_text);
        lv_obj_align(gui.debug_line_5, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 118);
        lv_label_set_text(gui.debug_line_5, "Debug Line 5: ");

    gui.debug_line_6 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_6, &gui.style_text);
        lv_obj_align(gui.debug_line_6, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 135);    
        lv_label_set_text(gui.debug_line_6, "Debug Line 6: ");

    gui.debug_line_7 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_7, &gui.style_text);
        lv_obj_align(gui.debug_line_7, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 152);
        lv_label_set_text(gui.debug_line_7, "Debug Line 7: ");

    gui.debug_line_8 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_8, &gui.style_text);
        lv_obj_align(gui.debug_line_8, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 169);
        lv_label_set_text(gui.debug_line_8, "Debug Line 8: ");

    gui.debug_line_9 = lv_label_create(gui.debug_screen, NULL);
        lv_label_set_style(gui.debug_line_9, &gui.style_text);
        lv_obj_align(gui.debug_line_9, NULL, LV_ALIGN_IN_TOP_LEFT, 30, 186);
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

void GUI::display_match_checklist(){
    // Load the Match Checklist Screen
    lv_scr_load(gui.match_screen);
}

void GUI::display_debug_terminal() {
    // Load the Debug Terminal Screen
    lv_scr_load(gui.debug_screen);
}

void GUI::run_selected_auton(){
    switch(gui.selected_color){
        case 0:
            switch(gui.selected_path){
                case 0:
                    red.solo_awp();
                    break;
                case 1:
                    red.left_half_awp();
                    break;
                case 2:
                    red.right_half_awp();
                    break;
                case 3:
                    red.goal_side_rush();
                    break;
                case 4:
                    red.ring_side_rush();
                    break;
            }
            break;
        case 1:
            switch(gui.selected_path){
                case 0:
                    blue.solo_awp();
                    break;
                case 1:
                    blue.left_half_awp();
                    break;
                case 2:
                    blue.right_half_awp();
                    break;
                case 3:
                    blue.goal_side_rush();
                    break;
                case 4:
                    blue.ring_side_rush();
                    break;
            }
            break;

        default:
            auton.test();
            break;
    }
}

void GUI::update_sensors(){
    char buffer[300];

    sprintf(buffer, "X: %.2f Y: %.2f Heading: %.3f°", util.get_robot_x(), util.get_robot_y(), util.get_heading());
    lv_label_set_text(gui.position_readings, buffer);
    lv_label_set_text(gui.match_position_readings, buffer);
    lv_label_set_text(gui.debug_line_9, buffer);

    sprintf(buffer, "FL: %.2f ML: %.2f BL: %.2f", left_drive.get_positions()[0], left_drive.get_positions()[1], left_drive.get_positions()[2]);
    lv_label_set_text(gui.left_drivetrain_encoders, buffer);

    sprintf(buffer, "FR: %.2f MR: %.2f BR: %.2f", right_drive.get_positions()[0], right_drive.get_positions()[1], right_drive.get_positions()[2]);
    lv_label_set_text(gui.right_drivetrain_encoders, buffer);

    sprintf(buffer, "LB Position: %.2f Color Sensor: %.2f", ((float)wall_stake_rotation_sensor.get_position()) / 100.0 , color.get_hue());
    lv_label_set_text(gui.misc_sensors, buffer);
}

void GUI::update_temps(){
    char buffer[300];
    sprintf(buffer, "Drivetrain Temperature: %.2f°C", util.get_drive_temp());
    lv_label_set_text(gui.drivetrain_temp, buffer);

    sprintf(buffer, "Intake: %.2f°C LB: %.2f°C", intake.get_temperature(), (wall_stake.get_temperatures()[0] + wall_stake.get_temperatures()[1]) / 2);
    lv_label_set_text(gui.motor_temp, buffer);
}

void GUI::update_match_checklist(){
    char buffer[300];
    sprintf(buffer, "Battery: %.1f%", pros::battery::get_capacity());
    lv_label_set_text(gui.battery_level, buffer);

    const char* selected_color_str = driver.skills ? "Skills" : ((gui.selected_color == 0) ? "Red:" : (gui.selected_color == 1) ? "Blue:" : "None:");
    const char* selected_path_str = driver.skills ? " " : ((gui.selected_path == 0) ? "Solo AWP" : (gui.selected_path == 1) ? "Left Half AWP" : (gui.selected_path == 2) ? "Right Half AWP" : (gui.selected_path == 3) ? "Goal Side Rush" : (gui.selected_path == 4) ? "Ring Side Rush" : "Test");
    sprintf(buffer, "Selected Auton: %s %s", selected_color_str, selected_path_str);
    lv_label_set_text(gui.selected_auton, buffer);

    int total_seconds = pros::millis() / 1000;
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    sprintf(buffer, "Time Elapsed: %d:%02d", minutes, seconds);
    lv_label_set_text(gui.elapsed_time, buffer);

    sprintf(buffer, "Radio Status: %s", controller.is_connected() ? "Connected" : "Disconnected");
    lv_label_set_text(gui.radio_status, buffer);

    const char* competition_status_str = (pros::competition::get_status() == 7) ? "Disabled" : (pros::competition::get_status() == 6) ? "Autonomous" : (pros::competition::get_status() == 4) ? "Driver Control" : "Not Connected";
    sprintf(buffer, "Competition Status: %s", competition_status_str);
    lv_label_set_text(gui.competition_status, buffer);
}