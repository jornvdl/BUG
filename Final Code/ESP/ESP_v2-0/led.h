#ifndef _LED_H
#define _LED_H

int * layout_hextobin(){
  static int binTemp[] = {0,0,0,0};
  layout_main = *bleKeyboard.getLayout();
  binTemp[3] = (layout_main &1);
  binTemp[2] = (layout_main>>1 &1);
  binTemp[1] = (layout_main>>2 &1);
  binTemp[0] = (layout_main>>3 &1);
  return binTemp;

}


void ledShow() {
  //Set neopixles according to ledBin top = ledBin[3], left = ledBin[2], down = ledBin[1], right = ledBin[0]
  //neo pixels: top = 0, left = 1, down = 2, right = 3;
  bool ledBin[4] = {0,0,0,0};
  ledBin[0] = *layout_hextobin();
  ledBin[1] = *(layout_hextobin()+1);
  ledBin[2] = *(layout_hextobin()+2);
  ledBin[3] = *(layout_hextobin()+3);     
  
  int* ptrColour = bleKeyboard.getColour(); 
  long ledColour = leds.Color(*ptrColour,*(ptrColour+1),*(ptrColour+2));
  
  for(int i = 0, i < 4, i++){
    if (ledBin[i]) {
      leds.setpixelColor((3-i), ledColour);
    }
    else {
      leds.setpixelColor((3-i), leds.Color(0,0,0));
    }
    leds.show();
  }

  if (debug) Serial.println("LEDs updated");

}


void LEDsoff() {
  leds.clear();
  leds.show();
}

void LEDsBlink() {
  int* ptrColour = bleKeyboard.getColour(); 
  long ledColour = leds.Color(*ptrColour,*(ptrColour+1),*(ptrColour+2));
  leds.fill(ledColour,0,numLeds);
  leds.show();
  delay(500);
  leds.clear();
  leds.show();
  delay(500);
}

void BLEdisconnected(){
  //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
  //neopixels: top = 0, left = 1, down = 2, right = 3; 
  int blinktimeoff;
  int blinktimeon;
  long blue = leds.Color(0,0,255);
  long off  = leds.Color(0,0,0);
  if (millis() - blinktimeoff > 300 && millis() - blinktimeon > 600) {
    
    for(int i = 0, i < 4, i++){
      if (*(layout_hextobin()+i)) {
        leds.setpixelColor((3-i), ledColour);
      }
      else {
      leds.setpixelColor((3-i), leds.Color(0,0,0));
      }
    leds.show();
    }
    blinktimeon = millis();
   
  }
  else if (millis() - blinktimeon > 300 && millis() - blinktimeoff > 600) {
    LEDsoff();
    blinktimeoff = millis();
  }
    
}

#endif // _LED_H
