#ifndef _LED_H
#define _LED_H

int* layout_hextobin(){
  static int binTemp[]   = {0,0,0,0};
         int layout_main = *bleKeyboard.getLayout();

  binTemp[3] = (layout_main &1);
  binTemp[2] = (layout_main>>1 &1);
  binTemp[1] = (layout_main>>2 &1);
  binTemp[0] = (layout_main>>3 &1);

  if (debug) Serial.println("Layout hextobin");

  return binTemp;
}


void ledsOn() {
  //Set neopixles according to ledBin top = ledBin[3], left = ledBin[2], down = ledBin[1], right = ledBin[0]
  //neo pixels: top = 0, left = 1, down = 2, right = 3;
  bool ledBin[4] = {0,0,0,0};
  
  ledBin[0] = *layout_hextobin();
  ledBin[1] = *(layout_hextobin()+1);
  ledBin[2] = *(layout_hextobin()+2);
  ledBin[3] = *(layout_hextobin()+3);     
  
  int* ptrColour = bleKeyboard.getColour(); 
  long ledColour = leds.Color(*ptrColour, *(ptrColour+1), *(ptrColour+2));
  
  for(int i = 0; i < 4; i++) {
    if (ledBin[i]) {
      leds.setPixelColor((3-i), ledColour);
    }
    else {
      leds.setPixelColor((3-i), leds.Color(0,0,0));
    }
    leds.show();
  }

  if (debug) Serial.println("LEDs On/update");

}


void ledsOff() {
  leds.clear();
  leds.show();
  if (debug) Serial.println("LEDs off");

}

void ledsBlink(bool keepColour, bool keepLayout) {
  long ledColour;

  if (keepColour) {
    int* ptrColour = bleKeyboard.getColour();
    ledColour = leds.Color(*ptrColour, *(ptrColour+1), *(ptrColour+2));
  } 
  else { // If not using current colour, then select blinkColour set in variables.
    ledColour = leds.Color(blinkColour[0], blinkColour[1], blinkColour[2]);
  }

  // Determine if LEDs should be on or off
  int ledPeriod = millis() % (blinkTime * 2);
  bool ledEnabled = ledPeriod > blinkTime;
  
  bool currentState = 0;
  for (int j = 0; j < 4; j++) {
    currentState = currentState | (leds.getPixelColor(j) > 0 );
  }
  
  if (debug) {
    Serial.print  ("Current state LEDs (blink) = ");
    Serial.println(currentState);
  }

  // Set LEDs
  for(int i = 0; i < 4; i++) {
    if( (*(layout_hextobin()+i) || !keepLayout) && ledEnabled) {
      leds.setPixelColor((3-i), ledColour);
    }
    else {
      leds.setPixelColor((3-i), leds.Color(0,0,0));
    }
  }
  leds.show();
}

#endif // _LED_H
