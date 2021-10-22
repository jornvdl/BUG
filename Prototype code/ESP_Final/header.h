#ifndef _HEADERFILE_H    // Put these two lines at the top of your file.
#define _HEADERFILE_H    // (Use a suitable name, usually based on the file name.)

#define buttonPin   18  //set the buttonpin
#define confPin     5   //set the conf button pin
#define NEOPIN      19  //set the pin for the neopixels
#define NUMPIXELS    5  //set the amount of neopixels
#define WHITE       255, 255, 255 //set the rgb value for white
#define BLUE        0, 0, 255     //set the rgb value for blue
#define RED         255, 0, 0     //set the rgb value for red
#define GREEN       0, 255, 0     //set the rgb value for green
#define PURPLE      255, 0, 255   //set the rgb value for purple
#define OFF         0, 0, 0       //set the rgb value for OFF

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

char KeyCycle[] = {w, a, s, d};
int LEDbin[] = {0,0,0,0};

//select the desired key and colour
#define key          arrowup
//#define colour       GREEN
int LED = 0x0;
  



//Rotation at press of conf button
const int ShortPress = 3000; //short press shorter than 1000 milliseconds
const int LongPress = 7000;  //long press longer than 3000 miliseconds
const int SleepPress = 3000;
int LastState = LOW;
int CurrentConfState;
int LastConfState = LOW;
unsigned long TimePressed = 0;
unsigned long TimeReleased = 0;
int n = 0;
unsigned long TimeSleep = 0;
bool factsettings = false;
