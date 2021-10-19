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
  
  //if BUG set to arrowup light up the top led in the selected colour
  if (key == arrowup) {
    pixels.clear();                                   //reset the pixels
    pixels.setBrightness(15);                         //set the pixel brightness
    pixels.setPixelColor(0, pixels.Color(OFF));       //set the pixels corresponding to the key to the selected colour
    pixels.setPixelColor(1, pixels.Color(colour));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();                                    //display the pixels according to the settings

  }
  //if BUG set to space light up the middle row of leds in the selected colour
  if (key == space) {
    pixels.clear();
    pixels.setBrightness(15);  
    pixels.setPixelColor(0, pixels.Color(colour));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(colour));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(colour));
    pixels.show();

  }  
  //if BUG set to arrowdown light up the botton led in the selected colour
  if (key == arrowdown) {
    pixels.clear();
    pixels.setBrightness(15);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(colour));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();

  }  
  //if BUG set to arrowright light up the right led in the selected colour
  if (key == arrowright) {
    pixels.clear();
    pixels.setBrightness(15);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(colour));
    pixels.show();

  }  
  //if BUG set to arrowleft light up the left led in the selected colour
  if (key == arrowleft) { 
    pixels.clear();
    pixels.setBrightness(15);  
    pixels.setPixelColor(0, pixels.Color(colour));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();
  
  }  
}

void loop() {

  key = KeyCycle[n];
  
  if (digitalRead(buttonPin) == HIGH && LastState == LOW) {
    bleKeyboard.press(key); //continuously send a spacebar when button is pressed
    LastState = HIGH;       //set last state to high
  }
  if (digitalRead(buttonPin) == LOW && LastState == HIGH) {
    bleKeyboard.release(key);  //stop sending the spacebar when the button is released
    LastState = LOW;
  }
  
  if(LastConfState == LOW && digitalRead(confPin) == HIGH) {       // button is pressed
    TimePressed = millis();
    LastConfState = HIGH;
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
  
  if( pressDuration > LongPress ) {
    n = 0;
    pressDuration = 0;
    TimeReleased = 0;
    TimePressed = 0;
  }

}
