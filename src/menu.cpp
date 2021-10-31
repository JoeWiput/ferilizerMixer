#include "main.h"
#include <LiquidCrystal.h>
#include "menu.h"
#include "pwm_menu.h"

short top_menu_idx = -1;
extern LiquidCrystal lcd;

byte currentCursorChar[] = {
    B10000,
    B11000,
    B11100,
    B11110,
    B11110,
    B11100,
    B11000,
    B10000};

byte arrowUpChar[] = {
    B00100,
    B01110,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000};

byte arrowDownChar[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B01110,
    B00100};

Menu back_to_main_menu_from_fert_menu = {
    "<Back>",
    back_to_main_menu_from_fert,
    NULL,
    0,
    0,
    {NULL},
    NULL

};

Menu status_ab_menu = {
    "Status",
    status_ab_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_status_ab_menu

};

Menu set_a_menu = {
    "A Fert.",
    set_a_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_a_menu_param

};

Menu set_b_menu = {
    "B Fert.",
    set_b_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_b_menu_param

};

Menu set_water_menu = {
    "Water",
    set_w_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_w_menu_param

};

Menu set_delay_b_menu = {
    "B Delay",
    set_delay_b_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_delay_b_menu_param

};

Menu set_stir_delay_menu = {
    "Stir Delay",
    set_stir_delay_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_stir_delay_menu_param

};

Menu back_to_mix_fert_menu_from_ab_menu = {
    "<Back>",
    back_to_mix_fert_menu_from_ab,
    NULL,
    0,
    0,
    {NULL},
    NULL};

Menu ab_menu = {
    "AB&Water Mix",
    mix_exc,
    NULL,
    0,
    7,
    {&back_to_mix_fert_menu_from_ab_menu, &status_ab_menu, &set_a_menu, &set_b_menu, &set_water_menu, &set_delay_b_menu, &set_stir_delay_menu},
    NULL,
    false};

Menu back_to_mix_fert_menu_from_ec_control_menu = {
    "<Back>",
    back_to_mix_fert_menu_from_ec_control,
    NULL,
    0,
    0,
    {NULL},
    NULL};

Menu status_ecph_control_menu = {
    "Status",
    status_ecph_control_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_status_ecph_control_param};

Menu set_ec_menu = {
    "Set EC",
    set_ec_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_ec_param};

Menu set_ph_menu = {
    "Set pH",
    set_ph_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_set_ph_param};

Menu ec_status_menu = {
    "EC",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_ec_params,
    true};

Menu ph_status_menu = {
    "pH",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_ph_params,
    true};

Menu ec_ph_control_menu = {
    "EC&pH Control",
    ec_ph_exc,
    NULL,
    0,
    6,
    {&back_to_mix_fert_menu_from_ec_control_menu,
     &status_ecph_control_menu,
     &set_ec_menu,
     &set_ph_menu,
     &ec_status_menu,
     &ph_status_menu},
    NULL,
    false};

Menu mix_menu = {
    "Fertilizer Mix",
    mix_exc,
    NULL,
    0,
    3,
    {&back_to_main_menu_from_fert_menu, &ab_menu, &ec_ph_control_menu},
    NULL,
    false};

Menu back_to_main_menu_from_manual_menu = {
    "<Back>",
    back_to_main_menu_from_manual,
    NULL,
    0,
    0,
    {NULL},
    NULL};

Menu pump1_menu = {
    "PumpA",
    pump1_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump1_params};

Menu pump2_menu = {
    "PumpB",
    pump2_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump2_params};

Menu pump3_menu = {
    "PumpW",
    pump3_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump3_params};

Menu pump4_menu = {
    "Pump4",
    pump4_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump4_params};

Menu manual_menu = {
    "Manual Test",
    NULL,
    NULL,
    0,
    5,
    {&back_to_main_menu_from_manual_menu, &pump1_menu, &pump2_menu, &pump3_menu, &pump4_menu}};

Menu back_to_pump_pwm_menu = {
    "<Back>",
    back_to_setting_menu_from_pwm,
    NULL,
    0,
    0,
    {NULL},
    0};

Menu pump1_pwm_menu = {
    "PumpA",
    pump1_setting_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump1_pwm_params};

Menu pump2_pwm_menu = {
    "PumpB",
    pump2_setting_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump2_pwm_params};

