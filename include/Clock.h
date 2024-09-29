#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

#ifndef clock_h
#define clock_h

class ClockValue;

enum ClockParts { Hour, Minute, Second };

class Clock {

    public: 
        Clock(byte col, byte row, bool big_font = false);

        void display_template(LiquidCrystal_I2C* lcd) const;
        void display(LiquidCrystal_I2C* lcd) const;
        void update(RTCDateTime* date_time);
        void fill(RTCDateTime* date_time);
        ClockValue* getPart(ClockParts part) const;

        ~Clock();

    private:
        byte _col, _row;
        bool _big_font;
        ClockValue *_hour, *_minute, *_second;
};

#endif