/*
@Title BUG ESP Final code including gatt protocol
@Authors Floris van der Heijde, Jorn van der Linden
@Delft University of Technology
@Date 21/10/2021

Button pin 18 pulldown
Neopixel data pin 19 pulldown
Conf button pin 5 pulldown

*/
#include "header.h"
#include <Preferences.h>
#include <BleKeyboardGATT.h>
#include <Adafruit_NeoPixel.h>

//Set name of bluetooth keyboard
BleKeyboard bleKeyboard("GAMER-BUG", "FvdH JvdL KvR");

Preferences preferences;

//Initialise the neopixels as pixels
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time in milliseconds to pause between pixels

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  bleKeyboard.begin();
  pixels.begin();

  // Get preferences from EEPROM flash memory. Store data using preferences.begin("bug_data", false) and preferences.putInt("..", value)
  preferences.begin("bug_data", true);
  int keybind = preferences.getInt("key", 0x20);
  int colour[3] = {preferences.getInt("cRed", 0x0F), preferences.getInt("cGreen", 0x0E), preferences.getInt("cBlue", 0x0D)};
  int layout = preferences.getInt("layout", 0x0E);
  int timeout = preferences.getInt("timeout", 300);
  preferences.end();
  
  pinMode(buttonPin, INPUT_PULLDOWN);
  pinMode(confPin, INPUT_PULLDOWN);
  
