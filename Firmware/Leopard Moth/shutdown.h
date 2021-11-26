/*
 *  Function to handle shutdown protocol for a correct shutdown.
 */

#ifndef _SHUTDOWN_H
#define _SHUTDOWN_H
#include "memory.h"

void shutdown() {
  if (debug) Serial.println("Shutting down! Turning LEDs off and writing memory...");
  ledsOff();                  //Turn Leds off
  lib2memory();               //Memory storage
  delay(50);
  digitalWrite(rdyPin,LOW);   //Set the readyPin low
  esp_deep_sleep_start();     //Set the ESP to deep sleep
}

#endif // _SHUTDOWN_H
