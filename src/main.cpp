#include <Arduino.h>
#include "main.h"
#include <LiquidCrystal.h>
#include "Wire.h"
#include "menu.h"

const int rs = PA7, en = PA5, d4 = PA1, d5 = PA2, d6 = PA3, d7 = PA4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int counter = 0;
int old_counter = 0;

//static int aState = 1, aLastSate = 1;
bool show_heart = false;

Menu *current_menu = NULL;
//short top_menu_idx = -1;

uint32_t adc_ec = 0;
uint32_t adc_ec_buff[NUM_EC_BUFFER] = {0};
uint32_t adc_ec_index = 0;

uint32_t adc_ph = 0;
uint32_t adc_ph_buff[NUM_PH_BUFFER] = {0};
uint32_t adc_ph_index;

uint32_t pulse_flow_1 = 0;
uint32_t pulse_flow_2 = 0;
uint32_t pulse_flow_3 = 0;
uint32_t total_pulse_flow_1 = 0;
uint32_t total_pulse_flow_2 = 0;
uint32_t total_pulse_flow_3 = 0;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

I2C_HandleTypeDef hi2c2;

HardwareTimer *timer4 = NULL;
HardwareTimer *timer5 = NULL;

Menu *active_submenu[4] = {NULL, NULL, NULL, NULL};
int active_index = 0;

extern Menu total_flow1_menu;

bool pump1_run = false;
bool pump2_run = false;
bool pump3_run = false;
bool pump4_run = false;

bool run_control_ecph = false;
bool run_mix_ab = false;
MIX_State mix_state = MIX_IDLE;
int32_t a_target = 3;    // unit mL
int32_t b_target = 3;    // unit mL
int32_t w_target = 1000; // unit mL
int32_t total_pulse_a = 0;
int32_t total_pulse_b = 0;
int32_t total_pulse_w = 0;
int32_t a_pulse_target = 0; // unit pulse
int32_t b_pulse_target = 0; // unit pulse
int32_t w_pulse_target = 0; // unit pulse

int32_t b_delay = 30;       // unit second
int32_t stir_delay = 5;     // unit second
uint32_t b_delay_ms = 0;    // unit ms
uint32_t stir_delay_ms = 0; // unit ms

int32_t ph_target = 70; // unint x0.1
int32_t ec_target = 20; // uinit x 0.1 mS/cm

int pump1_pwm = 100;
int pump2_pwm = 100;
int pump3_pwm = 100;
int pump4_pwm = 100;

bool stir_pump = true;
bool logging_enable = false;
bool unit_raw = false;
bool update_total_flow1 = false;

uint32_t dt_tick = 0;

//TwoWire Wire2(PB11, PB10);

uint32_t bubble_sort(uint32_t *buff, uint32_t n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (buff[j] > buff[j + 1])
      {
        uint32_t swap = buff[j];
        buff[j] = buff[j + 1];
        buff[j + 1] = swap;
      }
    }
  }
  // return the mendian
  return buff[NUM_EC_BUFFER >> 1 + 1];
}

