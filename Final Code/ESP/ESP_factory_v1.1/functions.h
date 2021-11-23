#ifndef _FUNCTIONS_H    // Put these two lines at the top of your file.
#define _FUNCTIONS_H    // (Use a suitable name, usually based on the file name.)
#endif // _FUNCTIONS_H    // Put this line at the end of your file.
int * layout_hextobin(){
  static int Bintemp[] = {0,0,0,0};
  layout_main = *bleKeyboard.getLayout();
  Bintemp[3] = (layout_main &1);
  Bintemp[2] = (layout_main>>1 &1);
  Bintemp[1] = (layout_main>>2 &1);
  Bintemp[0] = (layout_main>>3 &1);
  return Bintemp;

}

void LEDupdate() {
      //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
      //neo pixels: top = 0, left = 1, down = 2, right = 3;
      LEDbin[0] = *layout_hextobin();
      LEDbin[1] = *(layout_hextobin()+1);
      LEDbin[2] = *(layout_hextobin()+2);
      LEDbin[3] = *(layout_hextobin()+3);      
      if (LEDbin[0] == 1) {
      pixels.setPixelColor(3, pixels.Color(*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)));
      }
      else {
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      }
      if (LEDbin[1] == 1) {
      pixels.setPixelColor(2, pixels.Color(*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)));
      }
      else {
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      }
      if (LEDbin[2] == 1) {
      pixels.setPixelColor(1, pixels.Color(*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)));
      }
      else {
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      }
      if (LEDbin[3] == 1) {
      pixels.setPixelColor(0, pixels.Color(*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)));
      pixels.show();
      }
      else {
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.show();
      }
}

void LEDsoff() {
  pixels.clear();
  pixels.show();
}

void LEDsBlink() {
      pixels.fill(pixels.Color(*bleKeyboard.getColour(),*(bleKeyboard.getColour()+1),*(bleKeyboard.getColour()+2)),0,NUMPIXELS);
      pixels.show();
      delay(500);
      pixels.clear();
      pixels.show();
      delay(500);
}

void LEDsBlinkcolour(int Colour1, int Colour2, int Colour3) {
  pixels.fill(pixels.Color(Colour1,Colour2,Colour3));
  pixels.show();
  delay(500);
  pixels.clear();
  pixels.show();
  delay(500);
}

void MemoryStore(int n, int factsettings){
  preferences.begin("bug_data", false);
  preferences.putInt("cRed", *bleKeyboard.getColour());
  preferences.putInt("cGreen", *(bleKeyboard.getColour()+1));
  preferences.putInt("cBlue", *(bleKeyboard.getColour()+2));
  preferences.putInt("key", *bleKeyboard.getKeybind());
  preferences.putInt("layout", *bleKeyboard.getLayout());
  preferences.putInt("timeout", *bleKeyboard.getTimeout());
  preferences.putInt("factcount", n);
  preferences.putInt("factset", factsettings);
  preferences.end();
}

void MemoryPull(){
  preferences.begin("bug_data", true);
  keybind = preferences.getInt("key", 0x20);
  colour_main[0] = preferences.getInt("cRed", 0x22);
  colour_main[1] = preferences.getInt("cGreen", 0xA0);
  colour_main[2] = preferences.getInt("cBlue", 0xFF);
  layout_main = preferences.getInt("layout", 0x0F);
  timeDeepSleep = preferences.getInt("timeout", 300);
  n = preferences.getInt("factcount", 0);
  factsettings = preferences.getInt("factset", true);
  preferences.end();
}

void keyboard_initialise(){
  bleKeyboard.setTimeout(&timeDeepSleep);
  bleKeyboard.setKeybind(&keybind);
  bleKeyboard.setColour(&colour_main[0]);
  bleKeyboard.setLayout(&layout_main);
  bleKeyboard.flgRstTimer(false);
  bleKeyboard.flgRstBUG(false);
  bleKeyboard.flgIdentify(false);
  bleKeyboard.flgWASD(false);
  bleKeyboard.cirKeys(&keys[0]);
}

void BLEdisconnected(){
  //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
  //neo pixels: top = 0, left = 1, down = 2, right = 3; 

  if (millis() - blinktimeoff > 300 && millis() - blinktimeon > 600) {
    if (*layout_hextobin() == 1) {
    pixels.setPixelColor(3, pixels.Color(0,0,255));
    }
    else {
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    }
    if (*(layout_hextobin()+1) == 1) {
    pixels.setPixelColor(2, pixels.Color(0,0,255));
    }
    else {
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    }
    if (*(layout_hextobin()+2) == 1) {
    pixels.setPixelColor(1, pixels.Color(0,0,255));
    }
    else {
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    }
    if (*(layout_hextobin()+3) == 1) {
    pixels.setPixelColor(0, pixels.Color(0,0,255));
    pixels.show();
    }
    else {
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    }
    blinktimeon = millis();
   
  }
  else if (millis() - blinktimeon > 300 && millis() - blinktimeoff > 600) {
    LEDsoff();
    blinktimeoff = millis();
  }
    
}

