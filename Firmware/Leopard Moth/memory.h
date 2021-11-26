/* 
 *  In this file, saving and retrieving data to the internal EEPROM 
 *  memory will be handled. Except for the (global) confSelect, this
 *  is stored/saved to the BleKeyboard lib, handling a lot of the data.
 */

#ifndef _MEMORY_H
#define _MEMORY_H

#include <Preferences.h>

Preferences memory;

void memory2lib() {
  int  memKey;
  int  memColour[3];
  bool memMode[5];
  int  memLayout;
  int  memSleep;
    
  memory.begin("bug_data",true);

  // Select proper factory settings for first init
  if (!factWASD) {
    memKey      = memory.getInt("key",    keyArrows[factConf] );
  } else {
    memKey      = memory.getInt("key",    keyWASD[factConf]   );
  }

  memColour[0]  = memory.getInt("cRed",   factColour[0]       );
  memColour[1]  = memory.getInt("cGreen", factColour[1]       );
  memColour[2]  = memory.getInt("cBlue",  factColour[2]       );
  memMode[0]    = memory.getInt("mode0",  factMode[0]         );
  memMode[1]    = memory.getInt("mode1",  factMode[1]         );
  memMode[2]    = memory.getInt("mode2",  factMode[2]         );
  memMode[3]    = memory.getInt("mode3",  factMode[3]         );
  memMode[4]    = memory.getInt("mode4",  factMode[4]         );
  memLayout     = memory.getInt("layout", keyLayout[factConf] );
  memSleep      = memory.getInt("timeout",factSleep           );
  confSelect    = memory.getInt("conf",   factConf            );
  memory.end();

  bleKeyboard.setKeybind ( &memKey       );
  bleKeyboard.setColour  ( &memColour[0] );
  bleKeyboard.cirKeys    ( &memMode[0]   );
  bleKeyboard.setLayout  ( &memLayout    );
  bleKeyboard.setTimeout ( &memSleep     );
  bleKeyboard.flgWASD    ( factWASD      );
  bleKeyboard.flgRstTimer( false         );
  bleKeyboard.flgIdentify( false         );
  bleKeyboard.flgRstBUG  ( false         );
}

void lib2memory() {
  int*  memColour = bleKeyboard.getColour();
  bool* memMode   = bleKeyboard.cirKeys();
  
  memory.begin("bug_data", false);
  memory.putInt("key",    *bleKeyboard.getKeybind() );
  memory.putInt("cRed",   *(memColour)              );
  memory.putInt("cGreen", *(memColour+1)            );
  memory.putInt("cBlue",  *(memColour+2)            );
  memory.putInt("mode0",  *(memMode)                );
  memory.putInt("mode1",  *(memMode+1)              );
  memory.putInt("mode2",  *(memMode+2)              );
  memory.putInt("mode3",  *(memMode+3)              );
  memory.putInt("mode4",  *(memMode+4)              );
  memory.putInt("layout", *bleKeyboard.getLayout()  );
  memory.putInt("timeout",*bleKeyboard.getTimeout() );
  memory.putInt("conf",    confSelect               );
}

#endif // _MEMORY_H