void HAL_SYSTICK_Callback(void)
{
  static char log_buffer[40];
  static char float_ec_buffer[10];
  static char float_ec_target_buffer[10];
  static char float_ph_buffer[10];
  static char float_ph_target_buffer[10];

  static uint32_t start_stir_delay = 0;
  static uint32_t start_b_delay = 0;
  static uint32_t ec_buff[NUM_EC_BUFFER] = {0};
  static uint32_t ph_buff[NUM_EC_BUFFER] = {0};
  static uint32_t old_tick = 0;
  static uint32_t current_tick = 0;
  static uint32_t tick = 0;
  static uint32_t update_sensor_display_tick = 0;
  tick++;
  update_sensor_display_tick++;

  if (tick >= SAMPLE_SENSOR_TIME)
  {
    current_tick = HAL_GetTick();
    dt_tick = current_tick - old_tick;
    old_tick = current_tick;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    tick = 0;
    pulse_flow_1 = (uint32_t)(TIM1->CNT);
    pulse_flow_2 = (uint32_t)(TIM2->CNT);
    pulse_flow_3 = (uint32_t)(TIM3->CNT);

    total_pulse_flow_1 += pulse_flow_1;
    total_pulse_flow_2 += pulse_flow_2;
    total_pulse_flow_3 += pulse_flow_3;
    TIM1->CNT = 0;
    TIM2->CNT = 0;
    TIM3->CNT = 0;
    adc_ec_buff[adc_ec_index++] = analogRead(PB0);
    adc_ph_buff[adc_ph_index++] = analogRead(PB1);
    if (adc_ec_index >= NUM_EC_BUFFER)
    {
      adc_ec_index = 0;
    }
    if (adc_ph_index >= NUM_PH_BUFFER)
    {
      adc_ph_index = 0;
    }
    memcpy(ec_buff, adc_ec_buff, sizeof(adc_ec_buff));
    memcpy(ph_buff, adc_ph_buff, sizeof(adc_ph_buff));

    // return the median value of array
    adc_ec = bubble_sort(ec_buff, NUM_EC_BUFFER);
    adc_ph = bubble_sort(ph_buff, NUM_PH_BUFFER);

    if (run_mix_ab)
    {
      total_pulse_a += pulse_flow_1;
      total_pulse_b += pulse_flow_2;
      total_pulse_w += pulse_flow_3;
      int32_t err_pulse_a = a_pulse_target - total_pulse_a;
      int32_t err_pulse_w = w_pulse_target - total_pulse_w;
      int32_t err_pulse_b = b_pulse_target - total_pulse_b;

      switch (mix_state)
      {
      case MIX_IDLE:

        if (err_pulse_a <= 0)
        {
          timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // OFF A
        }
        else
        {
          mix_state = A_WATER_FILL;
          timer4->setCaptureCompare(1, pump1_pwm, PERCENT_COMPARE_FORMAT); // ON A
        }
        if (err_pulse_w <= 0)
        {
          timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // OFF Water
        }
        else
        {
          mix_state = A_WATER_FILL;
          timer4->setCaptureCompare(3, pump3_pwm, PERCENT_COMPARE_FORMAT); //       // ON Water
        }

        if (stir_pump)
        {
          timer4->setCaptureCompare(4, pump4_pwm, PERCENT_COMPARE_FORMAT); // ON Stir pump
        }

        if (err_pulse_a <= 0 && err_pulse_w <= 0)
        {
          mix_state = MIX_IDLE;
          run_mix_ab = false;
        }

        break;

      case A_WATER_FILL:
        if (err_pulse_a <= 0)
        {
          timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // OFF A
        }
        if (err_pulse_w <= 0)
        {
          timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // OFF A
        }
        if (err_pulse_a <= 0 && err_pulse_w <= 0)
        {
          if (stir_pump)
          {
            timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT); // OFF Stir pump
          }
          mix_state = B_DELAY;
          start_b_delay = HAL_GetTick();
        }
        break;
      case B_DELAY:
        if (HAL_GetTick() >= start_b_delay + b_delay_ms)
        {
          mix_state = B_FILL;
        }
        break;
      case B_FILL:
        if (err_pulse_b <= 0)
        {
          timer4->setCaptureCompare(2, pump2_pwm, PERCENT_COMPARE_FORMAT); // ON B pump
          if (stir_pump)
          {
            start_stir_delay = HAL_GetTick();
            mix_state = STIR_DELAY;
          }
          else
          {
            mix_state = MIX_IDLE;
            run_mix_ab = false;
          }
        }
        if (err_pulse_b > 0)
        {
          timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
          if (stir_pump)
          {
            timer4->setCaptureCompare(4, pump4_pwm, PERCENT_COMPARE_FORMAT); // ON STIR PUMP
          }
        }
        break;

      case STIR_DELAY:
        if (HAL_GetTick() >= start_stir_delay + stir_delay_ms)
        {
          timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT); // OFF STIR PUMP
          mix_state = MIX_IDLE;
          run_mix_ab = false;
        }
        break;
      }
    }
    else if (run_control_ecph)
    {
      float cur_ph = ADC_PH_TO_PH * (float)adc_ph + ADC_PH_TO_PH_BIAS;
      float cur_ec = ADC_EC_TO_mS * (float)adc_ec + ADC_EC_TO_ms_BIAS;
      float ph_target_t = ph_target * 0.1;
      float ec_target_t = ec_target * 0.1;
      int pump3_pwm_log, pump1_pwm_log, pump2_pwm_log;
      if (cur_ph > ph_target_t)
      {
        timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT);
        pump3_pwm_log = 0;

        // timer4->setCaptureCompare(3, pump3_pwm, PERCENT_COMPARE_FORMAT); // ON Acid pump
        // pump3_pwm_log = pump3_pwm;
      }
      else
      {
        timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // Off Acid pump
        pump3_pwm_log = 0;
      }

      if (cur_ec < ec_target_t)
      {
        timer4->setCaptureCompare(1, pump1_pwm, PERCENT_COMPARE_FORMAT); // ON A pump
        timer4->setCaptureCompare(2, pump2_pwm, PERCENT_COMPARE_FORMAT); // ON B pump
        pump1_pwm_log = pump1_pwm;
        pump2_pwm_log = pump2_pwm;
      }
      else
      {
        timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // Off A pump
        timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT); // Off B pump
        pump1_pwm_log = 0;
        pump2_pwm_log = 0;
      }

      // Serial.printf("ON\n");
      //Serial.printf("Joe\n");
      //Serial.printf("%.2f %.2f %.2f %.2f %d %d %d\n", ph_target_t, ec_target_t, cur_ph, cur_ec, pump3_pwm_log, pump1_pwm_log, pump2_pwm_log);
      if (logging_enable)
      {
        dtostrf(cur_ec, 0, 2, float_ec_buffer);
        dtostrf(cur_ph, 0, 2, float_ph_buffer);
        dtostrf(ec_target_t, 0, 2, float_ec_target_buffer);
        dtostrf(ph_target_t, 0, 2, float_ph_target_buffer);

        Serial.printf("%s %s %s %s %d %d %d\n", float_ph_target_buffer, float_ec_target_buffer, float_ph_buffer, float_ec_buffer, pump3_pwm_log, pump1_pwm_log, pump2_pwm_log);
      }
    }
  }

  if (update_sensor_display_tick >= UPDATE_DISPLAY_TIME)
  {
    for (int i = 0; i < 4; i++)
    {
      if (active_submenu[i] != NULL)
      {
        active_submenu[i]->render_param(active_submenu[i]);
      }
    }

    update_sensor_display_tick = 0;
  }
}

