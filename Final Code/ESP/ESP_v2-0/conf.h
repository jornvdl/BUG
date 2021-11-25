#ifndef _CONF_H
#define _CONF_H

bool modeSelect() {
  bool* ptrMode = bleKeyboard.cirKeys();
  if (*ptrMode || *(ptrMode+1) || *(ptrMode+2) || *(ptrMode+3) || *(ptrMode+4) ) {
    return 1;
  }
  else {
    return 0;
  }
}

void confRelease(int pressTime){
  if (debug) Serial.println("conf:released");
  int releaseTime = millis();
  int durationTime = releaseTime - pressTime;
  bool* ptrMode = bleKeyboard.cirKeys();
  while(durationTime < debounceTime) {
    if((durationTime < shutdownTime) && modeSelect()) {
      if (debug) Serial.println("conf:next key");
      confSelect++;
      if(confSelect > 4) confSelect = 0;
      while (!*(ptrMode + confSelect)) {
        confSelect++;
        if(confSelect > 4) confSelect = 0;  
      }
      //Write new values to library
      if (factWASD) {
        bleKeyboard.setKeybind  ( &keyWASD[confSelect]    );  
      }
      else {
        bleKeyboard.setKeybind  ( &keyArrows[confSelect]  );  
      }
      bleKeyboard.setLayout     ( &keyLayout[confSelect]  );
      //Update LEDs
      ledsOn();

    }
    else if(durationTime > shutdownTime && durationTime < factoryTime) {
      if (debug) Serial.println("conf:shutdown");
      shutdown();
    }
    else if(durationTime > factoryTime) {
      if (debug) Serial.println("conf:factory");
      factory();
    }
  }
}

void confPress(){
  if (debug) Serial.println("conf:pressed");
  int confTimer = millis();
  while(digitalRead(confPin)) {
    while((millis() - confTimer) > shutdownTime && (millis()- confTimer) < factoryTime) {
      ledsOff();
    }
    if ((millis() - confTimer) > factoryTime) {
      ledsBlink(true, false);
    }
  }
  confRelease(confTimer);
}

#endif // _CONF_H
