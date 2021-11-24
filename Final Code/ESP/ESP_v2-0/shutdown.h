#ifndef _SHUTDOWN_H
#define _SHUTDOWN_H
#include "memory.h"

void shutdown(int n, int factsettings){
  Ledsoff();                  //Turn Leds off
  digitalWrite(rdyPin,LOW);   //Set the readyPin low
  lib2memory();               //Memory storage
  esp_deep_sleep_start();     //Set the ESP to deep sleep
}

#endif // _SHUTDOWN_H
