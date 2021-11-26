/*
@Title BLE keyboard, arcade button to phone
@Author Floris van der Heijde
@Institute Umeå Institute of Design
@Date 29-01-2020
 
@Hardware
 
Any ESP32 dev board would do, but I used the:
Geekworm EASY KIT ESP32-C1
https://geekworm.com/products/official-geekworm-esp32-development-board

Arcade button
Adafruit Large Arcade button white
https://www.adafruit.com/product/1192

D5       Button pin
3.3V      Connected to the other leg of the button
 
In this example sketch processing can send an RGB value to Arduino and Arduino will change the LED color of the NUMPIXELS connected neopixels
*/
#include <BleKeyboard.h>
//Se the name of the bluetooth keyboard (that shows up in the bluetooth menu of your device)
BleKeyboard bleKeyboard("BUG-ESP");

const int buttonPin = 18;

// LED pin (Neopixel / WS2812b) at pin 19. Als het goed is, is de volgorde (met button beneden): links-boven-midden-onder-rechts

//Set the old button state to be LOW/false; which means not pressed
boolean oldPinState = LOW;

void setup() {
  //Start the Serial communication (with the computer at 115200 bits per second)
  //Serial.begin(115200);
  //Send this message to the computer
  //Serial.println("Starting BLE work!");
  //Begin the BLE keyboard/start advertising the keyboard (so phones can find it)
  bleKeyboard.begin();
  //Make the button pin an INPUT_PULLDOWN pin, which means that it is normally LOW, untill it is pressed/ connected to the 3.3V
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  while (digitalRead(buttonPin) ==HIGH) {
    bleKeyboard.press(32); //continuously send a spacebar 
    //delay(5);
  }
  bleKeyboard.release(32);  //release the spacebar
  delay(5);
}
