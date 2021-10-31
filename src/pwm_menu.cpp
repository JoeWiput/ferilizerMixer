#include <Arduino.h>
#include <LiquidCrystal.h>
#include "main.h"
#include "menu.h"
#include "pwm_menu.h"

#define TEST 0

void pump1_setting_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    int row = getDrawRowIndex_in_parent(menu);

    lcd.setCursor(15, row);
    lcd.print("    ");
    lcd.setCursor(15, row);
    lcd.printf("(%3d)", pump1_pwm);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(15, row);
            lcd.print(" ");
            lcd.setCursor(19, row);
            lcd.print(" ");
            return;
        }

        if (inc != 0)
        {
            pump1_pwm += (PUMP1_PWM_INC * inc);
            pump1_pwm = pump1_pwm >= MAX_PWM ? MAX_PWM : pump1_pwm;
            pump1_pwm = pump1_pwm <= MIN_PWM ? MIN_PWM : pump1_pwm;

            lcd.setCursor(15, row);
            lcd.print("    ");
            lcd.setCursor(15, row);
            lcd.printf("(%3d)", pump1_pwm);
            if (pump1_run)
            {
                timer4->setCaptureCompare(1, pump1_pwm, PERCENT_COMPARE_FORMAT);
            }
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(15, row);
                lcd.print(" ");
                lcd.setCursor(19, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(15, row);
                lcd.print("(");
                lcd.setCursor(19, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_pump1_pwm_params(Menu *menu)
{

    char val_buff[10];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d", pump1_pwm);
    lcd.setCursor(17, row_idx);
    lcd.print("   ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%d", pump1_pwm);
}

void pump2_setting_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    int row = getDrawRowIndex_in_parent(menu);

    lcd.setCursor(15, row);
    lcd.print("    ");
    lcd.setCursor(15, row);
    lcd.printf("(%3d)", pump2_pwm);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(15, row);
            lcd.print(" ");
            lcd.setCursor(19, row);
            lcd.print(" ");
            return;
        }

        if (inc != 0)
        {
            pump2_pwm += (PUMP2_PWM_INC * inc);
            pump2_pwm = pump2_pwm >= MAX_PWM ? MAX_PWM : pump2_pwm;
            pump2_pwm = pump2_pwm <= MIN_PWM ? MIN_PWM : pump2_pwm;

            lcd.setCursor(15, row);
            lcd.print("    ");
            lcd.setCursor(15, row);
            lcd.printf("(%3d)", pump2_pwm);
            if (pump2_run)
            {
                timer4->setCaptureCompare(2, pump2_pwm, PERCENT_COMPARE_FORMAT);
            }
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(15, row);
                lcd.print(" ");
                lcd.setCursor(19, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(15, row);
                lcd.print("(");
                lcd.setCursor(19, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_pump2_pwm_params(Menu *menu)
{

    char val_buff[10];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d", pump2_pwm);
    lcd.setCursor(17, row_idx);
    lcd.print("   ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%d", pump2_pwm);
}

void pump3_setting_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    int row = getDrawRowIndex_in_parent(menu);

    lcd.setCursor(15, row);
    lcd.print("    ");
    lcd.setCursor(15, row);
    lcd.printf("(%3d)", pump3_pwm);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(15, row);
            lcd.print(" ");
            lcd.setCursor(19, row);
            lcd.print(" ");
            return;
        }

        if (inc != 0)
        {
            pump3_pwm += (PUMP3_PWM_INC * inc);
            pump3_pwm = pump3_pwm >= MAX_PWM ? MAX_PWM : pump3_pwm;
            pump3_pwm = pump3_pwm <= MIN_PWM ? MIN_PWM : pump3_pwm;

            lcd.setCursor(15, row);
            lcd.print("    ");
            lcd.setCursor(15, row);
            lcd.printf("(%3d)", pump3_pwm);
            if (pump3_run)
            {
                timer4->setCaptureCompare(3, pump3_pwm, PERCENT_COMPARE_FORMAT);
            }
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(15, row);
                lcd.print(" ");
                lcd.setCursor(19, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(15, row);
                lcd.print("(");
                lcd.setCursor(19, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_pump3_pwm_params(Menu *menu)
{

    char val_buff[10];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d", pump3_pwm);
    lcd.setCursor(17, row_idx);
    lcd.print("   ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%d", pump3_pwm);
}

void pump4_setting_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    int row = getDrawRowIndex_in_parent(menu);

    lcd.setCursor(15, row);
    lcd.print("    ");
    lcd.setCursor(15, row);
    lcd.printf("(%3d)", pump4_pwm);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(15, row);
            lcd.print(" ");
            lcd.setCursor(19, row);
            lcd.print(" ");
            return;
        }

        if (inc != 0)
        {
            pump4_pwm += (PUMP4_PWM_INC * inc);
            pump4_pwm = pump4_pwm >= MAX_PWM ? MAX_PWM : pump4_pwm;
            pump4_pwm = pump4_pwm <= MIN_PWM ? MIN_PWM : pump4_pwm;

            lcd.setCursor(15, row);
            lcd.print("    ");
            lcd.setCursor(15, row);
            lcd.printf("(%3d)", pump4_pwm);
            if (pump3_run)
            {
                timer4->setCaptureCompare(4, pump4_pwm, PERCENT_COMPARE_FORMAT);
            }
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(15, row);
                lcd.print(" ");
                lcd.setCursor(19, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(15, row);
                lcd.print("(");
                lcd.setCursor(19, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_pump4_pwm_params(Menu *menu)
{

    char val_buff[10];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d", pump4_pwm);
    lcd.setCursor(17, row_idx);
    lcd.print("   ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%d", pump4_pwm);
}

void setting_unit_exec(Menu *menu)
{
    unit_raw = !unit_raw;
}

void draw_setting_unit_params(Menu *menu)
{
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (unit_raw)
    {
        // Display ADC for analog value
        lcd.setCursor(16, row_idx);
        lcd.print("    ");
        lcd.setCursor(17, row_idx);
        lcd.print("ADC");
    }

    else
    {
        lcd.setCursor(15, row_idx);
        lcd.print("     ");
        lcd.setCursor(16, row_idx);
        lcd.print("Real");
    }
}

void stir_pump_exc(Menu *menu)
{
    stir_pump = !stir_pump;
}

void draw_stir_pump_params(Menu *menu)
{
    int row_idx = getDrawRowIndex_in_parent(menu);
    if (stir_pump)
    {
        lcd.setCursor(17, row_idx);
        lcd.print("   ");
        lcd.setCursor(18, row_idx);
        lcd.print("ON");
    }
    else
    {
        lcd.setCursor(17, row_idx);
        lcd.print("   ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

void log_exc(Menu *menu)
{
    logging_enable = !logging_enable;
}

void draw_log_params(Menu *menu)
{
    int row_idx = getDrawRowIndex_in_parent(menu);
    if (logging_enable)
    {
        lcd.setCursor(17, row_idx);
        lcd.print("   ");
        lcd.setCursor(18, row_idx);
        lcd.print("ON");
    }
    else
    {
        lcd.setCursor(17, row_idx);
        lcd.print("   ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

void draw_ec_params(Menu *menu)
{
    char val_buff[20];
    char float_str[15];
    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", adc_ec);
    }
    else
    {
        dtostrf(ADC_EC_TO_mS * (float)adc_ec + ADC_EC_TO_ms_BIAS, 10, 2, float_str);
        sprintf(val_buff, "%s mS/cm", float_str);
    }
    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void draw_ph_params(Menu *menu)
{

    char val_buff[20];
    char float_str[15];
    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", adc_ph);
    }
    else
    {
        dtostrf(ADC_PH_TO_PH * (float)adc_ph + ADC_PH_TO_PH_BIAS, 10, 2, float_str);

        sprintf(val_buff, "%s    pH", float_str);
    }
    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void draw_flow1_params(Menu *menu)
{
    char val_buff[20];
    char float_str[20];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", pulse_flow_1);
    }
    else
    {
        dtostrf(1000 * mL_PER_PULSE * (float)pulse_flow_1 / dt_tick, 10, 3, float_str);
        sprintf(val_buff, "%s mL/s", float_str);
        //Serial.printf("1:pulse_flow %d %d\n", pulse_flow_1, dt_tick);
        // Serial.printf("1:%s\n", val_buff);
    }
    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}
void draw_flow2_params(Menu *menu)
{
    char val_buff[20];
    char float_str[20];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {

        sprintf(val_buff, "%d", pulse_flow_2);
    }
    else
    {
        dtostrf(1000 * mL_PER_PULSE * (float)pulse_flow_2 / dt_tick, 10, 3, float_str);
        sprintf(val_buff, "%s mL/s", float_str);
    }
    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}
void draw_flow3_params(Menu *menu)
{
    char val_buff[20];
    char float_str[20];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", pulse_flow_3);
    }
    else
    {
        dtostrf(1000 * mL_PER_PULSE * (float)pulse_flow_3 / dt_tick, 10, 3, float_str);

        sprintf(val_buff, "%s mL/s", float_str);
        //Serial.printf("3:pulse_flow %d %d\n", pulse_flow_3, dt_tick);
        // Serial.printf("3:%s\n", val_buff);
    }

    str_len = strlen(val_buff);

    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void draw_total_flow1_params(Menu *menu)
{
    char val_buff[20];
    char float_str[15];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", total_pulse_flow_1);
    }
    else
    {

        dtostrf(mL_PER_PULSE * (float)total_pulse_flow_1, 10, 3, float_str);
        sprintf(val_buff, "%s   mL", float_str);
    }

    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void draw_total_flow2_params(Menu *menu)
{
    char val_buff[20];
    char float_str[15];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", total_pulse_flow_2);
    }
    else
    {
        dtostrf(mL_PER_PULSE * (float)total_pulse_flow_2, 10, 3, float_str);
        sprintf(val_buff, "%s   mL", float_str);
    }
    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void draw_total_flow3_params(Menu *menu)
{
    char val_buff[20];
    char float_str[15];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", total_pulse_flow_3);
    }
    else
    {
        dtostrf(mL_PER_PULSE * (float)total_pulse_flow_3, 10, 3, float_str);
        sprintf(val_buff, "%s   mL", float_str);
    }

    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void status_ab_exc(Menu *menu)
{
    if (!run_mix_ab)
    {
        total_pulse_a = total_pulse_b = total_pulse_w = 0;
        a_pulse_target = (float)a_target / mL_PER_PULSE;
        b_pulse_target = (float)b_target / mL_PER_PULSE;
        w_pulse_target = (float)w_target / mL_PER_PULSE;
        b_delay_ms = b_delay * 1000;
        stir_delay_ms = stir_delay * 1000;
        mix_state = MIX_IDLE;
        run_mix_ab = true;
    }
    else
    {
        run_mix_ab = false;
        timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // OFF pump1
        timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT); // OFF pump2
        timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // OFF pump3
        timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT); // OFF pump4
        total_pulse_a = total_pulse_b = total_pulse_w = 0;
        a_pulse_target = b_pulse_target = w_pulse_target = 0;
        mix_state = MIX_IDLE;
    }
}
void draw_status_ab_menu(Menu *menu)
{
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (run_mix_ab)
    {
        // Display ADC for analog value
        lcd.setCursor(16, row_idx);
        lcd.print("    ");
        lcd.setCursor(18, row_idx);
        lcd.print("ON");
    }

    else
    {
        lcd.setCursor(15, row_idx);
        lcd.print("     ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

void set_a_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    sprintf(val_buff, "(%d) mL", a_target);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "%d mL", a_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            a_target += (INC_A_ML * inc);
            a_target = a_target >= MAX_A_ML ? MAX_A_ML : a_target;
            a_target = a_target <= 0 ? 0 : a_target;

            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "(%d) mL", a_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(16, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(16, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_set_a_menu_param(Menu *menu)
{
    char val_buff[20];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d mL", a_target);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%s ", val_buff);
}
void set_b_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    sprintf(val_buff, "(%d) mL", b_target);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "%d mL", b_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            b_target += (INC_B_ML * inc);
            b_target = b_target >= MAX_B_ML ? MAX_B_ML : b_target;
            b_target = b_target <= 0 ? 0 : b_target;

            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "(%d) mL", b_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(16, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(16, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}
void draw_set_b_menu_param(Menu *menu)
{
    char val_buff[20];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d mL", b_target);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%s ", val_buff);
}
void set_w_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    sprintf(val_buff, "(%d) mL", w_target);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "%d mL", w_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            w_target += (INC_W_ML * inc);
            w_target = w_target >= MAX_W_ML ? MAX_W_ML : w_target;
            w_target = w_target <= 0 ? 0 : w_target;

            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "(%d) mL", w_target);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(16, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(16, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}
void draw_set_w_menu_param(Menu *menu)
{
    char val_buff[20];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d mL", w_target);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%s ", val_buff);
}
void set_delay_b_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    sprintf(val_buff, "(%d) s", b_delay);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "%d s", b_delay);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            b_delay += (INC_B_DELAY * inc);
            b_delay = b_delay >= MAX_B_DELAY ? MAX_B_DELAY : b_delay;
            b_delay = b_delay <= 0 ? 0 : b_delay;

            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "(%d) s", b_delay);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(17, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(17, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}
void draw_set_delay_b_menu_param(Menu *menu)
{

    char val_buff[20];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d s", b_delay);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%s ", val_buff);
}
void set_stir_delay_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    sprintf(val_buff, "(%d) s", stir_delay);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "%d s", stir_delay);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            if (stir_delay > 0)
            {
                stir_pump = true;
            }
            else
            {
                stir_pump = false;
            }

            return;
        }

        if (inc != 0)
        {
            stir_delay += (INC_STIR_DELAY * inc);
            stir_delay = stir_delay >= MAX_STIR_DELAY ? MAX_STIR_DELAY : stir_delay;
            stir_delay = stir_delay <= 0 ? 0 : stir_delay;

            lcd.setCursor(9, row);
            lcd.print("           ");
            sprintf(val_buff, "(%d) s", stir_delay);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(17, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(17, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}
void draw_set_stir_delay_menu_param(Menu *menu)
{
    char val_buff[20];
    int row_idx = getDrawRowIndex_in_parent(menu);
    sprintf(val_buff, "%d s", stir_delay);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - strlen(val_buff), row_idx);
    lcd.printf("%s ", val_buff);
}

void status_ecph_control_exc(Menu *menu)
{

    if (!run_control_ecph)
    {

        run_control_ecph = true;
    }
    else
    {
        run_control_ecph = false;
        timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // OFF pump1
        timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT); // OFF pump2
        timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // OFF pump3
        timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT); // OFF pump4
    }
}

void draw_status_ecph_control_param(Menu *menu)
{
    int row_idx = getDrawRowIndex_in_parent(menu);

    if (run_control_ecph)
    {
        // Display ADC for analog value
        lcd.setCursor(16, row_idx);
        lcd.print("    ");
        lcd.setCursor(18, row_idx);
        lcd.print("ON");
    }

    else
    {
        lcd.setCursor(15, row_idx);
        lcd.print("     ");
        lcd.setCursor(17, row_idx);
        lcd.print("OFF");
    }
}

void set_ec_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];
    char float_str[15];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    dtostrf(0.1 * (float)ec_target, 0, 1, float_str);
    //  char *tmp = trimwhitespace(float_str);
    sprintf(val_buff, "(%s) mS/cm", float_str);
    start_cur_pos = 20 - strlen(val_buff);
    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(7, row);
            lcd.print("           ");
            dtostrf(0.1 * (float)ec_target, 0, 1, float_str);
            //char *tmp = trimwhitespace(float_str);
            sprintf(val_buff, "%s mS/cm", float_str);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            ec_target += (INC_EC * inc);
            ec_target = ec_target >= MAX_EC ? MAX_EC : ec_target;
            ec_target = ec_target <= 0 ? 0 : ec_target;

            lcd.setCursor(9, row);
            lcd.print("           ");
            dtostrf(0.1 * (float)ec_target, 0, 1, float_str);
            // char *tmp = trimwhitespace(float_str);
            sprintf(val_buff, "(%s) mS/cm", float_str);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(13, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(13, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_set_ec_param(Menu *menu)
{
    char val_buff[20];
    char float_str[15];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", ec_target);
    }
    else
    {
        dtostrf(0.1 * (float)ec_target, 0, 1, float_str);
        sprintf(val_buff, "%s mS/cm", float_str);
    }

    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}

void set_ph_exc(Menu *menu)
{
    static bool setting_flag = false;

    setting_flag = true;

    char val_buff[20];
    char float_str[15];

    int row = getDrawRowIndex_in_parent(menu);
    int start_cur_pos = 0;

    lcd.setCursor(9, row);
    lcd.print("           ");
    dtostrf(0.1 * (float)ph_target, 0, 1, float_str);
    sprintf(val_buff, "(%s) pH", float_str);
    start_cur_pos = 20 - strlen(val_buff);

    lcd.setCursor(start_cur_pos, row);
    lcd.printf("%s", val_buff);
    uint32_t start_t = millis();
    bool blink = false;

    while (setting_flag)
    {
        int inc = knob_read();
        int sw = read_SW();
        if (sw == SHORT_PRESS)
        {
            setting_flag = false;
            lcd.setCursor(9, row);
            lcd.print("           ");
            dtostrf(0.1 * (float)ph_target, 0, 1, float_str);
            sprintf(val_buff, "%s pH", float_str);
            start_cur_pos = 20 - strlen(val_buff);
            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
            return;
        }

        if (inc != 0)
        {
            ph_target += (INC_PH * inc);
            ph_target = ph_target >= MAX_PH ? MAX_PH : ph_target;
            ph_target = ph_target <= MIN_PH ? MIN_PH : ph_target;

            lcd.setCursor(9, row);
            lcd.print("           ");
            dtostrf(0.1 * (float)ph_target, 0, 1, float_str);
            sprintf(val_buff, "(%s) pH", float_str);
            start_cur_pos = 20 - strlen(val_buff);

            lcd.setCursor(start_cur_pos, row);
            lcd.printf("%s", val_buff);
        }

        if (millis() - start_t > 500)
        {
            start_t = millis();
            if (blink)
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print(" ");
                lcd.setCursor(16, row);
                lcd.print(" ");
                blink = !blink;
            }
            else
            {
                lcd.setCursor(start_cur_pos, row);
                lcd.print("(");
                lcd.setCursor(16, row);
                lcd.print(")");
                blink = !blink;
            }
        }
    }
}

void draw_set_ph_param(Menu *menu)
{
    char val_buff[20];
    char float_str[15];

    int str_len;

    int row_idx = getDrawRowIndex_in_parent(menu);
    if (unit_raw)
    {
        sprintf(val_buff, "%d", ph_target);
    }
    else
    {
        dtostrf(0.1 * (float)ph_target, 0, 1, float_str);
        sprintf(val_buff, "%s pH", float_str);
    }

    str_len = strlen(val_buff);
    lcd.setCursor(9, row_idx);
    lcd.print("           ");
    lcd.setCursor(20 - str_len, row_idx);
    lcd.print(val_buff);
}