Menu pump3_pwm_menu = {
    "PumpW",
    pump3_setting_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump3_pwm_params};

Menu pump4_pwm_menu = {
    "PumpS",
    pump4_setting_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_pump4_pwm_params};

Menu setting_unit_menu = {
    "Meter unit",
    setting_unit_exec,
    NULL,
    0,
    0,
    {NULL},
    draw_setting_unit_params};

Menu pump_pwm_menu = {
    "Pump PWM",
    NULL,
    NULL,
    0,
    5,
    {&back_to_pump_pwm_menu, &pump1_pwm_menu, &pump2_pwm_menu, &pump3_pwm_menu, &pump4_pwm_menu}

};

Menu back_to_main_menu_from_setting_menu = {
    "<Back>",
    back_to_main_menu_from_setting,
    NULL,
    0,
    0};

Menu enable_stir_pump_menu = {
    "Stir",
    stir_pump_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_stir_pump_params};

Menu enable_log_menu = {
    "Logging",
    log_exc,
    NULL,
    0,
    0,
    {NULL},
    draw_log_params};

Menu setting_menu = {
    "Setting",
    NULL,
    NULL,
    0,
    5,
    {&back_to_main_menu_from_setting_menu, &pump_pwm_menu, &setting_unit_menu, &enable_stir_pump_menu, &enable_log_menu},
};

Menu info_menu = {
    "Info",
    NULL,
    NULL,
    0,
    0};

Menu back_to_main_from_meter_menu = {
    "<Back>",
    back_to_main_menu_from_meter,
    NULL,
    0};

Menu ec_menu = {
    "EC",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_ec_params,
    true};

Menu ph_menu = {
    "pH",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_ph_params,
    true};

Menu temp_menu = {
    "Temp",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    NULL,
    true};

Menu flow1_menu = {
    "FlA",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_flow1_params,
    true};
Menu flow2_menu = {
    "FlB",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_flow2_params,
    true};
Menu flow3_menu = {
    "FlW",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_flow3_params,
    true};

Menu total_flow1_menu = {
    "TotA",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_total_flow1_params,
    true};

Menu total_flow2_menu = {
    "TotB",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_total_flow2_params,
    true};

Menu total_flow3_menu = {
    "TotW",
    NULL,
    NULL,
    0,
    0,
    {NULL},
    draw_total_flow3_params,
    true};

Menu meter_menu = {
    "Meter",
    NULL,
    NULL,
    0,
    10,
    {&back_to_main_from_meter_menu, &ec_menu, &ph_menu, &temp_menu, &flow1_menu, &flow2_menu, &flow3_menu, &total_flow1_menu, &total_flow2_menu, &total_flow3_menu}};

Menu main_menu = {
    "Main",
    NULL,
    NULL,
    0,
    5,
    {&mix_menu, &manual_menu, &meter_menu, &setting_menu, &info_menu}};

void back_to_mix_fert_menu_from_ec_control(Menu *menu)
{
    current_menu = &mix_menu;
}

void back_to_mix_fert_menu_from_ab(Menu *menu)
{
    current_menu = &mix_menu;
}

void back_to_main_menu_from_fert(Menu *menu)
{
    current_menu = &main_menu;
}

void back_to_main_menu_from_setting(Menu *menu)
{
    current_menu = &main_menu;
}

void back_to_main_menu_from_meter(Menu *menu)
{
    current_menu = &main_menu;
}

void back_to_main_menu_from_manual(Menu *menu)
{
    current_menu = &main_menu;
}

void back_to_setting_menu_from_pwm(Menu *menu)
{
    current_menu = &setting_menu;
}

int getItemIndex_in_parent(Menu *menu)
{
    Menu *parent = menu->parent;
    if (parent)
    {
        for (int i = 0; i < parent->num_submenus; i++)
        {
            if (parent->submenu[i] == menu)
            {

                return i;
            }
        }
    }
    return -1;
}