void Batterypercentage(){
  int m = 0;
  int batmeasure[20];
  int total = 0;
  float a = 0.00005;
  float b = 0.002;
  float c = 3.1787;
  while (m < 20){
    batmeasure[m] = analogRead(BatteryPin);
    total = total + batmeasure[m];
    m++;
  }
  float avg = total/20;
  float bV = 0.0021*avg - 0.4452;
  float battpercent = sqrt((bV/a) + (sq(b)/2*a) - (c/a)) - b/(2*a);
  if(battpercent>100){
    battpercent = 100;
  }
  int batt = round(battpercent);
  int batt05 = batt/5;
  int battfin = batt05*5;
  bleKeyboard.setBatteryLevel(battfin);
}

void keyArrayUpdate(){
  int keyCirc = *bleKeyboard.cirKeys();
  int k = 0;
  if (!bleKeyboard.flgWASD()) {
    if(keyCirc &1) {
      keys[0,0] = &factArrowup;
      keys[0,1] = &(factArrowup+1);
      k++;
    }
    else {
      keys[0,0] = &null;
      keys[0,1] = &null;
    }
    if(keyCirc>>1 &1) {
      keys[1,0] = &factArrowleft;
      keys[1,1] = &(factArrowleft+1);
      k++;
    }
    else {
      keys[1,0] = &null;
      keys[1,1] = &null;
    }
    if(keyCirc>>2 &1) {
      keys[2,0] = &factArrowdown;
      keys[2,1] = &(factArrowdown+1);
      k++
    }
    else {
      keys[2,0] = &null;
      keys[2,1] = &null;
    }
    if(keyCirc>>3 &1) {
      keys[3,0] = &factArrowright;
      keys[3,1] = &(factArrowright+1);
      k++;
    }
    else {
      keys[3,0] = &null;
      keys[3,1] = &null;
    }
    if(keyCirc>>4 &1) {
      keys[4,0] = &space;
      keys[4,1] = &(space+1);
      k++;
    }
    else {
      keys[4,0] = &null;
      keys[4,1] = &null;
    }
  }
  if (bleKeyboard.flgWASD()) {
    if(keyCirc &1) {
      keys[0,0] = &factW;
      keys[0,1] = &(factW+1);
      k++;
    }
    else {
      keys[0,0] = &null;
      keys[0,1] = &null;
    }
    if(keyCirc>>1 &1) {
      keys[1,0] = &factA;
      keys[1,1] = &(factA+1);
      k++;
    }
    else {
      keys[1,0] = &null;
      keys[1,1] = &null;
    }
    if(keyCirc>>2 &1) {
      keys[2,0] = &factS;
      keys[2,1] = &(factS+1);
      k++;
    }
    else {
      keys[2,0] = &null;
      keys[2,1] = &null;
    }
    if(keyCirc>>3 &1) {
      keys[3,0] = &factD;
      keys[3,1] = &(factD+1);
      k++;
    }
    else {
      keys[3,0] = &null;
      keys[3,1] = &null;
    }
    if(keyCirc>>4 &1) {
      keys[4,0] = &space;
      keys[4,1] = &(space+1);
      k++;
    }
    else {
      keys[4,0] = &null;
      keys[4,1] = &null;
    }
  }
  if(k == 0){
    customKey = true;
  }
}


/*
int * keybindarray(){
  int keyarraytemp[5] = {0,0,0,0,0};
  int keysuse = *bleKeyboard.cirKeys();
  m = 0;
  if(bleKeyboard.flgWASD() == 0) {
    if (keysuse &1) {
      keyarraytemp[m] == arrowup;
      m++;
    }
    if(keysuse>>1 &1) {
      keyarraytemp[m] == arrowleft;
      m++;
    }
    if(keysuse>>2 &1) {
      keyarraytemp[m] == arrowdown;
      m++;
    }
    if(keysuse>>3 &1) {
      keyarraytemp[m] == arrowright;
      m++;
    }
    if(keysuse>>4 &1) {
      keyarraytemp[m] == space;
      m++;
    }
  }
  else if (bleKeyboard.flgWASD() == 1) {
    if (keysuse &1) {
      keyarraytemp[m] == w;
      m++;
    }
    if(keysuse>>1 &1) {
      keyarraytemp[m] == a;
      m++;
    }
    if(keysuse>>2 &1) {
      keyarraytemp[m] == s;
      m++;
    }
    if(keysuse>>3 &1) {
      keyarraytemp[m] == d;
      m++;
    }
    if(keysuse>>4 &1) {
      keyarraytemp[m] == space;
      m++;
    }
  }
  if(m == 0) {
    customKey = true;
  }
  else {
    customKey = false;
  }
  int keyarray[m];
  for(int k = 0; k < m; k++) {
    keyarray[k] = keyarraytemp[k];
  } 
  
  return keyarray;
}*/