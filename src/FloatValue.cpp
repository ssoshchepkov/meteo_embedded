#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FloatValue.h"

FloatValue::FloatValue(byte col, byte row, float min, float max, float (*func)(), const char* postfix) {
    _col = col;
    _row = row;
    _min = min;
    _max = max;
    _func = func;
    _postfix = postfix;

    _max_len = (min < 0) ? 3 : 2;

    int x = int(max(abs(_min), abs(_max)));

    do
    {
        x /= 10;
        _max_len += 1;
    } while (x);
    if(_postfix) {
        _max_len += strlen(_postfix);
    }

}

void FloatValue::print(LiquidCrystal_I2C* lcd) const {
    clear_view(lcd);

    lcd->setCursor(_col, _row);
    if((_value < _min) || (_value > _max)) {
        lcd->print("ERR!");
    } else {
        lcd->print(_value, 1);
        if(_postfix) {
            lcd->print(_postfix);
        }
    }
}

void FloatValue::update_value() {
    _value = _func();
}

void FloatValue::clear_view(LiquidCrystal_I2C* lcd) const {
    lcd->setCursor(_col, _row);
    for(int i = 0; i < _max_len; i += 1) lcd->print(' ');
}

   
