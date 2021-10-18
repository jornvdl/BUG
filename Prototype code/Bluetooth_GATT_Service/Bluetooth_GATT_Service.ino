/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "Callbacks.h"
#include "defines.h"
#include <BleKeyboard.h>
#include <Adafruit_NeoPixel.h>

BleKeyboard bleKeyboard(BLEname);

Adafruit_NeoPixel pixels(numPix, ledPin, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup() {
  Serial.begin(115200);
  Serial.println("Serial output (DEBUG) of BUG. Use BLE Scanner on Android for communication now.");
  setBLE();

  pinMode(btnPin, INPUT);
  pixels.begin();

  int oldColor = color;
}

void loop() {
  // put your main code here, to run repeatedly:
  

  while (digitalRead(btnPin) == HIGH) {
    bleKeyboard.release(keystroke);
  }
  bleKeyboard.release(keystroke);
  delay(15);
}
