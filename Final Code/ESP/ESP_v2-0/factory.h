#ifndef _FACTORY_H
#define _FACTORY_H
void factory() {
  if (factWASD) {
    bleKeyboard.setKeybind ( &keyWASD[factConf] );  
    bleKeyboard.setColour  ( &factColour[0]       );
    bleKeyboard.cirKeys    ( &factMode[0]         );
    bleKeyboard.setLayout  ( &keyLayout[factConf] );
  }
  else {
    bleKeyboard.setKeybind ( &keyArrows[factConf] );  
    bleKeyboard.setColour  ( &factColour[0]       );
    bleKeyboard.cirKeys    ( &factMode[0]         );
    bleKeyboard.setLayout  ( &keyLayout[factConf] ); 
  }

}


#endif // _FACTORY_H
