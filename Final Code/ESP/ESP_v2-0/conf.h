#ifndef _CONF_H
#define _CONF_H

bool modeSelect() {
  bool* ptrMode = bleKeyboard.cirKeys();
  if (*ptrMode || *(ptrMode+1) || *(ptrMode+2) || *(ptrMode+3) || *(ptrMode+4) ) {
    if (debug) {
      Serial.print("modeSelect = true, since ");
      Serial.print(*ptrMode);Serial.print(*(ptrMode+1));Serial.print(*(ptrMode+2));Serial.print(*(ptrMode+3));Serial.println(*(ptrMode+4));
    }
    return 1;
  }
  else {
    if (debug) Serial.println("modeSelect = false");
    return 0;
  }
}

void confRelease(int pressTime) {
  if (debug) Serial.println("conf:released");
  int releaseTime = millis();
  int durationTime = releaseTime - pressTime;
  bool* ptrMode = bleKeyboard.cirKeys();

  if((durationTime < shutdownTime) && modeSelect()) {
    if (debug) Serial.println("conf:next key");
    confSelect++;
    if(confSelect > 4) confSelect = 0;


    while (!*(ptrMode + confSelect)) {
      confSelect++;
      if(confSelect > 4) confSelect = 0;  
    }
    
    //Write new values to library
    if (*bleKeyboard.flgWASD()) {
      bleKeyboard.setKeybind  ( &keyWASD[confSelect]    );  
    }
    else {
      bleKeyboard.setKeybind  ( &keyArrows[confSelect]  );  
    }
    bleKeyboard.setLayout     ( &keyLayout[confSelect]  );

    //Update LEDs if BLE connected, otherwise it is handled by ledBlink()
    if (bleKeyboard.isConnected()) ledsOn();

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

void confPress(){
  if (debug) Serial.println("conf:pressed");
  int confTimer = millis();
  while(digitalRead(confPin) || (millis()-confTimer) < debounceTime) {
    if ((millis() - confTimer) > shutdownTime && (millis()- confTimer) < factoryTime) {
      ledsOff();
    }
    else if ((millis() - confTimer) >= factoryTime) {
      ledsBlink(true, false);
    }
    else if (!bleKeyboard.isConnected()) ledsBlink(false, true);
  }
  confRelease(confTimer);
}

#endif // _CONF_H
