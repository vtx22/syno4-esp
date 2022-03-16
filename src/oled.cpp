//https://wokwi.com/arduino/projects/322861520670163540

#include "oled.hpp"

#define DEG2RAD (PI / 180.f)

OLED::OLED(TwoWire *wire, Messenger *msg) : _msg(msg)
{
   _display = new Adafruit_SSD1306(_WIDTH, _HEIGHT, wire, -1);

   uint8_t tryCNT = 0;
   while (!_display->begin(SSD1306_SWITCHCAPVCC, _adddress))
   {
      _msg->sendDebugMSG("Connecting to Display...");
      tryCNT++;
      if (tryCNT > 5)
      {
         while (true)
         {
            _msg->sendErrorMSG("COULD NOT CONNECT TO DISPLAY!");
            delay(1000);
         }
      }
      delay(500);
   }

   startupAnimation();
}

void OLED::startupAnimation()
{
   _display->clearDisplay();
   delay(500);
}

float OLED::calculateScaling(float *scan, DRAW_TYPE drawType)
{
   float maxDistance = 0;
   for (int i = 0; i < 360; i++)
   {
      if (scan[i] > maxDistance)
      {
         maxDistance = scan[i];
      }
   }

   if (drawType == RAW_SCAN)
   {
      return _HEIGHT / (2.f * maxDistance);
   }
}

void OLED::pixelToXY(float distance, float angle, float scaling, uint16_t *x, uint16_t *y)
{
   *x = 0;
   *y = 0;

   const uint16_t cW = _WIDTH / 2;
   const uint16_t cH = _HEIGHT / 2;

   if (angle >= 0 && angle <= 90)
   {
      float xLength = sin(angle * DEG2RAD) * distance;
      float yLength = cos(angle * DEG2RAD) * distance;

      *x = cW - xLength * scaling;
      *y = cH - yLength * scaling;
      return;
   }
   if (angle > 90 && angle <= 180)
   {
      angle -= 90;
      float xLength = cos(angle * DEG2RAD) * distance;
      float yLength = sin(angle * DEG2RAD) * distance;

      *x = cW - xLength * scaling;
      *y = cH + yLength * scaling;
      return;
   }
   if (angle > 180 && angle <= 270)
   {
      angle -= 180;
      float xLength = sin(angle * DEG2RAD) * distance;
      float yLength = cos(angle * DEG2RAD) * distance;

      *x = cW + xLength * scaling;
      *y = cH + yLength * scaling;
      return;
   }
   if (angle > 270 && angle <= 359)
   {
      angle -= 270;
      float xLength = cos(angle * DEG2RAD) * distance;
      float yLength = sin(angle * DEG2RAD) * distance;

      *x = cW + xLength * scaling;
      *y = cH - yLength * scaling;
      return;
   }
}

//Shows a LIDAR scan on the OLED
//scan: data array of distances to every angle = 360° / points, first element is drive direction, then CCW
//points: number of points in scan (points have to be equally spaced)
void OLED::showLIDARScan(float *scan)
{
   for (uint16_t i = 0; i < 360; i++)
   {
      uint16_t x, y;
      pixelToXY(scan[i], i, calculateScaling(scan, RAW_SCAN), &x, &y);

      _display->drawPixel(x, y, WHITE);
   }
   //=============================================

   _display->display();
}