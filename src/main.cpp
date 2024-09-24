#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "header.h"

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);  // Устанавливаем дисплей


char Time[]     = "TIME:  :  :  ";
char Calendar[] = "DATE:  /  /20  ";
ClockValue second(59, 11, 0), minute(59, 8, 0), hour(23, 5, 0), date(31, 5, 1), month(12, 8, 1), year(99, 13, 1);

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  Wire.begin(); // Join i2c bus
}

void loop() {
  if(button_pressed(BUTTON1_PIN)) {
      edit_parameters();
      save_clock_data();
      delay(200);
    }

    read_clock_data();
    display_date_time();
    delay(50);
}

void display_date_time() {

  hour.write_to_str(Time);
  minute.write_to_str(Time);
  second.write_to_str(Time);

  date.write_to_str(Calendar);
  month.write_to_str(Calendar);
  year.write_to_str(Calendar);
 
  lcd.setCursor(0,0);
  lcd.print(Time);
  lcd.setCursor(0,1);
  lcd.print(Calendar);
}

void delay_with_break_by_button() {
  byte j = 0;
  while(j < 10 && !button_pressed(BUTTON1_PIN) && !button_pressed(BUTTON2_PIN) && !button_pressed(BUTTON3_PIN)) {
    j++;
    delay(25);
  }
}

inline bool button_pressed(uint8_t button_pin) {
  return !digitalRead(button_pin);
}

void edit_parameters() {
  edit_parameter(&hour);
  edit_parameter(&minute);
  edit_parameter(&date);
  edit_parameter(&month);
  edit_parameter(&year);
}

void edit_parameter(ClockValue* parameter) {
  char text_buffer[3];

  while(button_pressed(BUTTON1_PIN));              // Wait until button 1 released

  while(true) {

    while(button_pressed(BUTTON2_PIN)) {                      // If button 2 is pressed
      parameter->inc();
      parameter->print(&lcd, text_buffer);
      delay(200);                                // Wait 200ms
    }
    while(button_pressed(BUTTON3_PIN)) {
      parameter->dec();
      parameter->print(&lcd, text_buffer);
      delay(200);                                // Wait 200ms
    }
    parameter->print_blank(&lcd);
    delay_with_break_by_button();
    parameter->print(&lcd, text_buffer);
    delay_with_break_by_button();

    if(button_pressed(BUTTON1_PIN)) {
      return;                          // Return parameter value and exit
    }
  }

}
 
void save_clock_data() {
  // Write data to DS1307 RTC
  Wire.beginTransmission(CLOCK_ADDR);               // Start I2C protocol with DS1307 address
  Wire.write(0);                              // Send register address
  Wire.write(0);                              // Reset sesonds and start oscillator
  minute.write_to_wire(&Wire);
  hour.write_to_wire(&Wire);
  Wire.write(1);                              // Write day (not used)
  date.write_to_wire(&Wire);
  month.write_to_wire(&Wire);
  year.write_to_wire(&Wire);
  Wire.endTransmission();                     // Stop transmission and release the I2C bus
}

void read_clock_data() {
  Wire.beginTransmission(CLOCK_ADDR);                 // Start I2C protocol with DS1307 address
  Wire.write(0);                                // Send register address
  Wire.endTransmission(false);                  // I2C restart
  Wire.requestFrom(CLOCK_ADDR, 7);                    // Request 7 bytes from DS1307 and release I2C bus at end of reading
  second.read_from_wire(&Wire);                  // Read seconds from register 0
  minute.read_from_wire(&Wire);                  // Read minuts from register 1
  hour.read_from_wire(&Wire);                    // Read from register 2
  Wire.read();                                  // Read day from register 3 (not used)
  date.read_from_wire(&Wire);                         // Read from register 4
  month.read_from_wire(&Wire);                         // Read from register 5
  year.read_from_wire(&Wire);                         // Read from register 6
}