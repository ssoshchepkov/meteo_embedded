#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include "ClockValue.h"
#include "Clock.h"

Clock::Clock(byte col, byte row, bool big_font) {
    _big_font = big_font;
    _col = col;
    _row = row;
    _hour = new ClockValue(23, col, row, big_font);
    _minute = new ClockValue(59, col + (big_font ? BIG_FONT_WIDTH : 1) * 2 + 1, row, big_font);
    _second = new ClockValue(59, col + (big_font ? BIG_FONT_WIDTH : 1) * 4 + 2, row, big_font);
}

void Clock::display_template(LiquidCrystal_I2C* lcd) const {
    if (_big_font) {
        lcd->setCursor(_col + BIG_FONT_WIDTH * 2, _row);
        lcd->print(".");
        lcd->setCursor(_col + BIG_FONT_WIDTH * 4 + 1, _row);
        lcd->print(".");
        lcd->setCursor(_col + BIG_FONT_WIDTH * 2, _row + 1);
        lcd->print(".");
        lcd->setCursor(_col + BIG_FONT_WIDTH * 4 + 1, _row + 1);
        lcd->print(".");

    } else {
        lcd->setCursor(_col + 2, _row);
        lcd->print(":");
        lcd->setCursor(_col + 5, _row);
        lcd->print(":");
    }
}

void Clock::display(LiquidCrystal_I2C* lcd) const {
    _hour->print(lcd);
    _minute->print(lcd);
    _second->print(lcd);
}

void Clock::update(RTCDateTime* date_time) {
    _hour->_value = date_time->hour;
    _minute->_value = date_time->minute;
    _second->_value = date_time->second;
}

void Clock::fill(RTCDateTime* date_time) {
    date_time->hour = _hour->_value;
    date_time->minute = _minute->_value;
    date_time->second = _second->_value;
}

ClockValue* Clock::getPart(ClockParts part) const {
    switch (part)
    {
        case ClockParts::Hour:
            return _hour;
        case ClockParts::Minute:
            return _minute;
        case ClockParts::Second:
            return _second;
        default:
            return NULL;
    }
}

Clock::~Clock() {
    delete _hour;
    delete _minute;
    delete _second;
}

