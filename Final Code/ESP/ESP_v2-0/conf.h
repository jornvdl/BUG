#ifndef _CONF_H
#define _CONF_H

void confPress(){
  static int confTimer;
  if(flgConfRecent && millis() - confTimer > 500){
    flgConfRecent = false;
  }
  if(!flgConfRecent){
    confTimer = millis();
    
  }

}


#endif // _CONF_H
