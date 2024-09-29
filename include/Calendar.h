#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>

#ifndef calendar_h
#define calendar_h

class ClockValue;

enum CalendarParts { Date, Month, Year };

class Calendar {

    public: 
        Calendar(byte col, byte row);

        void display_template(LiquidCrystal_I2C* lcd) const;
        void display(LiquidCrystal_I2C* lcd) const;
        void update(RTCDateTime* date_time);
        void fill(RTCDateTime* date_time);
        ClockValue* getPart(CalendarParts part) const;

        ~Calendar();

    private:
        byte _col, _row;    
        ClockValue *_date, *_month, *_year;
};

#endif