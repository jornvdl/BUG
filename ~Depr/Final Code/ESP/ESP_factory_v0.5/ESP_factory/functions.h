#ifndef _FUNCTIONS_H    // Put these two lines at the top of your file.
#define _FUNCTIONS_H    // (Use a suitable name, usually based on the file name.)
#endif // _FUNCTIONS_H    // Put this line at the end of your file.
int * layout_hextobin(int layouttemp){
  static int LEDtemp[] = {0,0,0,0};
  if (layouttemp < 0x8) {
    LEDtemp[0] = 0;
    if (layouttemp< 0x4) {
      LEDtemp[1] = 0;
      if (layouttemp< 0x2) {
        LEDtemp[2] = 0;
        if (layouttemp== 0x0) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layouttemp> 0x2) {
          LEDtemp[3] = 1;
        }
        else {
          LEDtemp[3] = 0;
        }
      }
    }
    else {
      LEDtemp[1] = 1;
      if (layouttemp< 0x6) {
        LEDtemp[2] = 0;
        if (layouttemp== 0x4) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layouttemp== 0x6) {
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
    if (layouttemp< 0xC) {
      LEDtemp[1] = 0;
      if (layouttemp< 0xA) {
        LEDtemp[2] = 0;
        if (layouttemp== 0x8) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layouttemp== 0xA) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
    }
    else {
      LEDtemp[1] = 1;
      if (layouttemp< 0xE) {
        LEDtemp[2] = 0;
        if (layouttemp== 0xC) {
          LEDtemp[3] = 0;
        }
        else {
          LEDtemp[3] = 1;
        }
      }
      else {
        LEDtemp[2] = 1;
        if (layouttemp== 0xE) {
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

void LEDupdate(int *LEDbin,int colour0,int colour1,int colour2) {
      //Set neopixels according to LEDbin top = LEDbin[3], left = LEDbin[2], down = LEDbin[1], right = LEDbin[0]
      //neo pixels: top = 0, left = 1, down = 2, right = 3;
      if (*LEDbin == 1) {
      pixels.setPixelColor(3, pixels.Color(colour0,colour1,colour2));
      }
      else {
      pixels.setPixelColor(3, pixels.Color(0,0,0));
      }
      if (*(LEDbin+1) == 1) {
      pixels.setPixelColor(2, pixels.Color(colour0,colour1,colour2));
      }
      else {
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      }
      if (*(LEDbin+2) == 1) {
      pixels.setPixelColor(1, pixels.Color(colour0,colour1,colour2));
      }
      else {
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      }
      if (*(LEDbin+3) == 1) {
      pixels.setPixelColor(0, pixels.Color(colour0,colour1,colour2));
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

void LEDsBlink(int colour0, int colour1, int colour2) {
      pixels.fill(pixels.Color(colour0,colour1,colour2),0,NUMPIXELS);
      pixels.show();
      delay(500);
      pixels.clear();
      pixels.show();
      delay(500);
}

void MemoryStore(int colour0, int colour1, int colour2, int layout, int keybind, int timeout, int n){
  preferences.begin("bug_data", false);
  preferences.putInt("cRed", colour0);
  preferences.putInt("cGreen", colour1);
  preferences.putInt("cBlue", colour2);
  preferences.putInt("key", keybind);
  preferences.putInt("layout", layout);
  preferences.putInt("timeout", timeout);
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
