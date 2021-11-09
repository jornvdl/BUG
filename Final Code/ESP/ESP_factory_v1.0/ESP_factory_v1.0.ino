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
  //start the Neopixels and BleKeyboard
  bleKeyboard.begin();
  pixels.begin();

  //configure the pins 
  pinMode(buttonPin, INPUT); //set the buttonpin as pulldown
  pinMode(confPin, INPUT);   //set the confpin as pulldown
  pinMode(readyPin, OUTPUT); //set the ready pin as output

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


  //Check for updates from the PC/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (*bleKeyboard.keySetBLE()) {//Check for a keybind update
    TimeSleep = millis();        //reset sleep timing    
    factsettings = false;        //disable factory settings mode
    bleKeyboard.rstKeyFlag();    //reset the KEY flag
  }

  if (*bleKeyboard.setFactory()){//Check if PC sent factory senttings
    n = 0;                                  //start keyloop back at default
    factsettings = true;                    //device in factory settings
    bleKeyboard.rstFactory();               //reset the factory settings flag
    bleKeyboard.rstUpdate();                //reset the update flag
    bleKeyboard.setColour(&KeyFact[n][1]);  //reset the LED colour to factory settings
  }

  

  //Check if the device has been on for longer than the timeout value/////////////////////////////////////////////////////////////////////////////////
  if ((millis()/1000 - TimeSleep/1000) > *bleKeyboard.getTimeout()) {
     LEDsoff();
     digitalWrite(readyPin,LOW);
     MemoryStore(n);
     esp_deep_sleep_start();    //set the BUG to deep sleep
  }



  //Configuration button Behavior/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
    TimePressed = millis();     //start conf button press duration timer
    TimeSleep = millis();       //reset the sleep timer
    LastConfState = HIGH;       //set last conf state to HIGH
  }

  if(LastConfState == HIGH && digitalRead(confPin) == HIGH) {  //While the conf button is pressed 
    //Turn off pixel to indicate that if the button is released at that time the BUG will go into deep sleep
    while((millis() - TimePressed) > SleepPress && (millis() - TimePressed) < LongPress && digitalRead(confPin) == HIGH) {
      LEDsoff();            //turn off the LEDs
      LastConfState = HIGH; 
    }
    //Have all the pixels blink to indicate the gamepad will reset to factory setting if the button is released
    if((millis() - TimePressed) > LongPress) {
      LEDsBlink();          //blink the pixels
      LastConfState = HIGH;
    }
  }

  if(LastConfState == HIGH && digitalRead(confPin) == LOW) { // button is released
    TimeReleased = millis();    //store the button release time
    LastConfState = LOW;        //set the last conf state to LOW
  }

  long pressDuration = TimeReleased - TimePressed;  //calculate the duration of the configuration button press

  //if the button is pressed for less than 3 seconds the button will cycle through the factory keys
  if( pressDuration < ShortPress && pressDuration > 0 && factsettings && (millis() - recentPress) > 500) {
    n = n+1;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    confUpdate = true;
    recentPress = millis();     //store the press time for debouncing
    if(n > 4) {
      n = 0;
    }  
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
    MemoryStore(n);
    esp_deep_sleep_start();     //start deepsleep
  }
  //check if the button was prssed long enough for factory settings mode
  if (pressDuration > LongPress) {
    n = 0;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    bleKeyboard.setColour(&KeyFact[n][1]);    //set the colour to factory settings
    confUpdate = true;
    factsettings = true;
  }



  //Factory setting library updates///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (factsettings) {
    bleKeyboard.setKey(&KeyFact[n][0]);     //set the key to factory settings
    bleKeyboard.setLayout(&KeyFact[n][4]);  //set the LED layout to factory settings
  }


  //The Button press/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
    bleKeyboard.press();    //continuously send a spacebar when button is pressed
    LastState = HIGH;       //set last state to high
    TimeSleep = millis();   //reset the sleep timer
  }
  if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
    bleKeyboard.releaseAll();  //stop sending the spacebar when the button is released
    LastState = LOW;           //set the last buttonstate to LOW
  }

  //LED updates/bluetooth connectivity///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (bleKeyboard.isConnected() && (*bleKeyboard.isUpdated()||confUpdate||startup) ) {
      confUpdate = false;
      startup = false;
    if (*bleKeyboard.isUpdated()) {
      timeDeepSleep = *bleKeyboard.getTimeout();
      TimeSleep = millis();       //reset sleep timing
      bleKeyboard.rstUpdate();    //reset the update flag
    }
      //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
      //neo pixels: top = 0, left = 1, down = 2, right = 3;
      LEDupdate();

  }
  else if (!(bleKeyboard.isConnected())) {
      BLEdisconnected();
  }
}
