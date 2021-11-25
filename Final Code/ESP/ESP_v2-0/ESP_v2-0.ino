/*
 * 
 */

#define USE_NIMBLE
#define debug 1       // Set to 1 to enable serial debug information. Baudrate = 115200

#include <BleKeyboardGATT.h>
#include <Adafruit_NeoPixel.h>

// Import custom libraries
#include "variables.h"
#include "flags.h"
#include "init.h"
#include "factory.h"
#include "led.h"
#include "btn.h"
#include "shutdown.h"
#include "conf.h"

// setup() is run once at start up
void setup() {
  initSystem();
  sleeptimer = millis();
}

// loop() is looped after completion of the setup() function.
//  in this function, the main loop is implemented.
void loop() {
  if (bleKeyboard.isConnected()) {
    ledOn();                // Enable LEDs
    sleepTimer = millis();  // Reset sleeptimer

    while(bleKeyboard.isConnected()) {
      // React to a button press
      if (digitalRead(btnPin)) {
        sleepTimer = millis();
        btnPress();
      } 

      // React to a configuration press
      if (digitalRead(confPin)) {
        sleepTimer = millis();
        confPress();
      } 

      // Sleeptimer restart requested, so BLE char updated
      if (*bleKeyboard.flgRstTimer()) {
        sleepTimer = millis();
        ledOn();
        bleKeyboard.flgRstTimer(false);
      }

      // Factory reset requested over BLE
      if (*bleKeyboard.flgRstBUG()) {
        factory();
      }

      // Shutdown if to long inactivity
      int timeLived = millis() - sleepTimer;
      if (timeLived > *bleKeyboard.getTimeout()) {
        if (debug) Serial.println("Sleeptimer exceeded!")
        shutdown();
      }
    }
  } 

  else { // !bleKeyboard.isConnected()
    bleDisconnected();

    while(!bleKeyboard.isConnected()) {
      // React to a configuration press
      if (digitalRead(confPin)) {
        sleepTimer = millis();
        confPress();
      }

      // Shutdown if to long inactivity
      int timeLived = millis() - sleepTimer;
      if (timeLived > *bleKeyboard.getTimeout()) {
        if (debug) Serial.println("Sleeptimer exceeded!")
        shutdown();
      }
    }
  }
}
