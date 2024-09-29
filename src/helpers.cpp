#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "header.h"

void create_big_font_characters(LiquidCrystal_I2C* display) {
  byte v1[8] = {
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111,
    0b00111
  };
  byte v2[8] = {
    0b00111,
    0b00111,
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000
  };
  byte v3[8] = { 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000,
    0b00000,
    0b11111,
    0b11111
  };
  byte v4[8] = {
    0b11111,
    0b11111, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b11111,
    0b11111
  };
  byte v5[8] = { 
    0b11100,
    0b11100,  
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b11100,
    0b11100
  };
  byte v6[8] = {
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100
  };
  byte v7[8] = { 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000,
    0b00000, 
    0b00000,
    0b00111, 
    0b00111
  };
  byte v8[8] = {
    0b11111, 
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000, 
    0b00000
  };

  display->createChar(1, v1);
  display->createChar(2, v2);
  display->createChar(3, v3);
  display->createChar(4, v4);
  display->createChar(5, v5);
  display->createChar(6, v6);
  display->createChar(7, v7);
  display->createChar(8, v8);
}