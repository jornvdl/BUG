#ifndef _FACTORY_H
#define _FACTORY_H
void factory() {
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
}


#endif // _FACTORY_H
