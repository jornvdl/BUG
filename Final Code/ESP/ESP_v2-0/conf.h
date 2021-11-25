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
  while(durationTime < debounceTime) {
    if((durationTime < shutdownTime) && modeSelect()) {
      if (debug) Serial.println("conf:next key");
      factConf++;
      if(factConf > 4) factConf = 0;
      while (!factMode[factConf]) {
        factConf++;
        if(factConf > 4) factConf = 0;  
      }
      //Write new values to library
      if (factWASD) {
        bleKeyboard.setKeybind  ( &keyWASD[factConf]    );  
      }
      else {
        bleKeyboard.setKeybind  ( &keyArrows[factConf]  );  
      }
      bleKeyboard.setLayout     ( &keyLayout[factConf]  );
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
  while(digitalRead(btnPin)) {
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