void put_active_menu(Menu *menu)
{
  active_submenu[active_index] = menu;
  active_index++;
  active_index = active_index >= 4 ? 0 : active_index;
}
int knob_read()
{
  static int aState = 1;
  static int aLastSate = 1;
  static int counter = 0;
  static int old_counter = 0;
  int inc = 0;

  aState = digitalRead(SW_KNOB_A);
  if (aState != aLastSate)
  {
    if (digitalRead(SW_KNOB_B) != aState)
    {
      counter--;
    }
    if (digitalRead(SW_KNOB_B) == aState)
    {
      counter++;
    }
  }
  aLastSate = aState;
  if (abs(counter - old_counter) > 1)
  {
    inc = (counter - old_counter) / 2;
    old_counter = counter = 0;
  }

  return inc;
}

int read_SW()
{
  static int push_state = 0;
  static uint32_t press_time = 0;

  switch (push_state)
  {
  case 0:
    if (!digitalRead(PUSH_SW))
    {
      push_state++;
      press_time = millis();
    }

    break;
  case 1:

    if ((millis() > press_time + 30))
    {
      if (!digitalRead(PUSH_SW))
      {
        press_time = millis();
        push_state++;
      }
      else
      {
        push_state = 0;
      }
    }

    break;
  case 2:
    if (digitalRead(PUSH_SW) && (millis() < press_time + 400))
    {
      //Short press
      push_state = 0;
      return SHORT_PRESS;
    }
    else if (digitalRead(PUSH_SW) && (millis() > press_time + 400))
    {
      //Long press
      push_state = 0;
      return LONG_PRESS;
    }

    break;

  default:;
  }
  return NO_PRESS;
}

void init_hw_io()
{

  pinMode(PUSH_SW, INPUT);
  pinMode(SW_KNOB_A, INPUT);
  pinMode(SW_KNOB_B, INPUT);
  /*pinMode(PUMP1_PIN, OUTPUT);
  pinMode(PUMP2_PIN, OUTPUT);
  pinMode(PUMP3_PIN, OUTPUT);
  pinMode(PUMP4_PIN, OUTPUT); */

  // initialize lcd to 20x4
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
}

void beep_on()
{
  uint8_t gpio_A_data_ON[2] = {0x13, 0x01};
  HAL_I2C_Master_Transmit(&hi2c2, MCP23017_ADDRESS << 1, gpio_A_data_ON, 2, 200);
}

