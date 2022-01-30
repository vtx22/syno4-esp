#include "oled.hpp"

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

//Shows a LIDAR scan on the OLED
//scan: data array of distances to every angle = 360° / points, first element is drive direction, then CCW
//points: number of points in scan (points have to be equally spaced)
void OLED::showLIDARScan(float *scan, int points)
{
   float maxDistance = 0;
   int maxDistanceIndex;

   //Find maximum distance for map scaling
   for (int i = 0; i < points; i++)
   {
      if (scan[i] > maxDistance)
      {
         maxDistance = scan[i];
         maxDistanceIndex = i;
      }
   }

   _display->clearDisplay();
   //Draw Center Point
   uint16_t cW = _WIDTH / 2;
   uint16_t cH = _HEIGHT / 2;

   _display->drawPixel(cW, cH, WHITE);
   _display->drawPixel(cW - 1, cH, WHITE);
   _display->drawPixel(cW - 1, cH - 1, WHITE);
   _display->drawPixel(cW, cH - 1, WHITE);

   //        a
   //   |========|
   // b |        | d
   //   |========|
   //       c

   //Find longest distance for every side of the rectangle around the scan-shape

   //Calculate angles for assigned side - TODO
   int angleLongSide = 120;
   int angleShortSide = 180 - angleLongSide;

   //Working for a
   float maxDisA = 0;
   float maxDisC = 0;

   //Find max distance from center axis for angles 0 - 60
   for (int i = 0; i <= angleLongSide / 2; i++) // 0 - 60
   {
      float distance = sin((90 - i) * PI / 180.f) * scan[i];
      if (maxDisA < distance)
      {
         maxDisA = distance;
      }
   }
   //Find max distance from center axis for angles 359 - 300
   for (int i = 0; i < angleLongSide / 2; i++) // 0 - 59
   {
      float distance = sin((90 - i - 1) * PI / 180.f) * scan[359 - i];
      if (maxDisA < distance)
      {
         maxDisA = distance;
      }
   }

   //=============================================

   float maxDisB = 0;
   float maxDisD = 0;

   for (int i = angleLongSide / 2; i < 90; i++)
   {
      float distance =
   }

   _display->display();
}