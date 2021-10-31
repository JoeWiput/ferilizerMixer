#include <Arduino.h>
#include "menu.h"

#ifndef _H_MAIN
#define _H_MAIN

#define PUSH_SW PB12
#define SW_KNOB_A PB13
#define SW_KNOB_B PB14
#define PUMP1_PIN PB6
#define PUMP2_PIN PB7
#define PUMP3_PIN PB8
#define PUMP4_PIN PB9

#define MAX_PWM 100
#define MIN_PWM 0
#define PUMP1_PWM_INC 10
#define PUMP2_PWM_INC 10
#define PUMP3_PWM_INC 10
#define PUMP4_PWM_INC 10
#define NUM_EC_BUFFER 5
#define NUM_PH_BUFFER 5

//#define mL_PER_PULSE 0.00519303       // mililite/pulse flow meter calat smapling of sensor 200 ms
//#define mL_PER_PULSE 0.178350003870966 // Calibrate at sampling of sensor 600 ms
//#define mL_PER_PULSE 0.173892047004951
//#define mL_PER_PULSE 0.169434090138936
//define mL_PER_PULSE 0.15
//#define mL_PER_PULSE 0.18
#define mL_PER_PULSE 0.181752090149037
#define SAMPLE_SENSOR_TIME 600
#define UPDATE_DISPLAY_TIME 800
#define ml_PER_SECOND (1000 * mL_PER_PULSE / SAMPLE_SENSOR_TIME)
#define ADC_EC_TO_mS 0.0287
#define ADC_EC_TO_ms_BIAS 0.071
#define ADC_PH_TO_PH 0.0085
#define ADC_PH_TO_PH_BIAS 1.1193

#define MCP23017_ADDRESS 0x20
#define ADS1115_ADDRESS 0x48

#define MAX_A_ML 10000
#define MAX_B_ML 10000
#define MAX_W_ML 100000
#define MAX_B_DELAY 3600 * 12
#define MAX_STIR_DELAY 3600
#define INC_A_ML 1
#define INC_B_ML 1
#define INC_W_ML 100
#define INC_B_DELAY 30
#define INC_STIR_DELAY 5

#define INC_EC 1
#define MAX_EC 10000
#define INC_PH 1
#define MAX_PH 140
#define MIN_PH 10

enum
{
    SHORT_PRESS,
    LONG_PRESS,
    NO_PRESS
};

typedef enum
{
    MIX_IDLE,
    A_WATER_FILL,
    B_DELAY,
    B_FILL,
    STIR_DELAY

} MIX_State;

extern uint32_t dt_tick;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern HardwareTimer *timer4;

extern MIX_State mix_state;
extern bool run_mix_ab;
extern int32_t total_pulse_a;
extern int32_t total_pulse_b;
extern int32_t total_pulse_w;
extern int32_t a_target;       // unit mL
extern int32_t b_target;       // unit mL
extern int32_t w_target;       // unit mL
extern int32_t b_delay;        // unit second
extern uint32_t b_delay_ms;    // unit microsec
extern int32_t stir_delay;     // unit second
extern uint32_t stir_delay_ms; // unit microsec
extern int32_t a_pulse_target; // unit mL
extern int32_t b_pulse_target; // unit mL
extern int32_t w_pulse_target; // unit mL

extern bool run_control_ecph;
extern int32_t ph_target; // unint x0.1
extern int32_t ec_target; // uinit x 0.1 mS/cm

extern bool pump1_run;
extern bool pump2_run;
extern bool pump3_run;
extern bool pump4_run;

extern int pump1_pwm;
extern int pump2_pwm;
extern int pump3_pwm;
extern int pump4_pwm;

extern bool unit_raw;
extern bool stir_pump;
extern bool logging_enable;
extern uint32_t pulse_flow_1;
extern uint32_t pulse_flow_2;
extern uint32_t pulse_flow_3;

extern uint32_t adc_ec;
extern uint32_t adc_ec_buff[NUM_EC_BUFFER];
extern uint32_t adc_ec_index;
extern uint32_t adc_ph;
extern uint32_t adc_ph_buff[NUM_PH_BUFFER];
extern uint32_t adc_ph_index;

extern uint32_t total_pulse_flow_1;
extern uint32_t total_pulse_flow_2;
extern uint32_t total_pulse_flow_3;

extern void put_active_menu(Menu *menu);
extern Menu *active_submenu[4];

int read_SW();
int knob_read();
int knob_read();

HAL_StatusTypeDef init_ADS1115IDGST();
int16_t read_raw_pH();
int16_t read_raw_temperature();
uint32_t bubble_sort(uint32_t *buff, uint32_t n);

//char *trimwhitespace(char *str);

#endif