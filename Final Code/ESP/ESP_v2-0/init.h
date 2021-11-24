/* Initialization header
 *  All initializations will be done here. 
 */

#ifndef _INIT_H
#define _INIT_H

#include "memory.h"

BleKeyboard bleKeyboard(deviceName, manufacturer);



void initSystem() {
  // Enable debug output over serial
  if (debug) Serial.begin(115200);

  bleKeyboard.begin();
  leds.begin();

  // Configure GPIO pins
  pinMode(btnPin,  INPUT);
  pinMode(confPin, INPUT);
  pinMode(batPin,  INPUT);
  pinMode(rdyPin,  OUTPUT);

  // Get data from memory and set to library
  memory2lib();

  // Start sleeptimer

  digitalWrite(rdyPin, HIGH);
}


#endif // _INIT_H
