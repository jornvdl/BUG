/*
 * Title: ESP Factory code
 * Authors: Floris van der Heijde, Jorn van der Linden
 * Institution: Delft University of Technology
 * Date: 2021/22/01
 */

#include "header.h"
#include "functions.h"
#include <BleKeyboardGATT.h>
#include <Adafruit_NeoPixel.h>

//Set the BUG name
BleKeyboard bleKeyboard("BUGsy");;

//Initialise the Neopixels as "pixels"
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 //Time in milliseconds to pause between pixels

void setup() {
  // Setup code, runs once
  Serial.begin(115200);
  bleKeyboard.begin();
  pixels.begin();
  
  pinMode(buttonPin, INPUT); //set the buttonpin as pulldown
  pinMode(confPin, INPUT);   //set the confpin as pulldown
  pinMode(readyPin, OUTPUT);                 //set the ready pin as output
  //Initialise the LED colour, Layout, and the keybinding.
  int colour[3] = {0xFF, 0xFE, 0xFD}; //random vars
  int layout = 0x0F;  // 16, all on
  int keybind = 0x20; //space
  int timeout = 300;
  
  bleKeyboard.setTimeout(&timeout);
  bleKeyboard.setKey(&keybind);
  bleKeyboard.setColour(&colour[0]);
  bleKeyboard.setLayout(&layout);
  bleKeyboard.rstUpdate();
  bleKeyboard.rstFactory();
  bleKeyboard.rstKeyFlag();
  TimeSleep = millis();
  blinktimeoff = millis();
  blinktimeon = millis();

}