//  int colour[3] = {0x0F, 0x0E, 0x0D}; //random vars
//  int layout = 0x0F;  // 16, all on
//  int keybind = 0x20; //space
//  int timeout = 300;
  
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
    if (*bleKeyboard.isUpdated()) {
      factsettings = false;
      TimeSleep = millis();
      bleKeyboard.rstUpdate();
    }
  
    if (*bleKeyboard.keySetBLE()) {
     factsettings = false;
     bleKeyboard.rstKeyFlag();
    }
    
    if ((millis()/1000 - TimeSleep/1000) > *bleKeyboard.getTimeout()) {
       pixels.clear();
       pixels.show();
       bleKeyboard.end();
       esp_deep_sleep_start();
    }

  bleKeyboard.setBatteryLevel(70);

  
   int layout = *bleKeyboard.getLayout();
    int colour[3] = {*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)};
    //LED layout hexadecimal to binary
      //LED hexadecimal to binary
    if (layout < 0x8) {
      LEDbin[0] = 0;
      if (layout < 0x4) {
        LEDbin[1] = 0;
        if (layout < 0x2) {
          LEDbin[2] = 0;
          if (layout == 0x0) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
        else {
          LEDbin[2] = 1;
          if (layout > 0x2) {
            LEDbin[3] = 1;
          }
          else {
            LEDbin[3] = 0;
          }
        }
      }
      else {
        LEDbin[1] = 1;
        if (layout < 0x6) {
          LEDbin[2] = 0;
          if (layout == 0x4) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
        else {
          LEDbin[2] = 1;
          if (layout == 0x6) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
      }
    }
    else {
      
      LEDbin[0] = 1;
      if (layout < 0xC) {
        LEDbin[1] = 0;
        if (layout < 0xA) {
          LEDbin[2] = 0;
          if (layout == 0x8) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
        else {
          LEDbin[2] = 1;
          if (layout == 0xA) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
      }
      else {
        LEDbin[1] = 1;
        if (layout < 0xE) {
          LEDbin[2] = 0;
          if (layout == 0xC) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
        else {
          LEDbin[2] = 1;
          if (layout == 0xE) {
            LEDbin[3] = 0;
          }
          else {
            LEDbin[3] = 1;
          }
        }
      }
    }

        //Check if the device has been set to factory settings
    if (*bleKeyboard.setFactory()){
      n = 0;
      factsettings = true;
      bleKeyboard.rstFactory();
      bleKeyboard.rstUpdate();
      bleKeyboard.setColour(&KeyFact[n][1]);
    }
  
    if (factsettings) {
      bleKeyboard.setKey(&KeyFact[n][0]);
  
      bleKeyboard.setLayout(&KeyFact[n][4]);
    }
  
  
  
    //The Button press
    if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
      bleKeyboard.press(); //continuously send a spacebar when button is pressed
      LastState = HIGH;       //set last state to high
      TimeSleep = millis();
    }
    if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
      bleKeyboard.releaseAll();  //stop sending the spacebar when the button is released
      LastState = LOW;
    }
    //The configuration button response
    if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
      TimePressed = millis();
      LastConfState = HIGH;
      TimeSleep = millis();
      }
    
    if(LastConfState == HIGH && digitalRead(confPin) == HIGH) {
      //Turn off pixel to indicate that if the button is released at that time the gamepad will go into deep sleep
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
      TimeReleased = millis();
      LastConfState = LOW;
    }
  
    long pressDuration = TimeReleased - TimePressed;  //calculate the duration of the configuration button press
   
    //if the button is pressed for less than 3 seconds the button will cycle through the factory keys
    if( pressDuration < ShortPress && pressDuration > 0 && factsettings && (millis() - recentPress) > 500) {
      n = n+1;
      pressDuration = 0;
      TimeReleased = 0;
      TimePressed = 0;
      recentPress = millis();
      if(n > 4) {
        n = 0;
      }  
    }
  
    if (millis() - recentPress > 500) {
      recentPress = 0;
    }
    
    if( pressDuration > SleepPress && pressDuration < LongPress) {
      pixels.clear();
      pixels.show();
      bleKeyboard.end();
      esp_deep_sleep_start();
    }
  
    if (pressDuration > LongPress) {
      n = 0;
      pressDuration = 0;
      TimeReleased = 0;
      TimePressed = 0;
      bleKeyboard.setColour(&KeyFact[n][1]);
    }
  //
  //LED Control
  //If the BUG is connected
  if (bleKeyboard.isConnected()) { 
  
  
    
  
   //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
   //neo pixels button top: left = 0, top = 1, middle = 2, down = 3, right = 4;
   if (LEDbin[0] == 1) {
    //pixels.clear();
    pixels.setPixelColor(4, pixels.Color(colour[0],colour[1],colour[2]));
   }
   else {
    //pixels.clear();
    pixels.setPixelColor(4, pixels.Color(OFF));
   }
   if (LEDbin[1] == 1) {
    pixels.setPixelColor(2, pixels.Color(colour[0],colour[1],colour[2]));
   }
   else {
    pixels.setPixelColor(2, pixels.Color(OFF));
   }
   if (LEDbin[2] == 1) {
    pixels.setPixelColor(0, pixels.Color(colour[0],colour[1],colour[2]));
   }
   else {
    pixels.setPixelColor(0, pixels.Color(OFF));
   }
   if (LEDbin[3] == 1) {
    pixels.setPixelColor(1, pixels.Color(colour[0],colour[1],colour[2]));
    pixels.show();
   }
   else {
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.show();
   }
  

  }
  //If the BUG is not connected
  else{
    if (millis() - blinktimeoff > 300 && millis() - blinktimeon > 600) {
       if (LEDbin[0] == 1) {
        //pixels.clear();
        pixels.setPixelColor(4, pixels.Color(0,0,40));
       }
       else {
        //pixels.clear();
        pixels.setPixelColor(4, pixels.Color(OFF));
       }
       if (LEDbin[1] == 1) {
        pixels.setPixelColor(2, pixels.Color(0,0,40));
       }
       else {
        pixels.setPixelColor(2, pixels.Color(OFF));
       }
       if (LEDbin[2] == 1) {
        pixels.setPixelColor(0, pixels.Color(0,0,40));
       }
       else {
        pixels.setPixelColor(0, pixels.Color(OFF));
       }
       if (LEDbin[3] == 1) {
        pixels.setPixelColor(1, pixels.Color(0,0,40));
        pixels.show();
        blinktimeon = millis();
       }
       else {
        pixels.setPixelColor(1, pixels.Color(OFF));
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
