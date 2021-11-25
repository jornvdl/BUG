/*
 * 
 */

#define USE_NIMBLE
#define debug 1       // Set to 1 to enable serial debug information. Baudrate = 115200

#include <BleKeyboardGATT.h>
#include <Adafruit_NeoPixel.h>

// Import custom libraries
#include "variables.h"
#include "init.h"
#include "factory.h"
#include "led.h"
#include "battery.h"
#include "btn.h"
#include "shutdown.h"
#include "conf.h"

// setup() is run once at start up
void setup() {
  initSystem();
  sleepTimer = millis();
}

// loop() is looped after completion of the setup() function.
//  in this function, the main loop is implemented.
void loop() {
  if (bleKeyboard.isConnected()) {
    ledsOn();                // Enable LEDs
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
        if (debug) Serial.println("Sleeptimer reset requested from library");
        sleepTimer = millis();
        ledsOn();
        batterySend();
        bleKeyboard.flgRstTimer(false);
      }

      // Factory reset requested over BLE
      if (*bleKeyboard.flgRstBUG()) {
        if (debug) Serial.println("Reset BUG from BLE flag.");
        factory();
      }

      // Identify BUG
      if (*bleKeyboard.flgIdentify()) {
        ledsBlink(true, false);
      }

      // Shutdown if to long inactivity
      int timeLived = millis() - sleepTimer;
      if (timeLived > *bleKeyboard.getTimeout()) {
        if (debug) Serial.println("Sleeptimer exceeded!");
        shutdown();
      }
    }
  } 

  else { // !bleKeyboard.isConnected()

    while(!bleKeyboard.isConnected()) {
      // Let the LEDs blink
      ledsBlink(false, true);

      // React to a configuration press
      if (digitalRead(confPin)) {
        sleepTimer = millis();
        confPress();
      }

      // Shutdown if to long inactivity
      int timeLived = millis()/1000 - sleepTimer;
      if (timeLived > *bleKeyboard.getTimeout()) {
        if (debug) Serial.println("Sleeptimer exceeded!");
        shutdown();
      }
    }
  }
}
