/*
@Title BLE keyboard, arcade button to phone
@Author Geert Roumen
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

const int buttonPin = 5;
//Set the old button state to be LOW/false; which means not pressed
boolean oldPinState = LOW;

void setup() {
  //Start the Serial communication (with the computer at 115200 bits per second)
  Serial.begin(115200);
  //Send this message to the computer
  Serial.println("Starting BLE work!");
  //Begin the BLE keyboard/start advertising the keyboard (so phones can find it)
  bleKeyboard.begin();
  //Make the button pin an INPUT_PULLDOWN pin, which means that it is normally LOW, untill it is pressed/ connected to the 3.3V
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {

  if (bleKeyboard.isConnected()) {
    //if the keyboard is connected to a device
    if (digitalRead(buttonPin) == HIGH) {
      //If the button pin is pressed (since it is pulled down, it is pressed when it is high
      if (oldPinState == LOW) {
        //if the old Pin state was LOW and the button pin is HIGH than...
        //send the spacebar
        bleKeyboard.print(" ");
        //bleKeyboard.write(0x20);
        //or you can comment this one out, and it will send the newline character
        //bleKeyboard.write(KEY_RETURN);
      }
      oldPinState = HIGH;
    } else {
      oldPinState = LOW;
    }
  }
  delay(10);
}