void loop() {
  //Main code runs repeatedly
  //
  digitalWrite(readyPin,HIGH);
  //check if the BUG has received an update from the computer
  
  //check if the BUG has received a new keybinding
  if (*bleKeyboard.keySetBLE()) {
    TimeSleep = millis();        //reset sleep timing    
    factsettings = false;        //disable factory settings mode
    bleKeyboard.rstKeyFlag();    //reset the KEY flag
  }

  //Check if the last activity was more than 5 min ago 
  if ((millis()/1000 - TimeSleep/1000) > *bleKeyboard.getTimeout()) {
     pixels.clear();            //clear the neopixels 
     pixels.show();             //update the neopixels
     digitalWrite(readyPin,LOW);
     esp_deep_sleep_start();    //set the BUG to deep sleep
  }


  int layout = *bleKeyboard.getLayout();
  int colour[3] = {*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)};
  //convert hexadecimal layout to binary
  LEDbin[0] = *layout_hextobin(layout);
  LEDbin[1] = *(layout_hextobin(layout)+1);
  LEDbin[2] = *(layout_hextobin(layout)+2);
  LEDbin[3] = *(layout_hextobin(layout)+3);

  

  //Check if the device has been set to factory settings via the PC
  if (*bleKeyboard.setFactory()){
    n = 0;                                  //start keyloop back at default
    factsettings = true;                    //device in factory settings
    bleKeyboard.rstFactory();               //reset the factory settings flag
    bleKeyboard.rstUpdate();                //reset the update flag
    bleKeyboard.setColour(&KeyFact[n][1]);  //reset the LED colour to factory settings
  }
  
  //if the device is in factory settings
  if (factsettings) {
    bleKeyboard.setKey(&KeyFact[n][0]);     //set the key to factory settings
    bleKeyboard.setLayout(&KeyFact[n][4]);  //set the LED layout to factory settings
  }


  //Button Behaviour
  
  //The Button press
  if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
    bleKeyboard.press();    //continuously send a spacebar when button is pressed
    LastState = HIGH;       //set last state to high
    TimeSleep = millis();   //reset the sleep timer
    Serial.print("pressed");
  }
  if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
    bleKeyboard.releaseAll();  //stop sending the spacebar when the button is released
    LastState = LOW;           //set the last buttonstate to LOW
  }
  
  //The configuration button response
  if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
    TimePressed = millis();     //start conf button press duration timer
    LastConfState = HIGH;       //set last conf state to HIGH
    TimeSleep = millis();       //reset the sleep timer
    }
    
  //While the conf button is continously pressed 
  if(LastConfState == HIGH && digitalRead(confPin) == HIGH) {
    //Turn off pixel to indicate that if the button is released at that time the BUG will go into deep sleep
    while((millis() - TimePressed) > SleepPress && (millis() - TimePressed) < LongPress && digitalRead(confPin) == HIGH) {
      pixels.clear();
      pixels.show();
      LastConfState = HIGH;
    }
    //Have all the pixels blink to indicate the gamepad will reset to factory setting if the button is released
    if((millis() - TimePressed) > LongPress) {
      pixels.fill(pixels.Color(colour[0],colour[1],colour[2]),0,5);
      pixels.show();
      delay(500);
      pixels.clear();
      pixels.show();
      delay(500);
      LastConfState = HIGH;
      factsettings = true;
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
  if (millis() - recentPress > 500) {
    recentPress = 0;            //reset the recent press time
  }
  //check if the conf press duration was in the sleep time window 
  if( pressDuration > SleepPress && pressDuration < LongPress) {
    pixels.clear();             //reset the neopixels
    pixels.show();              //update the neopixels
    bleKeyboard.end();
    digitalWrite(readyPin, LOW);
    esp_deep_sleep_start();     //start deepsleep
  }
  //check if the button was prssed long enough for factory settings mode
  if (pressDuration > LongPress) {
    n = 0;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    bleKeyboard.setColour(&KeyFact[n][1]);    //set the colour to factory settings
    //bleKeyboard.end();
    //bleKeyboard.begin();
  }

  if (bleKeyboard.isConnected() && (*bleKeyboard.isUpdated()||confUpdate) ) {
      confUpdate = false;

    if (*bleKeyboard.isUpdated()) {
      TimeSleep = millis();       //reset sleep timing
      bleKeyboard.rstUpdate();    //reset the update flag
    }
      //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
      //neo pixels: top = 0, left = 1, down = 2, right = 3;
      if (LEDbin[0] == 1) {
      //pixels.clear();
      pixels.setPixelColor(3, pixels.Color(colour[0],colour[1],colour[2]));
      }
      else {
      //pixels.clear();
      pixels.setPixelColor(3, pixels.Color(OFF));
      }
      if (LEDbin[1] == 1) {
      pixels.setPixelColor(2, pixels.Color(colour[0],colour[1],colour[2]));
      }
      else {
      pixels.setPixelColor(2, pixels.Color(OFF));
      }
      if (LEDbin[2] == 1) {
      pixels.setPixelColor(1, pixels.Color(colour[0],colour[1],colour[2]));
      }
      else {
      pixels.setPixelColor(1, pixels.Color(OFF));
      }
      if (LEDbin[3] == 1) {
      pixels.setPixelColor(0, pixels.Color(colour[0],colour[1],colour[2]));
      pixels.show();
      }
      else {
      pixels.setPixelColor(0, pixels.Color(OFF));
      pixels.show();
      }
  }
  else if (not(bleKeyboard.isConnected())) {
    if (millis() - blinktimeoff > 300 && millis() - blinktimeon > 600) {
       if (LEDbin[0] == 1) {
        //pixels.clear();
        pixels.setPixelColor(3, pixels.Color(0,0,200));
       }
       else {
        //pixels.clear();
        pixels.setPixelColor(3, pixels.Color(OFF));
       }
       if (LEDbin[1] == 1) {
        pixels.setPixelColor(2, pixels.Color(0,0,200));
       }
       else {
        pixels.setPixelColor(2, pixels.Color(OFF));
       }
       if (LEDbin[2] == 1) {
        pixels.setPixelColor(1, pixels.Color(0,0,200));
       }
       else {
        pixels.setPixelColor(1, pixels.Color(OFF));
       }
       if (LEDbin[3] == 1) {
        pixels.setPixelColor(0, pixels.Color(0,0,200));
        pixels.show();
        blinktimeon = millis();
       }
       else {
        pixels.setPixelColor(0, pixels.Color(OFF));
        pixels.show();
        blinktimeon = millis();
       }
    }
    else if (millis() - blinktimeon > 300 && millis() - blinktimeoff > 600) {
       pixels.clear();
       pixels.show();
       blinktimeoff = millis();
    }
    
  }





  
}
