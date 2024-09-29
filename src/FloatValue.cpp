#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FloatValue.h"

FloatValue::FloatValue(byte col, byte row, float (*func)(), const char* postfix) {
    _col = col;
    _row = row;
    _func = func;
    _postfix = postfix;
}

void FloatValue::print(LiquidCrystal_I2C* lcd) const {
    lcd->setCursor(_col, _row);
    lcd->print(_value, 1);
    if(_postfix) {
        lcd->print(_postfix);
    }
}

void FloatValue::update_value() {
    _value = _func();
}

   
