#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = LV_COLOR_HEX(0xa600ff);
  background_style.body.grad_color = LV_COLOR_HEX(0xa600ff);

  static lv_style_t tabview_indic_style;
  tabview_indic_style.body.border.color = LV_COLOR_WHITE;
  tabview_indic_style.body.border.width = 4;
  tabview_indic_style.body.border.part = LV_BORDER_FULL;
  tabview_indic_style.body.border.opa = LV_OPA_100;
  tabview_indic_style.body.padding.inner = 5;
  tabview_indic_style.body.opa = LV_OPA_100;

  static lv_style_t tabview_btn_style;
  lv_style_copy(&tabview_btn_style, &lv_style_plain);
  tabview_btn_style.body.main_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.body.grad_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.text.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_tgl_style;
  lv_style_copy(&tabview_btn_tgl_style, &tabview_btn_style);
  tabview_btn_tgl_style.body.border.width = 2;
  tabview_btn_tgl_style.body.border.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_pr_style;
  lv_style_copy(&tabview_btn_pr_style, &lv_style_plain);
  tabview_btn_pr_style.body.main_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.body.grad_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.text.color = LV_COLOR_WHITE;

  lv_obj_t *tabview_windows = lv_tabview_create(lv_scr_act(), NULL);
  lv_obj_t *tab_auton = lv_tabview_add_tab(tabview_windows, "Auton");
  lv_obj_t *tab_values = lv_tabview_add_tab(tabview_windows, "Values");

  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_INDIC,
                       &tabview_indic_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_REL,
                       &tabview_btn_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_PR,
                       &tabview_btn_pr_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_REL,
                       &tabview_btn_tgl_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_PR,
                       &tabview_btn_pr_style);

  static lv_style_t switch_team_blue_style;
  lv_style_copy(&switch_team_blue_style, &lv_style_plain);
  switch_team_blue_style.body.main_color = LV_COLOR_BLUE;
  switch_team_blue_style.body.grad_color = LV_COLOR_BLUE;
  switch_team_blue_style.body.radius = LV_RADIUS_CIRCLE;
  switch_team_blue_style.body.border.color = LV_COLOR_WHITE;
  switch_team_blue_style.body.border.part = LV_BORDER_FULL;
  switch_team_blue_style.body.border.width = 2;

  static lv_style_t switch_side_off_style;
  lv_style_copy(&switch_side_off_style, &switch_team_blue_style);
  switch_side_off_style.body.main_color = LV_COLOR_ORANGE;

  static lv_style_t switch_team_red_style;
  lv_style_copy(&switch_team_red_style, &switch_team_blue_style);
  switch_team_red_style.body.main_color = LV_COLOR_RED;
  switch_team_red_style.body.grad_color = LV_COLOR_RED;

  static lv_style_t switch_team_bg_style;
  lv_style_copy(&switch_team_bg_style, &lv_style_plain);
  switch_team_bg_style.body.main_color = LV_COLOR_BLUE;
  switch_team_bg_style.body.grad_color = LV_COLOR_BLUE;
  switch_team_bg_style.body.radius = LV_RADIUS_CIRCLE;

  static lv_style_t switch_team_indic_style;
  lv_style_copy(&switch_team_indic_style, &lv_style_plain);
  switch_team_indic_style.body.main_color = LV_COLOR_RED;
  switch_team_indic_style.body.grad_color = LV_COLOR_RED;
  switch_team_indic_style.body.padding.inner = 0;
  switch_team_indic_style.body.padding.hor = 0;
  switch_team_indic_style.body.padding.ver = 0;
  switch_team_indic_style.body.shadow.width = 0;
  switch_team_indic_style.body.radius = LV_RADIUS_CIRCLE;

  lv_obj_t *label_team = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_team, "Choose Team Color:");
  lv_obj_align(label_team, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  lv_obj_t *switch_team = lv_sw_create(tab_auton, NULL);
  lv_sw_off(switch_team);
  lv_obj_align(switch_team, NULL, LV_ALIGN_IN_LEFT_MID, 190, 0);

  lv_sw_set_style(switch_team, LV_SW_STYLE_KNOB_OFF, &switch_team_blue_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_KNOB_ON, &switch_team_red_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_BG, &switch_team_bg_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_INDIC, &switch_team_indic_style);
  ///////////
  lv_obj_t *label_front = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_front, "Front");
  lv_obj_align(label_team, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 100);

  lv_obj_t *label_back = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_back, "Back");
  lv_obj_align(label_back, NULL, LV_ALIGN_IN_TOP_LEFT, 220, 100);

  lv_obj_t *switch_side = lv_sw_create(tab_auton, NULL);
  lv_sw_off(switch_side);
  lv_obj_align(switch_side, NULL, LV_ALIGN_IN_LEFT_MID, 190, 100);
  /*
    lv_sw_set_style(switch_side, LV_SW_STYLE_KNOB_OFF, &switch_side_blue_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_KNOB_ON, &switch_side_red_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_BG, &switch_side_bg_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_INDIC, &switch_side_indic_style);
    */

  ////////////////////////////////////
  lv_obj_t *label_pot = lv_label_create(tab_values, NULL);
  lv_obj_align(label_pot, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
