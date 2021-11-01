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
