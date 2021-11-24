/*
 * 
 */

#define USE_NIMBLE
#define debug 1       // Set to 1 to enable serial debug information. Baudrate = 115200

#include <BleKeyboard.h>

// Import custom libraries
#include "variables.h"
#include "flags.h"
#include "init.h"
#include "factory.h"
#include "led.h"
#include "btn.h"
#include "shutdown.h"
#include "conf.h"



// Move next two lines to led.h
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel leds(numLeds, ledPin, NEO_GRB + NEO_KHZ800);



void setup() {
  
}

void loop() {
  
}