void beep_off()
{
  uint8_t gpio_A_data_OFF[2] = {0x13, 0x00};
  HAL_I2C_Master_Transmit(&hi2c2, MCP23017_ADDRESS << 1, gpio_A_data_OFF, 2, 200);
}

void init_mcp23107()
{
  uint8_t gpio_A_dir[2] = {0x00, 0xFE};
  uint8_t gpio_A_data[2] = {0x12, 0x00};
  uint8_t gpio_B_dir[2] = {0x01, 0xFE};
  uint8_t gpio_B_data[2] = {0x13, 0x00};

  HAL_I2C_Master_Transmit(&hi2c2, 0x40, gpio_A_dir, 2, 200);
  HAL_I2C_Master_Transmit(&hi2c2, 0x40, gpio_A_data, 2, 200);
  HAL_I2C_Master_Transmit(&hi2c2, 0x40, gpio_B_dir, 2, 200);
  HAL_I2C_Master_Transmit(&hi2c2, 0x40, gpio_B_data, 2, 200);
}

HAL_StatusTypeDef init_ADS1115IDGST()
{
  unsigned char ADSwrite[6];
  HAL_StatusTypeDef status;
  // Set pointer to config resister
  ADSwrite[0] = 0x01;
  // Start single convertion & AINP=AI0 AINN=AIN1 , +/-6.114VDC & single conversion mode
  ADSwrite[1] = 0b10000001;
  // 128 sampling/second
  ADSwrite[2] = 0b10000011;

  status = HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 3, 100);
  return status;
}

int16_t read_raw_pH()
{
  unsigned char ADSwrite[6];
  int16_t reading;
  // Set pointer address to configured resistor
  ADSwrite[0] = 0x01;
  // Start single convertion & AINP=AI0 AINN=AIN1 , +/-6.114VDC & single conversion mode
  ADSwrite[1] = 0b10000001;
  // 128 sampling/second
  ADSwrite[2] = 0b10000011;
  HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 3, 100);

  // Set pointer address to ADC register
  ADSwrite[0] = 0x00;
  HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 1, 100);
  HAL_Delay(20);
  HAL_I2C_Master_Receive(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 2, 100);
  reading = (ADSwrite[0] << 8 | ADSwrite[1]);
  return reading;
}

int16_t read_raw_temperature()
{
  unsigned char ADSwrite[6];
  int16_t reading;
  HAL_StatusTypeDef status;
  // Set pointer address to configured resistor
  ADSwrite[0] = 0x01;
  // Start single convertion & AINP=AI1 AINN=GND , +/-6.114VDC & single conversion mode
  ADSwrite[1] = 0b11100001;
  // 128 sampling/second
  ADSwrite[2] = 0b10000011;
  status = HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 3, 100);
  Serial.printf("I2C1:%d\n", status);

  // Set pointer address to ADC register
  ADSwrite[0] = 0x00;
  status = HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 1, 100);
  Serial.printf("I2C2:%d\n", status);
  HAL_Delay(20);
  status = HAL_I2C_Master_Receive(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 2, 100);
  Serial.printf("I2C3:%d\n", status);
  reading = (ADSwrite[0] << 8 | ADSwrite[1]);
  return reading;
}

void test()
{
  unsigned char ADSwrite[6];
  int16_t reading;
  float voltage[4];
  const float voltageConv = 6.114 / 32768.0;
  char buff[20];
  HAL_StatusTypeDef status;
  for (int i = 0; i < 4; i++)
  {
    ADSwrite[0] = 0x01;

    switch (i)
    {
    case (0):
      ADSwrite[1] = 0xC1; //11000001
      break;
    case (1):
      ADSwrite[1] = 0xD1; //11010001
      break;
    case (2):
      ADSwrite[1] = 0xE1;
      break;
    case (3):
      ADSwrite[1] = 0xF1;
      break;
    }

    ADSwrite[2] = 0x83; //10000011 LSB

    status = HAL_I2C_Master_Transmit(&hi2c2, 0x90, ADSwrite, 3, 100);
    Serial.printf("1:%d\n", status);
    ADSwrite[0] = 0x00;
    status = HAL_I2C_Master_Transmit(&hi2c2, 0x90, ADSwrite, 1, 100);
    Serial.printf("2:%d\n", status);
    HAL_Delay(20);

    status = HAL_I2C_Master_Receive(&hi2c2, 0x90, ADSwrite, 2, 100);
    Serial.printf("3:%d\n", status);
    reading = (ADSwrite[0] << 8 | ADSwrite[1]);
    if (reading < 0)
    {
      reading = 0;
    }
    voltage[i] = reading * voltageConv;
    dtostrf(voltage[i], 5, 3, buff);
    Serial.printf("%s\n", buff);
  }
}

