#ifndef _VARIABLES_H
#define _VARIABLES_H

/////////////////////////// Definitions and values ///////////////////////////
// Device Info
#define deviceName    "BUGsy"
#define manufacturer  "Espressif"

// Pin declarations
#define btnPin        19
#define confPin       2
#define ledPin        1
#define rdyPin        4
#define batPin        0

// Led configuration variables
#define numLeds       4
#define blinkTime     600
int blinkColour[3]  = {0x0, 0x0, 0xFF};

// Configuration button variables
#define debounceTime  500   // in millis
#define shutdownTime  3000  // in millis
#define factoryTime   7000  // in millis

// Factory settings variables
int  factSleep     = 300;                  // in seconds
int  factColour[3] = {0x22, 0xA0, 0xFF};   // R,G,B values
bool factMode[5]   = {1,1,1,1,0};          // 0 disabled, 1: ↑←↓→␣, 2: WASD␣
int  factConf      = 0;                    // Start value of confSelect. Range [0,4]
bool factWASD      = false;

// Keybind arrays and corresponding layout
#define keyRight      215
#define keyLeft       216
#define keyDown       217
#define keyUp         218
#define keyW          119
#define keyA          97
#define keyS          115
#define keyD          100
#define keySpace      32

int keyArrows[5]  = {keyUp, keyLeft, keyDown, keyRight, keySpace};
int keyWASD[5]    = {keyW,  keyA,    keyS,    keyD,     keySpace};
int keyLayout[5]  = {0x01,  0x02,    0x04,    0x08,     0xE};

// Battery percentage variables equation in battery.h
float a = 0.00005;
float b = 0.002;
float c = 3.1787;

////////////////////////////// Global variables //////////////////////////////
// Classes from libraries
BleKeyboard       bleKeyboard(deviceName, manufacturer);
Adafruit_NeoPixel leds(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

// Mode select
int confSelect;

// Timers
volatile long sleepTimer;

#endif // _VARIABLES_H
