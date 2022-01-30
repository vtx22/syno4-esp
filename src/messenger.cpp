#include "messenger.hpp"

Messenger::Messenger(DEBUG_LEVEL level) : _debugLvl(level)
{
}

void Messenger::sendErrorMSG(String message)
{
   if (_debugLvl != ERRORS_ONLY && _debugLvl != ERRORS_WARNINGS && _debugLvl != ALL)
   {
      return;
   }
}

void Messenger::sendDebugMSG(String message)
{
   if (_debugLvl != ALL)
   {
      return;
   }
}