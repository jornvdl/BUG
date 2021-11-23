

/*
 * Title: ESP Factory code
 * Authors: Floris van der Heijde, Jorn van der Linden
 * Institution: Delft University of Technology
 * Date: 2021/11/08
 */
#define USE_NIMBLE
#include "header.h"
#include <BleKeyboardGATT.h>
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>

#define debug 1

//Set the BUG name
BleKeyboard bleKeyboard("BUGsy");
//Set the memory system as preferences
Preferences preferences;
//Initialise the Neopixels as "pixels"
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 //Time in milliseconds to pause between pixels
//Include the functions header
#include "functions.h"

void setup() {
  // put your setup code here, to run once:
  if (debug) Serial.begin(115200);
  //start the Neopixels and BleKeyboard
  bleKeyboard.begin();
  pixels.begin();

  //configure the pins 
  pinMode(buttonPin, INPUT); //set the buttonpin as pulldown
  pinMode(confPin, INPUT);   //set the confpin as pulldown
  pinMode(readyPin, OUTPUT); //set the ready pin as output
  pinMode(BatteryPin, INPUT); //set the battery pin as input

  //pull the configurations variables from flash memory
  MemoryPull();

  //intialise the blekeyboard library values and flags
  keyboard_initialise();

  //Start the required timers
  TimeSleep = millis();
  blinktimeoff = millis();
  blinktimeon = millis();
  startup = true; //set startup to true

  digitalWrite(readyPin,HIGH); //Set the ready pin to high to ensure functionality of the Conf button and the LEDs
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //check the array of keybind options
  keyArrayUpdate();
  //Check for updates from the PC/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (customKey == true) {//Check for a keybind update
    TimeSleep = millis();        //reset sleep timing    
    factsettings = false;        //disable factory settings mode
    customKey = false;
  }

  if (*bleKeyboard.flgRstBUG()){//Check if PC sent factory senttings
    n = 0;                                  //start keyloop back at default
    factsettings = true;                    //device in factory settings
    bleKeyboard.flgRstBUG(false);               //reset the factory settings flag
    bleKeyboard.flgRstTimer(false);                //reset the update flag
    bleKeyboard.setColour(&KeyFact[n][1]);  //reset the LED colour to factory settings
  }

  

  //Check if the device has been on for longer than the timeout value/////////////////////////////////////////////////////////////////////////////////
  if ((millis()/1000 - TimeSleep/1000) > *bleKeyboard.getTimeout()) {
     LEDsoff();
     digitalWrite(readyPin,LOW);
     MemoryStore(n,factsettings);
     esp_deep_sleep_start();    //set the BUG to deep sleep
  }



  //Configuration button Behavior/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
    if (debug) Serial.println("Conf button is pressed!");
    TimePressed = millis();     //start conf button press duration timer
    TimeSleep = millis();       //reset the sleep timer
    LastConfState = HIGH;       //set last conf state to HIGH
  }

  if(LastConfState == HIGH && digitalRead(confPin) == HIGH) {  //While the conf button is pressed 
    //Turn off pixel to indicate that if the button is released at that time the BUG will go into deep sleep
    while((millis() - TimePressed) > SleepPress && (millis() - TimePressed) < LongPress && digitalRead(confPin) == HIGH) {
      if (debug) Serial.println("Confbtn > 3s!");
      LEDsoff();            //turn off the LEDs
      LastConfState = HIGH; 
    }
    //Have all the pixels blink to indicate the gamepad will reset to factory setting if the button is released
    if((millis() - TimePressed) > LongPress) {
      if (debug) Serial.println("Confbtn > 7s!");
      LEDsBlink();          //blink the pixels
      LastConfState = HIGH;
    }
  }

  if(LastConfState == HIGH && digitalRead(confPin) == LOW) { // button is released
    if (debug) Serial.println("Conf button is released!");
    TimeReleased = millis();    //store the button release time
    LastConfState = LOW;        //set the last conf state to LOW
  }

  long pressDuration = TimeReleased - TimePressed;  //calculate the duration of the configuration button press

  //if the button is pressed for less than 3 seconds the button will cycle through the factory keys
  if( pressDuration < ShortPress && pressDuration > 0 && factsettings && (millis() - recentPress) > 500) {
    n++;
    if(n > 4) n=0;
    if (debug) Serial.print("New n value (before null-check). n=");
    if (debug) Serial.println(n);
    while(Keys[n] == NULL) {
      if (debug) Serial.print("Keys[n] == NULL! (Inside new n value!) n=");
      if (debug) Serial.println(n);
      n++;
      if(n > 4) n=0;
    }
    if (debug) Serial.print("New n value (after null-check).  n=");
    if (debug) Serial.println(n);
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    confUpdate = true;
    recentPress = millis();     //store the press time for debouncing
  }

  //check if the conf button was pressed more than 0.5 seconds ago to ensure it is a new press
  if (millis() - recentPress > 500) {//software debounce
    recentPress = 0;            //reset the recent press time
  }

  //check if the conf press duration was in the sleep time window 
  if( pressDuration > SleepPress && pressDuration < LongPress) {
    LEDsoff();
    bleKeyboard.end();
    digitalWrite(readyPin, LOW);
    MemoryStore(n,factsettings);
    esp_deep_sleep_start();     //start deepsleep
  }
  //check if the button was prssed long enough for factory settings mode
  if (pressDuration > LongPress) {
    n = 0;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    bleKeyboard.setColour(&factColour[0]);    //set the colour to factory settings
    confUpdate = true;
    factsettings = true;
  }



  //Factory setting library updates///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (factsettings) {
    while(Keys[n] == NULL) n++;
    bleKeyboard.setKeybind(Keys[n]);     //set the key to factory settings
    bleKeyboard.setLayout(Keys[n]+1);  //set the LED layout to factory settings
  }


  //The Button press/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
    bleKeyboard.press();    //continuously send a spacebar when button is pressed
    if (debug) Serial.println("The button is pressed!");
    LastState = HIGH;       //set last state to high
    TimeSleep = millis();   //reset the sleep timer
  }
  if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
    bleKeyboard.releaseAll();  //stop sending the spacebar when the button is released
    if (debug) Serial.println("The button is pressed!");
    LastState = LOW;           //set the last buttonstate to LOW
  }

  //LED updates/bluetooth connectivity///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (bleKeyboard.isConnected() && (*bleKeyboard.flgRstTimer()||confUpdate||startup) ) {
    confUpdate = false;
    startup = false;
    if (*bleKeyboard.flgRstTimer()) {
      timeDeepSleep = *bleKeyboard.getTimeout();
      TimeSleep = millis();       //reset sleep timing
      bleKeyboard.flgRstTimer(false);    //reset the update flag
    }
    //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
    //neo pixels: top = 0, left = 1, down = 2, right = 3;
    LEDupdate();
    Batterypercentage();
    Serial.print(analogRead(BatteryPin));
    Serial.print("\n");
  }
  else if (!(bleKeyboard.isConnected())) {
      BLEdisconnected();
  }
}
