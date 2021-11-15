#ifndef _FUNCTIONS_H    // Put these two lines at the top of your file.
#define _FUNCTIONS_H    // (Use a suitable name, usually based on the file name.)
#endif // _FUNCTIONS_H    // Put this line at the end of your file.
int * layout_hextobin(){
  static int LEDtemp[] = {0,0,0,0};
  layout_main = *bleKeyboard.getLayout();
  if (layout_main < 0x8) {
    LEDtemp[0] = 0;
    if (layout_main< 0x4) {
      LEDtemp[1] = 0;
      if (layout_main< 0x2) {
        LEDtemp[2] = 0;
        if (layout_main== 0x0) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layout_main> 0x2) {
          LEDtemp[3] = 1;
        }
        else {
          LEDtemp[3] = 0;
        }
      }
    }
    else {
      LEDtemp[1] = 1;
      if (layout_main< 0x6) {
        LEDtemp[2] = 0;
        if (layout_main== 0x4) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layout_main== 0x6) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
    }
  }
  else {
    
    LEDtemp[0] = 1;
    if (layout_main< 0xC) {
      LEDtemp[1] = 0;
      if (layout_main< 0xA) {
        LEDtemp[2] = 0;
        if (layout_main== 0x8) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layout_main== 0xA) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
    }
    else {
      LEDtemp[1] = 1;
      if (layout_main< 0xE) {
        LEDtemp[2] = 0;
        if (layout_main== 0xC) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layout_main== 0xE) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
    }
  }

  return LEDtemp;
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

void MemoryStore(int n){
  preferences.begin("bug_data", false);
  preferences.putInt("cRed", *bleKeyboard.getColour());
  preferences.putInt("cGreen", *(bleKeyboard.getColour()+1));
  preferences.putInt("cBlue", *(bleKeyboard.getColour()+2));
  preferences.putInt("key", *bleKeyboard.getKey());
  preferences.putInt("layout", *bleKeyboard.getLayout());
  preferences.putInt("timeout", *bleKeyboard.getTimeout());
  preferences.putInt("factcount", n);
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
  preferences.end();
}

void keyboard_initialise(){
  bleKeyboard.setTimeout(&timeDeepSleep);
  bleKeyboard.setKey(&keybind);
  bleKeyboard.setColour(&colour_main[0]);
  bleKeyboard.setLayout(&layout_main);
  bleKeyboard.rstUpdate();
  bleKeyboard.rstFactory();
  bleKeyboard.rstKeyFlag();
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
/*
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
  float voltage = avg/1489;//2600=>1575 currently use 2750=>1489
  float bV = voltage*2.67;

  float battpercent = sqrt((bV/a) + (sq(b)/2*a) - (c/a)) - b/(2*a);
  if(battpercent>100){
    battpercent = 100;
  }
  int batt = round(battpercent);
  int batt05 = batt/5;
  int battfin = batt05*5;
  bleKeyboard.setBatteryLevel(battfin);
  
}
*/
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
