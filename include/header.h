#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#ifndef meteo_embedded_h
#define meteo_embedded_h

#define ASCII_0_CODE 48

class ClockValue {
  public:
    
  ClockValue(byte max_value, byte col, byte row) {
    _max_value = max_value;
    _col = col;
    _row = row;
  }

  void read_from_wire(TwoWire* wire) {
    _value = bcd_to_decimal(wire->read());    
  }

  void write_to_wire(TwoWire* wire) {
    wire->write(decimal_to_bcd(_value));   
  }

    void inc() {
        _value = (_value == _max_value) ? 0 : _value + 1;
    }

    void dec() {
        _value = !_value ? _max_value : _value - 1;
    }

    void print(LiquidCrystal_I2C* lcd, char* buffer) {
        sprintf(buffer,"%02u", _value);
        lcd->setCursor(_col, _row);
        lcd->print(buffer);
    }

    void print_blank(LiquidCrystal_I2C* lcd) {
        lcd->setCursor(_col, _row);
        lcd->print("  ");
    }

    void write_to_str(char* s) {
        s[_col] = _value / 10 + ASCII_0_CODE;
        s[_col + 1] = _value % 10 + ASCII_0_CODE;
    }

  private:
    byte _max_value;
    byte _col, _row;
    byte _value;

    // Convert BCD to decimal
    inline byte bcd_to_decimal(byte val) {
        return (val >> 4) * 10 + (val & 0x0F);
    }

    // Convert decimal to BCD        
    inline byte decimal_to_bcd(byte val) {
        return ((val / 10) << 4) + (val % 10);
    }
};

void display_date_time();
void read_clock_data();
void save_clock_data();
void edit_parameters();
void delay_with_break_by_button();
bool button_pressed(uint8_t button_pin);
void edit_parameter(ClockValue* parameter);

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define CLOCK_ADDR 0x68

#define BUTTON1_PIN 8 // button1 is connected to pin 8
#define BUTTON2_PIN 9 // button2 is connected to pin 9
#define BUTTON3_PIN 10

#endif