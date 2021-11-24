#ifndef _SHUTDOWN_H
#define _SHUTDOWN_H

void shutdown(int n, int factsettings){
  //Turn Leds off
  Ledsoff();
  //Set the readyPin low
  digitalWrite(rdyPin,LOW);
  //Memory storage
  preferences.begin("bug_data", false);
  preferences.putInt("cRed", *bleKeyboard.getColour());
  preferences.putInt("cGreen", *(bleKeyboard.getColour()+1));
  preferences.putInt("cBlue", *(bleKeyboard.getColour()+2));
  preferences.putInt("key", *bleKeyboard.getKeybind());
  preferences.putInt("layout", *bleKeyboard.getLayout());
  preferences.putInt("timeout", *bleKeyboard.getTimeout());
  preferences.putInt("dUp", *bleKeyboard.cirKeys());
  preferences.putInt("dLeft", *(bleKeyboard.cirKeys()+1));
  preferences.putInt("dDown", *(bleKeyboard.cirKeys()+2));
  preferences.putInt("dRight", *(bleKeyboard.cirKeys()+3));
  preferences.putInt("Space", *(bleKeyboard.cirKeys()+4));
  preferences.putInt("factcount", n);
  preferences.putInt("factset", factsettings);
  preferences.end();
  //Set the ESP to deep sleep
  esp_deep_sleep_start();
}

#endif // _SHUTDOWN_H
