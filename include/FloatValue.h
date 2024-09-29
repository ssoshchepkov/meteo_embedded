#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#ifndef floatvalue_h
#define floatvalue_h


class FloatValue {
  public:
    
    FloatValue(byte col, byte row, float (*func)(), const char* postfix = NULL);
    void print(LiquidCrystal_I2C* lcd) const;
    void update_value();

private:
    byte _col, _row;
    float _value;
    float (*_func)();
    const char *_postfix = NULL;
};

#endif