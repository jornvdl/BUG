/*
@Title BUG ESP code including indication LEDs
@Author Floris van der Heijde
@Delft University of Technology
@Date 05-10-2021

@Hardware
ESP-C3-12F kit dev board
neopixles

18 Pulldown button pin
19 Neopixle output pin

*/

#include <BleKeyboard.h>
#include <Adafruit_NeoPixel.h>

//Set the name of the BUG(Bluetooth Ultrasimple Gamepad
BleKeyboard bleKeyboard("BUG-ESP");

#define buttonPin   18  //set the buttonpin
#define NEOPIN      19  //set the pin for the neopixels
#define NUMPIXELS    5  //set the amount of neopixels
#define WHITE       255, 255, 255 //set the rgb value for white
#define BLUE        0, 0, 255     //set the rgb value for blue
#define RED         255, 0, 0     //set the rgb value for red
#define GREEN       0, 255, 0     //set the rgb value for green
#define PURPLE      255, 0, 255   //set the rgb value for purple
#define OFF         0, 0, 0       //set the rgb value for OFF

//Define char for space arrow up, down, left, and right
char space = 32;
char arrowup = KEY_UP_ARROW;
char arrowdown = KEY_DOWN_ARROW;
char arrowleft = KEY_LEFT_ARROW;
char arrowright = KEY_RIGHT_ARROW;


//select the desired key and colour
#define key          space
#define colour       PURPLE


//NEOPIXEL known numbers button on the right: top LED is 0 and right LED is 1 schatting: mid LED is 2, left LED is 3 and bottom LED is 4

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  bleKeyboard.begin();
  pinMode(buttonPin, INPUT_PULLDOWN); //set buttonpin as pulldown so standard low
  pixels.begin();
}

void loop() {

  //if BUG set to arrowup light up the top led in the selected colour
  if (key == arrowup) {
    pixels.clear();
    pixels.setBrightness(25);  
    pixels.setPixelColor(0, pixels.Color(colour));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();

  }
  //if BUG set to space light up the middle row of leds in the selected colour
  if (key == space) {
    pixels.clear();
    pixels.setBrightness(25);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(colour));
    pixels.setPixelColor(2, pixels.Color(colour));
    pixels.setPixelColor(3, pixels.Color(colour));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();

  }  
  //if BUG set to arrowdown light up the botton led in the selected colour
  if (key == arrowdown) {
    pixels.clear();
    pixels.setBrightness(25);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(colour));
    pixels.show();

  }  
  //if BUG set to arrowright light up the right led in the selected colour
  if (key == arrowright) {
    pixels.clear();
    pixels.setBrightness(25);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(colour));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(OFF));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();

  }  
  //if BUG set to arrowleft light up the left led in the selected colour
  if (key == arrowleft) { 
    pixels.clear();
    pixels.setBrightness(25);  
    pixels.setPixelColor(0, pixels.Color(OFF));
    pixels.setPixelColor(1, pixels.Color(OFF));
    pixels.setPixelColor(2, pixels.Color(OFF));
    pixels.setPixelColor(3, pixels.Color(colour));
    pixels.setPixelColor(4, pixels.Color(OFF));
    pixels.show();
  
  }  
  while (digitalRead(buttonPin) ==HIGH) {
      bleKeyboard.press(key); //continuously send a spacebar 
    }
    bleKeyboard.release(key);  //release the spacebar
    delay(5);
}
