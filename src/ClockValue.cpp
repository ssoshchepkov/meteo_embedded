#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ClockValue.h"

  ClockValue::ClockValue(byte max_value, byte col, byte row, bool big_font) {
    _max_value = max_value;
    _col = col;
    _row = row;
    _big_font = big_font;
  }

    void ClockValue::inc() {
        _value = (_value == _max_value) ? 0 : _value + 1;
    }

    void ClockValue::dec() {
        _value = !_value ? _max_value : _value - 1;
    }

     void ClockValue::print(LiquidCrystal_I2C* lcd) const {

        if(!_big_font) {
            lcd->setCursor(_col, _row);
            lcd->print(_value / 10);
            lcd->print(_value % 10);
        }else {
            display_big_digit(_value / 10, _col, _row, lcd);
            display_big_digit(_value % 10, _col + BIG_FONT_WIDTH, _row, lcd);
        }
    }

    void ClockValue::print_blank(LiquidCrystal_I2C* lcd) const {
        lcd->setCursor(_col, _row);
        lcd->print("  ");

        if(_big_font) {
            lcd->print("    ");
            lcd->setCursor(_col, _row + 1);
            lcd->print("      ");
        }
    }

    void ClockValue::display_big_digit(byte value, byte col, byte row, LiquidCrystal_I2C* lcd) const {
        byte d1,d2,d3,d4,d5,d6;

        switch(value){
            case 0: d1=1,d2=8,d3=6,
                    d4=1,d5=3,d6=6;
                    break;
            case 1: d1=32,d2=2,d3=6,
                    d4=32,d5=32,d6=6;
                    break;
            case 2: d1=2,d2=8,d3=6,
                    d4=1,d5=4,d6=5;
                    break;
            case 3: d1=2,d2=4,d3=6,
                    d4=7,d5=3,d6=6;
                    break;
            case 4: d1=1,d2=3,d3=6,
                    d4=32,d5=32,d6=6;
                    break;
            case 5: d1=1,d2=4,d3=5,
                    d4=7,d5=3,d6=6;
                    break;
            case 6: d1=1,d2=4,d3=5,
                    d4=1,d5=3,d6=6;
                    break;
            case 7: d1=1,d2=8,d3=6,
                    d4=32,d5=32,d6=6;
                    break;
            case 8: d1=1,d2=4,d3=6,
                    d4=1,d5=3,d6=6;
                    break;
            case 9: d1=1,d2=4,d3=6,
                    d4=7,d5=3,d6=6;
                    break;
        }

        lcd->setCursor(col, row);
        lcd->write((uint8_t)d1);
        lcd->setCursor(col + 1, row);
        lcd->write((uint8_t)d2);
        lcd->setCursor(col + 2, row);
        lcd->write((uint8_t)d3);

        lcd->setCursor(col, row + 1);
        lcd->write((uint8_t)d4);
        lcd->setCursor(col + 1, row + 1);
        lcd->write((uint8_t)d5);
        lcd->setCursor(col + 2, row + 1);
        lcd->write((uint8_t)d6);
    }