#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <messenger.hpp>
#include <math.h>

class OLED
{
public:
   OLED(TwoWire *wire, Messenger *msg);
   ~OLED();

   void showLIDARScan(float *scan, int points);
   void startupAnimation();

private:
   const static uint16_t _HEIGHT = 64;
   const static uint16_t _WIDTH = 128;
   const static uint8_t _adddress = 0x3C;

   Adafruit_SSD1306 *_display;
   Messenger *_msg;
};