
#ifndef _H_MENU
#define _H_MENU

#include <Arduino.h>
#include <LiquidCrystal.h>

#define MAX_TITLE 15
#define MAX_SUBMENU 10
#define PUMP_PWM_INCREMENT 10

typedef struct _menu Menu;

struct _menu
{
    char title[MAX_TITLE];
    void (*command)(Menu *);
    Menu *parent;
    short idx;
    short num_submenus;
    struct _menu *submenu[MAX_SUBMENU];
    void (*render_param)(Menu *);
    bool is_sensor_data;
};

extern LiquidCrystal lcd;

extern Menu *current_menu;

void init_menu();
void inc_menu(Menu *menu, short inc);
void display_menu(Menu *menu);
Menu *get_selected_submenu();
int getItemIndex_in_parent(Menu *menu);
int getDrawRowIndex_in_parent(Menu *menu);
int read_SW();

void back_to_main_menu_from_fert(Menu *menu);
void back_to_main_menu_from_setting(Menu *menu);
void back_to_main_menu_from_meter(Menu *menu);
void back_to_main_menu_from_manual(Menu *menu);

void back_to_setting_menu_from_pwm(Menu *menu);

void back_to_mix_fert_menu_from_ab(Menu *menu);

void back_to_mix_fert_menu_from_ec_control(Menu *menu);

void draw_pump1_params(Menu *menu);
void draw_pump2_params(Menu *menu);
void draw_pump3_params(Menu *menu);
void draw_pump4_params(Menu *menu);

void pump1_exc(Menu *menu);
void pump2_exc(Menu *menu);
void pump3_exc(Menu *menu);
void pump4_exc(Menu *menu);

void mix_exc(Menu *menu);
void ec_ph_exc(Menu *menu);
void ab_exc(Menu *menu);

#endif