void setup()
{
  // put your setup code here, to run once:

  init_hw_io();

  pinMode(PC13, OUTPUT);
  pinMode(PB0, INPUT_ANALOG);
  pinMode(PB1, INPUT_ANALOG);

  //HAL_Init();  // Not neccessary

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_TIM1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  // TIM1_CH1 PA8
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  // TIM2_CH1 PA0
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  // TIM3_CH1 PA6
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  Serial.printf("Hey1\n");
  //__HAL_RCC_AFIO_CLK_ENABLE();

  __HAL_RCC_I2C2_CLK_ENABLE();

  RCC->APB1RSTR |= 0x00400000; // Reset i2c peripheral
  RCC->APB1RSTR &= 0xFFBFFFFF;
  hi2c2 = I2C_HandleTypeDef();
  hi2c2.Instance = I2C2;

  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  //hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.OwnAddress2 = 0;

  HAL_StatusTypeDef jj = HAL_I2C_Init(&hi2c2);
  Serial.printf("Hey2\n");

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.Period = 0xFFFF;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.Period = 0xFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.Period = 0xFFFF;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_TIM_Base_Init(&htim1);
  HAL_TIM_Base_Init(&htim2);
  HAL_TIM_Base_Init(&htim3);

  TIM_ClockConfigTypeDef sClockSourceConfig;
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_TI1;
  sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_RISING;
  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  sClockSourceConfig.ClockFilter = 0;
  HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  __HAL_TIM_SET_COUNTER(&htim3, 0);
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim3);

  timer4 = new HardwareTimer(TIM4);
  timer4->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PB6);
  timer4->setOverflow(50, MICROSEC_FORMAT);                // 100000 microseconds = 100 milliseconds
  timer4->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT); // 50%
  timer4->setMode(2, TIMER_OUTPUT_COMPARE_PWM1, PB7);
  timer4->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT); // 50%
  timer4->setMode(3, TIMER_OUTPUT_COMPARE_PWM1, PB8);
  timer4->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT); // 50%
  timer4->setMode(4, TIMER_OUTPUT_COMPARE_PWM1, PB9);
  timer4->setCaptureCompare(4, 0, PERCENT_COMPARE_FORMAT); // 50%
  timer4->resume();

  init_mcp23107();
  init_menu();
  display_menu(current_menu);

  beep_on();
  HAL_Delay(500);
  beep_off();

  // HAL_StatusTypeDef status = init_ADS1115IDGST();

  // Serial.printf("I2C ADS1115IDGST:%d\n", status);
  Serial.printf("jj:%d\n", jj);
  HAL_Delay(3000);
  //HAL_StatusTypeDef mm = HAL_I2C_IsDeviceReady(&hi2c2, ADS1115_ADDRESS, 1, 200);
  // Serial.printf("mm:%d\n", mm);
  //HAL_Delay(3000);

  /* while(1)
  {
     uint32_t analog=analogRead(PB0);
     Serial.printf("adc:%d\n",analog);
     HAL_Delay(500);
  } */

  /*while (1)
  {
    test();
   
    HAL_Delay(500);
  } */
}

void loop()
{

  // put your main code here, to run repeatedly:

  while (1)
  {
    int inc = knob_read();
    if (inc != 0)
    {
      inc_menu(current_menu, inc);
      display_menu(current_menu);
    }

    int sw = read_SW();
    if (sw == SHORT_PRESS)
    {
      Menu *cur_submenu = get_selected_submenu();
      // If it is not leaf submenu
      if (cur_submenu->num_submenus > 0)
      {

        current_menu = cur_submenu;

        display_menu(current_menu);
      }
      // If it is the leaf submenu
      else if (cur_submenu->num_submenus == 0)
      {
        if (cur_submenu->command != NULL)
        {

          cur_submenu->command(cur_submenu);
          display_menu(current_menu);
        }
      }
    }
  }
}

/*char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}*/