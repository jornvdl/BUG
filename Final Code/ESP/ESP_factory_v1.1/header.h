#ifndef _HEADERFILE_H    // Put these two lines at the top of your file.
#define _HEADERFILE_H    // (Use a suitable name, usually based on the file name.)

#define buttonPin   19  //set the buttonpin   19 final 18 prototype
#define confPin     2   //set the conf button pin   2 final 5 prototype
#define NEOPIN      1   //set the pin for the neopixels   1 final 19 prototype
#define NUMPIXELS   4   //set the amount of neopixels
#define readyPin    4   //set ready pin as 4
#define BatteryPin  0


#endif // _HEADERFILE_H    // Put this line at the end of your file.


//Define char for space arrow up, down, left, and right
char space = 32;
char arrowup = 218;
char arrowdown = 217;
char arrowleft = 216;
char arrowright = 215;
char w = 119;
char a = 97;
char s = 115;
char d = 100;

//factory setting keypress, colour and layout
int KeyFact[5][5] = {{arrowup, 0x22, 0xA0, 0xFF, 0x01},
                      {arrowleft, 0x22, 0xA0, 0xFF, 0x02},
                      {arrowdown, 0x22, 0xA0, 0xFF, 0x04},        
                      {arrowright, 0x22, 0xA0, 0xFF, 0x08},         
                      {space, 0x22, 0xA0, 0xFF, 0x0E}};
//initialise LED binary array
int LEDbin[] = {0,0,0,0};

//Factory setting key+layout and colour arrays
bool memKeys[5] = {1,1,1,1,1};
int factColour[3] = {0x22, 0xA0, 0xFF};
int factArrowup[2] = {218, 0x01};
int factArrowleft[2] = {216, 0x02};
int factArrowdown[2] = {217, 0x04};
int factArrowright[2] = {215, 0x08};
int factSpace[2] = {32, 0x0E};
int factW[2] = {119,0x01};
int factA[2] = {97,0x02};
int factS[2] = {115,0x04};
int factD[2] = {100,0x08};
int *null = NULL;

//initilisation for buttonpress timings and debounce of the configuration button
const int ShortPress = 3000; //short press shorter than 3000 milliseconds
const int LongPress = 7000;  //long press longer than 7000 miliseconds
const int SleepPress = 3000; //Sleep press inbetween long and short

int LastState = LOW;
int CurrentConfState;
int LastConfState = LOW;

//General variables
int keybind = 0x20;
int colour_main[3] = {0x22, 0xA0, 0xFF};
int layout_main = 0x0E;
int timeDeepSleep = 300;
int n = 0; 
int m = 0;
int keys[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}};


unsigned long TimePressed = 0;
unsigned long TimeReleased = 0;
unsigned long TimeSleep = 0;
unsigned long recentPress = 0;
unsigned long blinktimeon = 0;
unsigned long blinktimeoff = 0;

bool factsettings = true;
bool confUpdate = false;
bool startup = false;
bool customKey = false;
