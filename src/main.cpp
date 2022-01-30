// Software for SYNO4 - ESP8266 Software
//
// 02/2022

#include <Arduino.h>
#include <Wire.h>

#include "oled.hpp"

OLED *display;
Messenger *msg;

float scanData[360]; //Stores a full LIDAR scan, distance in m for every angle from 0 - 360°

void setup()
{
   Wire.setClock(400000);
   Wire.begin();
   msg = new Messenger(ALL);
   display = new OLED(&Wire, msg);
}

void loop()
{
   // put your main code here, to run repeatedly:
}