void draw_pump1_params(Menu *menu)
{

    static char buffer[8];
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (pump1_run)
    {
        sprintf(buffer, "ON(%d)", pump1_pwm);
        lcd.setCursor(20 - strlen(buffer), row_idx);
        lcd.print(buffer);
    }
    else
    {

        lcd.setCursor(13, row_idx);
        lcd.print("       ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}
void draw_pump2_params(Menu *menu)
{

    static char buffer[8];
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (pump2_run)
    {

        sprintf(buffer, "ON(%d)", pump2_pwm);
        lcd.setCursor(20 - strlen(buffer), row_idx);
        lcd.print(buffer);
    }
    else
    {

        lcd.setCursor(13, row_idx);
        lcd.print("       ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}
void draw_pump3_params(Menu *menu)
{

    static char buffer[8];
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (pump3_run)
    {

        sprintf(buffer, "ON(%d)", pump3_pwm);
        lcd.setCursor(20 - strlen(buffer), row_idx);
        lcd.print(buffer);
    }
    else
    {

        lcd.setCursor(13, row_idx);
        lcd.print("       ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

void draw_pump4_params(Menu *menu)
{

    static char buffer[8];
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (pump4_run)
    {

        sprintf(buffer, "ON(%d)", pump4_pwm);
        lcd.setCursor(20 - strlen(buffer), row_idx);
        lcd.print(buffer);
    }
    else
    {
        lcd.setCursor(13, row_idx);
        lcd.print("       ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

int getDrawRowIndex_in_parent(Menu *menu)
{
    int idx = getItemIndex_in_parent(menu);
    return idx - top_menu_idx;
}

void ab_fer_exc(Menu *menu)
{
}

void ec_ph_exc(Menu *menu)
{
}

void mix_exc(Menu *menu)
{
}

void pump1_exc(Menu *menu)
{
    pump1_run = !pump1_run;
    if (pump1_run)
    {
        timer4->setCaptureCompare(1, pump1_pwm, PERCENT_COMPARE_FORMAT);
    }
    else
    {
        timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT);
    }

    if (menu->render_param)
    {
        menu->render_param(menu);
    }
}

void pump2_exc(Menu *menu)
{
    pump2_run = !pump2_run;
    if (pump2_run)
    {
        timer4->setCaptureCompare(2, pump2_pwm, PERCENT_COMPARE_FORMAT);
    }
    else
    {
        timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
    }
    if (menu->render_param)
    {
        menu->render_param(menu);
    }
}

void pump3_exc(Menu *menu)
{
    pump3_run = !pump3_run;
    if (pump3_run)
    {
        timer4->setCaptureCompare(3, pump3_pwm, PERCENT_COMPARE_FORMAT);
    }
    else
    {
        timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT);
    }
    if (menu->render_param)
    {
        menu->render_param(menu);
    }
}

void pump4_exc(Menu *menu)
{
    pump4_run = !pump4_run;
    if (pump4_run)
    {
        timer4->setCaptureCompare(4, pump1_pwm, PERCENT_COMPARE_FORMAT);
    }
    else
    {
        timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT);
    }

    if (menu->render_param)
    {
        menu->render_param(menu);
    }
}

void init_menu()
{
    lcd.createChar(0, currentCursorChar);

    back_to_main_from_meter_menu.parent = &meter_menu;
    ec_menu.parent = &meter_menu;
    ph_menu.parent = &meter_menu;
    temp_menu.parent = &meter_menu;
    flow1_menu.parent = &meter_menu;
    flow2_menu.parent = &meter_menu;
    flow3_menu.parent = &meter_menu;
    total_flow1_menu.parent = &meter_menu;
    total_flow2_menu.parent = &meter_menu;
    total_flow3_menu.parent = &meter_menu;

    back_to_main_menu_from_setting_menu.parent = &setting_menu;
    back_to_main_menu_from_manual_menu.parent = &manual_menu;
    pump1_menu.parent = &manual_menu;
    pump2_menu.parent = &manual_menu;
    pump3_menu.parent = &manual_menu;
    pump4_menu.parent = &manual_menu;

    back_to_mix_fert_menu_from_ab_menu.parent = &ab_menu;
    status_ab_menu.parent = &ab_menu;
    set_a_menu.parent = &ab_menu;
    set_b_menu.parent = &ab_menu;
    set_water_menu.parent = &ab_menu;
    set_delay_b_menu.parent = &ab_menu;
    set_stir_delay_menu.parent = &ab_menu;

    back_to_mix_fert_menu_from_ec_control_menu.parent = &ec_ph_control_menu;
    status_ecph_control_menu.parent = &ec_ph_control_menu;
    set_ec_menu.parent = &ec_ph_control_menu;
    set_ph_menu.parent = &ec_ph_control_menu;
    ph_status_menu.parent = &ec_ph_control_menu;
    ec_status_menu.parent = &ec_ph_control_menu;

    mix_menu.parent = &main_menu;
    manual_menu.parent = &main_menu;
    meter_menu.parent = &main_menu;
    setting_menu.parent = &main_menu;
    info_menu.parent = &main_menu;

    back_to_main_menu_from_fert_menu.parent = &main_menu;
    ab_menu.parent = &mix_menu;
    ec_ph_control_menu.parent = &mix_menu;

    enable_stir_pump_menu.parent = &setting_menu;
    enable_log_menu.parent = &setting_menu;
    setting_unit_menu.parent = &setting_menu;
    pump_pwm_menu.parent = &setting_menu;
    back_to_pump_pwm_menu.parent = &pump_pwm_menu;
    pump1_pwm_menu.parent = &pump_pwm_menu;
    pump2_pwm_menu.parent = &pump_pwm_menu;
    pump3_pwm_menu.parent = &pump_pwm_menu;
    pump4_pwm_menu.parent = &pump_pwm_menu;

    current_menu = &main_menu;
}

void inc_menu(Menu *menu, short inc)
{
    short new_idx = current_menu->idx + inc;
    if (new_idx < 0)
    {
        menu->idx = 0;
        return;
    }
    if ((current_menu->num_submenus > 0) && (new_idx < current_menu->num_submenus))
    {
        menu->idx = new_idx;
    }
    for (int i = 0; i < 4; i++)
    {
        lcd.setCursor(0, i);
        lcd.print(" ");
    }
}

bool is_manu_in_page(Menu *menu)
{
    int idx = getDrawRowIndex_in_parent(menu);
    if (idx < 0 || idx > 3)
    {
        return false;
    }
    return true;
}

void display_menu(Menu *menu)
{
    static Menu *last_drawn_menu = NULL;

    if (last_drawn_menu != menu)
    {
        active_submenu[0] = NULL;
        active_submenu[1] = NULL;
        active_submenu[2] = NULL;
        active_submenu[3] = NULL;
        lcd.clear();
        // Enter the new page, set top_menu_idx=0;
        top_menu_idx = 0;
        for (int i = 0; i < menu->num_submenus; i++)
        {
            lcd.setCursor(1, i);
            lcd.print(menu->submenu[i]->title);
            if (menu->submenu[i]->render_param != NULL)
            {

                menu->submenu[i]->render_param(menu->submenu[i]);
                if (menu->submenu[i]->is_sensor_data)
                {
                    put_active_menu(menu->submenu[i]);
                }
            }

            if (i == 3)
                break;
        }
        last_drawn_menu = menu;
    }

    // Check menu index already in display menu page, then draw only cursor
    if ((menu->idx >= top_menu_idx) && (menu->idx < top_menu_idx + 4))
    {
        lcd.setCursor(0, menu->idx - top_menu_idx);
        lcd.write((byte)0);
        if (menu->submenu[menu->idx]->render_param != NULL)
        {
            // Redraw menu parameter if updated
            menu->submenu[menu->idx]->render_param(menu->submenu[menu->idx]);
        }
    }
    // Draw the new menu item
    else
    {
        int j = 0;
        lcd.clear();
        active_submenu[0] = NULL;
        active_submenu[1] = NULL;
        active_submenu[2] = NULL;
        active_submenu[3] = NULL;
        if (menu->idx < top_menu_idx)
        {
            top_menu_idx = menu->idx;
        }
        if (menu->idx > top_menu_idx + 3)
        {
            top_menu_idx = menu->idx - 3;
        }
        for (int i = top_menu_idx; i < menu->num_submenus; i++)
        {
            lcd.setCursor(1, j);
            lcd.print(menu->submenu[i]->title);
            if (menu->submenu[i]->render_param != NULL)
            {

                menu->submenu[i]->render_param(menu->submenu[i]);
                if (menu->submenu[i]->is_sensor_data)
                {
                    put_active_menu(menu->submenu[i]);
                }
            }
            j++;
            if (j == 4)
                break;
        }
        if (menu->idx > top_menu_idx)
        {
            lcd.setCursor(0, 3);
            lcd.write((byte)0);
        }
        else
        {
            lcd.setCursor(0, 0);
            lcd.write((byte)0);
        }
    }
}

Menu *get_selected_submenu()
{
    return current_menu->submenu[current_menu->idx];
}
