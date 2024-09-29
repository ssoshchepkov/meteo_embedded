#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include "ClockValue.h"
#include "Calendar.h"

Calendar::Calendar(byte col, byte row) {
    _col = col;
    _row = row;
    _date = new ClockValue(31, col, row);
    _month = new ClockValue(12, col + 3, row);
    _year = new ClockValue(99, col + 8, row);
}

void Calendar::display_template(LiquidCrystal_I2C* lcd) const {
    lcd->setCursor(_col + 2, _row);
    lcd->print("-  -20");   
}

void Calendar::display(LiquidCrystal_I2C* lcd) const {
    _date->print(lcd);
    _month->print(lcd);
    _year->print(lcd);
}

void Calendar::update(RTCDateTime* date_time) {
    _year->_value = date_time->year % 100;
    _month->_value = date_time->month;
    _date->_value = date_time->day;
}

void Calendar::fill(RTCDateTime* date_time) {
    date_time->year = _year->_value + 2000;
    date_time->month = _month->_value;
    date_time->day = _date->_value;
}

ClockValue* Calendar::getPart(CalendarParts part) const {
    switch (part)
    {
        case CalendarParts::Date:
            return _date;
        case CalendarParts::Month:
            return _month;
        case CalendarParts::Year:
            return _year;
        default:
            return NULL;
    }
}

Calendar::~Calendar() {
    delete _date;
    delete _month;
    delete _year;
}

