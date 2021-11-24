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
#define flashTime     600

// Configuration button variables
#define debounceTime  500   // in millis
#define shutdownTime  3000  // in millis
#define factoryTime   7000  // in millis

// Factory settings variables
const int  factSleep     = 300;                  // in seconds
const int  factColour[3] = {0x22, 0xA0, 0xFF};   // R,G,B values
const int  factMode[5]   = {1,1,1,1,0};          // 0 disabled, 1: ↑←↓→␣, 2: WASD␣
const int  factConf      = 0;                    // Start value of confSelect. Range [0,4]
const bool factWASD      = false;

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

const int keyArrows[5]  = {keyUp, keyLeft, keyDown, keyRight, keySpace};
const int keyWASD[5]    = {keyW,  keyA,    keyS,    keyD,     keySpace};
const int keyLayout[5]  = {0x01,  0x02,    0x04,    0x08,     0xE};

////////////////////////////// Global variables //////////////////////////////
// Mode select
int confSelect;

#endif // _VARIABLES_H