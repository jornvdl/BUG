#ifndef _FACTORY_H
#define _FACTORY_H
void factory() {
  if (debug) Serial.println("factory: writing factory settings to library");
  if (factWASD) {
    bleKeyboard.setKeybind ( &keyWASD[factConf] );  
  }
  else {
    bleKeyboard.setKeybind ( &keyArrows[factConf] );  
  }
  bleKeyboard.setColour  ( &factColour[0]       );
  bleKeyboard.cirKeys    ( &factMode[0]         );
  bleKeyboard.setLayout  ( &keyLayout[factConf] ); 
  
  bleKeyboard.flgRstBUG(false);
  bleKeyboard.flgIdentify(false);

  confSelect = factConf;
}


#endif // _FACTORY_H
