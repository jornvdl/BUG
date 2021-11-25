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
}

// loop() is looped after completion of the setup() function.
//  in this function, the main loop is implemented.
void loop() {
  
}
