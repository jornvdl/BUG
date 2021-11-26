/*
 *  Function to reset BUG to the factory settings
 */

#ifndef _FACTORY_H
#define _FACTORY_H
void factory() {
  if (debug) Serial.println("factory: writing factory settings to library");
  if (factWASD) {
    bleKeyboard.setKeybind ( &keyWASD[factConf] );  
    bleKeyboard.flgWASD(true);
  }
  else {
    bleKeyboard.setKeybind ( &keyArrows[factConf] );  
    bleKeyboard.flgWASD(false);
  }
  bleKeyboard.setColour  ( &factColour[0] );
  bleKeyboard.cirKeys    ( &factMode[0]   );
  bleKeyboard.setLayout  ( &keyLayout[0]  ); 
  
  bleKeyboard.flgRstBUG(false);
  bleKeyboard.flgIdentify(false);

  confSelect = factConf;

  ledsOn();
}


#endif // _FACTORY_H
