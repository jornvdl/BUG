/*
@Title BUG ESP code including indication LEDs Devkit
@Author Floris van der Heijde
@Delft University of Technology
@Date 05-10-2021

@Hardware
ESP-C3-12F kit dev board
neopixles

18 Pulldown button pin
19 Neopixle output pin

*/
#include "header.h"
#include <BleKeyboard.h>
#include <Adafruit_NeoPixel.h>

//Set the name of the BUG(Bluetooth Ultrasimple Gamepad
BleKeyboard bleKeyboard("BUG-ESP");

//NEOPIXEL known numbers button on the top: 0=left, 1=top, 2=centre, 3=bottom, 4=right

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels


void setup() {
  bleKeyboard.begin();                //start ble keyboard
  pinMode(buttonPin, INPUT_PULLDOWN); //set buttonpin as pulldown so standard low
  pinMode(confPin, INPUT_PULLDOWN);   //set conf button pin as pulldown so standard low
  pixels.begin();

  pixels.setBrightness(15);   

  TimeSleep = millis();
 // uint32_t ALL = pixels.Color(255, 255, 255);
}

void loop() {
  
  if ((millis() - TimeSleep) > 300000) {
     pixels.clear();
     pixels.show();
     esp_deep_sleep_start();
  }
  
  key = KeyCycle[n];
  //Testing ifs for LED shift with keys
  if (key == w) {
    LED = 0x1;
  }
  else if (key == a){
    LED = 0x2;
  }
  else if (key == s) {
    LED = 0x4;
  }
  else if (key == d) {
    LED = 0x8;
  }
  else {
    LED = 0xF;
  }

  
  //LED hexadecimal to binary
  if (LED < 0x8) {
    LEDbin[0] = 0;
    if (LED < 0x4) {
      LEDbin[1] = 0;
      if (LED < 0x2) {
        LEDbin[2] = 0;
        if (LED == 0x0) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
      else {
        LEDbin[2] = 1;
        if (LED > 0x2) {
          LEDbin[3] = 1;
        }
        else {
          LEDbin[3] = 0;
        }
      }
    }
    else {
      LEDbin[1] = 1;
      if (LED < 0x6) {
        LEDbin[2] = 0;
        if (LED == 0x4) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
      else {
        LEDbin[2] = 1;
        if (LED == 0x6) {
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
    if (LED < 0xC) {
      LEDbin[1] = 0;
      if (LED < 0xA) {
        LEDbin[2] = 0;
        if (LED == 0x8) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
      else {
        LEDbin[2] = 1;
        if (LED == 0xA) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
    }
    else {
      LEDbin[1] = 1;
      if (LED < 0xE) {
        LEDbin[2] = 0;
        if (LED == 0xC) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
      else {
        LEDbin[2] = 1;
        if (LED == 0xE) {
          LEDbin[3] = 0;
        }
        else {
          LEDbin[3] = 1;
        }
      }
    }
  }

 //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
 //neo pixels button top: left = 0, top = 1, middle = 2, down = 3, right = 4;
 if (LEDbin[0] == 1) {
  //pixels.clear();
  pixels.setPixelColor(4, pixels.Color(colour));
 }
 else {
  //pixels.clear();
  pixels.setPixelColor(4, pixels.Color(OFF));
 }
 if (LEDbin[1] == 1) {
  pixels.setPixelColor(2, pixels.Color(colour));
 }
 else {
  pixels.setPixelColor(2, pixels.Color(OFF));
 }
 if (LEDbin[2] == 1) {
  pixels.setPixelColor(0, pixels.Color(colour));
 }
 else {
  pixels.setPixelColor(0, pixels.Color(OFF));
 }
 if (LEDbin[3] == 1) {
  pixels.setPixelColor(1, pixels.Color(colour));
  pixels.show();
 }
 else {
  pixels.setPixelColor(1, pixels.Color(OFF));
  pixels.show();
 }

  //The Button press
  if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
    bleKeyboard.press(key); //continuously send a spacebar when button is pressed
    LastState = HIGH;       //set last state to high
    TimeSleep = millis();
  }
  if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
    bleKeyboard.release(key);  //stop sending the spacebar when the button is released
    LastState = LOW;
  }
  
  if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
    TimePressed = millis();
    LastConfState = HIGH;
    TimeSleep = millis();
    }
  while(LastConfState == HIGH && digitalRead(confPin) == HIGH) {
    if((millis() - TimePressed) > 3000 && (millis() - TimePressed) < 7000) {
      pixels.clear();
      pixels.show();
    }
    if((millis() - TimePressed) > 7000) {
      pixels.fill(pixels.Color(colour),0,5);
      pixels.show();
      delay(500);
      pixels.clear();
      pixels.show();
      delay(500);
    }
  }
  if(LastConfState == HIGH && digitalRead(confPin) == LOW) { // button is released
    TimeReleased = millis();
    LastConfState = LOW;
  }

  long pressDuration = TimeReleased - TimePressed;
  
  if( pressDuration < ShortPress && pressDuration > 0) {
    n = n+1;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
    if(n > 3) {
      n = 0;
     
    }  
  }
  
  if( pressDuration > LongPress && pressDuration < SleepPress) {
    n = 0;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
  }

  if (pressDuration > SleepPress) {
      pixels.clear();
      pixels.show();
      esp_deep_sleep_start();

  }


}
