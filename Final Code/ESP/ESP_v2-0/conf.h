#ifndef _CONF_H
#define _CONF_H

void confPress(){
  static int confTimer;
  if(flgConfRecent && millis() - confTimer > 500){
    flgConfRecent = false;
  }
  if(!flgConfRecent){
    confTimer = millis();
    while((millis() - confTimer) > shutdownTime && (millis() - confTimer) < factoryTime) {
      ledsOff();
    }
    if ((millis() - confTimer) > factoryTime) {
      ledsBlink();
    }
  }

}

void confRelease(){
  
}

#endif // _CONF_H
