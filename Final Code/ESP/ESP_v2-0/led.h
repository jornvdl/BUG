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
  //Set neopixels according to ledBin top = ledBin[3], left = ledBin[2], down = ledBin[1], right = ledBin[0]
  //neo pixels: top = 0, left = 1, down = 2, right = 3;
  bool ledBin[4] = {0,0,0,0};
  ledBin[0] = *layout_hextobin();
  ledBin[1] = *(layout_hextobin()+1);
  ledBin[2] = *(layout_hextobin()+2);
  ledBin[3] = *(layout_hextobin()+3);     
  int* ptrColour = bleKeyboard.getColour(); 
  long ledColour = pixels.Color(*ptrColour,*(ptrColour+1),*(ptrColour+2));
  for(int i = 0, i < 4, i++){
    if (ledBin[i]) {
      pixels.setpixelColor((3-i), ledColour);
    }
    else {
      pixels.setpixelColor((3-i), pixels.Color(0,0,0));
    }
    pixels.show();
  }

  if (debug) Serial.println("LEDs updated");
  
}


#endif // _LED_H
