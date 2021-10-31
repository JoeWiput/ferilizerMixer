#include "menu.h"

#ifndef _H_PWM_MENU
#define _H_PWM_MENU

extern int pump1_pwm;
extern int pump2_pwm;
extern int pump3_pwm;
extern int pump4_pwm;
extern short top_menu_idx;

void status_ab_exc(Menu *menu);
void draw_status_ab_menu(Menu *menu);
void set_a_exc(Menu *menu);
void draw_set_a_menu_param(Menu *menu);
void set_b_exc(Menu *menu);
void draw_set_b_menu_param(Menu *menu);
void set_w_exc(Menu *menu);
void draw_set_w_menu_param(Menu *menu);
void set_delay_b_exc(Menu *menu);
void draw_set_delay_b_menu_param(Menu *menu);
void set_stir_delay_exc(Menu *menu);
void draw_set_stir_delay_menu_param(Menu *menu);

void set_ec_exc(Menu *menu);
void draw_set_ec_param(Menu *menu);
void set_ph_exc(Menu *menu);
void draw_set_ph_param(Menu *menu);

void status_ecph_control_exc(Menu *menu);
void draw_status_ecph_control_param(Menu *menu);

void pump1_setting_exc(Menu *menu);
void draw_pump1_pwm_params(Menu *menu);
void pump2_setting_exc(Menu *menu);
void draw_pump2_pwm_params(Menu *menu);
void pump3_setting_exc(Menu *menu);
void draw_pump3_pwm_params(Menu *menu);
void pump4_setting_exc(Menu *menu);
void draw_pump4_pwm_params(Menu *menu);
void setting_unit_exec(Menu *menu);
void draw_setting_unit_params(Menu *menu);
void stir_pump_exc(Menu *menu);
void log_exc(Menu *menu);

void draw_log_params(Menu *menu);
void draw_stir_pump_params(Menu *menu);

void draw_total_flow1_params(Menu *menu);
void draw_total_flow2_params(Menu *menu);
void draw_total_flow3_params(Menu *menu);

void draw_ec_params(Menu *menu);
void draw_ph_params(Menu *menu);
void draw_flow1_params(Menu *menu);
void draw_flow2_params(Menu *menu);
void draw_flow3_params(Menu *menu);

#endif