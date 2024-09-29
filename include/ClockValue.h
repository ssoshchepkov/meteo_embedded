#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Calendar.h"
#include "Clock.h"

#ifndef clockvalue_h
#define clockvalue_h

#define BIG_FONT_HEIGHT 2
#define BIG_FONT_WIDTH 3

class ClockValue {
  public:
    
  ClockValue(byte max_value, byte col, byte row, bool big_font = false);

    void inc();
    void dec();

    void print(LiquidCrystal_I2C* lcd) const;
    void print_blank(LiquidCrystal_I2C* lcd) const;

private:
    byte _max_value;
    byte _col, _row;
    byte _value;
    bool _big_font;

    void display_big_digit(byte value, byte col, byte row, LiquidCrystal_I2C* lcd) const;

    friend void Clock::update(RTCDateTime* date_time);
    friend void Clock::fill(RTCDateTime* date_time);
    friend void Calendar::update(RTCDateTime* date_time);
    friend void Calendar::fill(RTCDateTime* date_time);
};

#endif