#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <messenger.hpp>

enum DRAW_TYPE
{
   RAW_SCAN = 0x00,
} typedef DRAW_TYPE;

class OLED
{
public:
   OLED(TwoWire *wire, Messenger *msg);
   ~OLED();

   void showLIDARScan(float *scan);
   void startupAnimation();
   void pixelToXY(float distance, float angle, float scaling, uint16_t *x, uint16_t *y);
   float calculateScaling(float *scan, DRAW_TYPE);

private:
   const static uint16_t _HEIGHT = 64;
   const static uint16_t _WIDTH = 128;
   const static uint8_t _adddress = 0x3C;

   Adafruit_SSD1306 *_display;
   Messenger *_msg;
};