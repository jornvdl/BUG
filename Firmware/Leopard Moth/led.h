/*
 *  Here, the indicator LED behaviour is managed. Three options are available: 
 *  All leds off, a selection (according to a given layout) on or blinking.
 *  All three options have a seperate function and are accompanied by a function
 *  to convert the layout to a more useable format.
 */

#ifndef _LED_H
#define _LED_H

int* layout_hextobin(){
  static int binTemp[]   = {0,0,0,0};
         int layout_main = *bleKeyboard.getLayout();

  binTemp[3] = (layout_main &1);
  binTemp[2] = (layout_main>>1 &1);
  binTemp[1] = (layout_main>>2 &1);
  binTemp[0] = (layout_main>>3 &1);

  //if (debug) Serial.println("Layout hextobin");

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
  // Turn off all Neopixels, but only if they are currently on to prevent 
  // unneccesary communications
  bool currentState = 0;
  for (int j = 0; j < 4; j++) {
    currentState = currentState || (leds.getPixelColor(j) > 0 );
  }

  if (currentState) {
    leds.clear();
    leds.show();
    if (debug) Serial.println("LEDs off");
  }
}

void ledsBlink(bool keepColour, bool keepLayout) {
// Function to let the leds blink. The function must be called in a loop, since it only updates is state,
// is does not handle the blinking it self.

  long ledColour;

  // Determining the color to show during blinking
  if (keepColour) {
    int* ptrColour = bleKeyboard.getColour();
    ledColour = leds.Color(*ptrColour, *(ptrColour+1), *(ptrColour+2));
  } 
  else { // If not using current colour, then select blinkColour set in variables.
    ledColour = leds.Color(blinkColour[0], blinkColour[1], blinkColour[2]);
  }

  // Determine if LEDs should be on or off. This is done using the system time
  //  by using the modulo and the millis().
  int ledPeriod = millis() % (blinkTime * 2);
  bool ledEnabled = ledPeriod > blinkTime;
  
  // Getting current state, to prevent unnecessary updates to the leds
  bool currentState = 0;
  for (int j = 0; j < 4; j++) {
    currentState = currentState || (leds.getPixelColor(j) > 0 );
  }

  // Debug output
  if (debug && !currentState &&  ledEnabled) {
    Serial.print("LED Blink: on  ");
    if (keepColour) Serial.print("[keepcolour]");
    if (keepLayout) {
      Serial.print("[keeplayout=");
      Serial.print(*bleKeyboard.getLayout());
      Serial.print("]");
    }
    Serial.print("\n");
  }
  if (debug &&  currentState && !ledEnabled) Serial.println("LED Blink: off");

  // Set LEDs to corrent state and update
  for(int i = 0; i < 4; i++) {
    if( !currentState && ledEnabled) {              // If currently off, but supposed to be on
      if (*(layout_hextobin()+i) || !keepLayout ) { // and specific LED should be on
        leds.setPixelColor((3-i), ledColour);       // set LED colour
      }
      else {                                        // otherwise set off (layout specific)
        leds.setPixelColor((3-i), leds.Color(0,0,0));
      }
    }
    else if ( currentState && !ledEnabled) {        // If currently on, but supposed to be off
      leds.setPixelColor((3-i), leds.Color(0,0,0)); // Turn off
    }
  }
  leds.show();
}

#endif // _LED_H
