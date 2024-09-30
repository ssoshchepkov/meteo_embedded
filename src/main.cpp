#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <DS3231.h>
#include <Thinary_AHT10.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h> 

#include <BMP085.h>

#include "header.h"

float get_pressure();
float get_outside_temp();

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

DS3231 real_time_clock;
AHT10Class AHT10;

OneWire oneWire(A1);// вход датчика 18b20
DallasTemperature dallas_temperature(&oneWire);

BMP085 dps = BMP085();

unsigned long last_sensor_query_time;

Clock clock_view(0, 0, true);
Calendar calendar_view(1, 2);

FloatValue humidity(1, 3, 0.0, 99.9, [] { return AHT10.GetHumidity(); }, "%");
FloatValue pressure(7, 3, 0.0, 999.9, get_pressure);
FloatValue temp_inside(13, 2, -99.9, 99.9, [] { return AHT10.GetTemperature(); }, "\337C");
FloatValue temp_outside(13, 3, -99.9, 99.9, get_outside_temp, "\337C");

void setup() {
  pinMode(EDIT_NEXT_PARAM_BUTTON, INPUT_PULLUP);
  pinMode(INC_PARAM_BUTTON, INPUT_PULLUP);
  pinMode(DEC_PARAM_BUTTON, INPUT_PULLUP);

  pinMode(BRIGHTNESS_OUTPUT_PIN, OUTPUT); // яркость

  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  create_big_font_characters(&lcd);

  Wire.begin(); // Join i2c bus

  AHT10.begin();

  real_time_clock.begin();
  dps.init();
  dallas_temperature.begin();
  dallas_temperature.setResolution(10);

  clock_view.display_template(&lcd);
  calendar_view.display_template(&lcd);

  update_date_time_view();
  update_sensor_data_view();
}

void loop() {

  set_auto_brightness();

  // ОПРОС ДАТЧИКОВ КАЖДЫЕ 5 СЕК
  if(millis() - last_sensor_query_time > SENSOR_QUERY_DELAY_MSEC) {
    update_sensor_data_view();
    last_sensor_query_time = millis();
  }

  if(button_pressed(EDIT_NEXT_PARAM_BUTTON)) {
      edit_parameters();
      save_clock_data();
      delay(200);
    }

    update_date_time_view();

    delay(50);
}

void update_sensor_data_view() {
  humidity.update_value();
  temp_inside.update_value();
  pressure.update_value();
  temp_outside.update_value();

  humidity.print(&lcd);
  pressure.print(&lcd);
  temp_inside.print(&lcd);
  temp_outside.print(&lcd);
}

void update_date_time_view() {
    RTCDateTime current_date_time = real_time_clock.getDateTime();  
    calendar_view.update(&current_date_time);
    clock_view.update(&current_date_time);

    clock_view.display(&lcd);
    calendar_view.display(&lcd);
}
 //автоматичекая яркость дисплея
void set_auto_brightness() {
    int brightness = (1024 - analogRead(0)) / 4;
    analogWrite(BRIGHTNESS_OUTPUT_PIN, brightness);
}

void delay_with_break_by_button() {
  byte j = 0;
  while(j < 10 && !button_pressed(EDIT_NEXT_PARAM_BUTTON) && !button_pressed(INC_PARAM_BUTTON) && !button_pressed(DEC_PARAM_BUTTON)) {
    j++;
    delay(25);
  }
}

void edit_parameters() {
  edit_parameter(clock_view.getPart(ClockParts::Hour));
  edit_parameter(clock_view.getPart(ClockParts::Minute));
  edit_parameter(calendar_view.getPart(CalendarParts::Date));
  edit_parameter(calendar_view.getPart(CalendarParts::Month));
  edit_parameter(calendar_view.getPart(CalendarParts::Year));
}

void edit_parameter(ClockValue* parameter) {

  while(button_pressed(EDIT_NEXT_PARAM_BUTTON)); // Wait until edit button released

  while(true) {

    while(button_pressed(INC_PARAM_BUTTON)) {
      parameter->inc();
      parameter->print(&lcd);
      delay(200);
    }
    while(button_pressed(DEC_PARAM_BUTTON)) {
      parameter->dec();
      parameter->print(&lcd);
      delay(200);
    }
    parameter->print_blank(&lcd);
    delay_with_break_by_button();
    parameter->print(&lcd);
    delay_with_break_by_button();

    if(button_pressed(EDIT_NEXT_PARAM_BUTTON)) {
      return;
    }
  }
}
 
void save_clock_data() {
  RTCDateTime current;
  calendar_view.fill(&current);
  clock_view.fill(&current);
  real_time_clock.setDateTime(current.year, current.month, current.day, current.hour, current.minute, 0);
}

float get_pressure() {
  int32_t pascal_pressure = 0;
  dps.getPressure(&pascal_pressure); 
  return pascal_to_mmhg(pascal_pressure);
}

float get_outside_temp() { 
  dallas_temperature.requestTemperatures();
  return dallas_temperature.getTempCByIndex(0);
}