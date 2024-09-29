#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "ClockValue.h"
#include "Clock.h"
#include "Calendar.h"
#include "FloatValue.h"

#ifndef meteo_embedded_h
#define meteo_embedded_h

void update_date_time_view();
void save_clock_data();
void edit_parameters();
void delay_with_break_by_button();
void edit_parameter(ClockValue* parameter);
void set_auto_brightness();
void update_sensor_data_view();

void create_big_font_characters(LiquidCrystal_I2C* display);

inline bool button_pressed(uint8_t button_pin) {
  return !digitalRead(button_pin);
}

// перевод паскалей в мм ртутного столба
inline float pascal_to_mmhg(float p) {
  return p / 133.3;
}

#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

#define CLOCK_ADDR 0x68

#define EDIT_NEXT_PARAM_BUTTON 8 // button1 is connected to pin 8
#define INC_PARAM_BUTTON 9 // button2 is connected to pin 9
#define DEC_PARAM_BUTTON 10

#define BRIGHTNESS_OUTPUT_PIN 11

#define SENSOR_QUERY_DELAY_MSEC 5000 // время смены показаний датчиков

#endif