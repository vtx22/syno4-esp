#pragma once
#include <Arduino.h>

enum DEBUG_LEVEL
{
   NONE = 0x00,
   ERRORS_ONLY,
   ERRORS_WARNINGS,
   ALL,

} typedef DEBUG_LEVEL;

class Messenger
{
public:
   Messenger(DEBUG_LEVEL level);
   ~Messenger();

   void sendErrorMSG(String message);
   void sendDebugMSG(String message);

   void setDebugLevel(DEBUG_LEVEL level) { _debugLvl = level; };

private:
   DEBUG_LEVEL _debugLvl = ALL;
};