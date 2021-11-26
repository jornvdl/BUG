/*  Initialization header
 *  All initializations will be done here. 
 */

#ifndef _INIT_H
#define _INIT_H

#include "memory.h"


void initSystem() {
  // Enable debug output over serial
  if (debug) Serial.begin(115200);
  if (debug) Serial.println("Debug serial started.");

  // Start BLE Keyboard server and LED controller
  bleKeyboard.begin();
  leds.begin();

  // Configure GPIO pins
  pinMode(btnPin,  INPUT);
  pinMode(confPin, INPUT);
  pinMode(batPin,  INPUT);
  pinMode(rdyPin,  OUTPUT);

  // Get data from memory and set to library
  memory2lib();   
  if (debug) Serial.println("Memory read and written to lib.");

  bleKeyboard.flgIdentify(false);

  digitalWrite(rdyPin, HIGH);
}


#endif // _INIT_H
