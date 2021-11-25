/* Button header
 *  btnPress() is called when main detects a button press. It sends the event
 *  to the library and waits until the button is released. It then sends that
 *  event to the library and ends the function, returning to the main scope.
 */


#ifndef _BTN_H
#define _BTN_H


void btnPress() {
  if (debug) Serial.println("Game button pressed!");

  bleKeyboard.press();
  while(digitalRead(btnPin)) {};
  bleKeyboard.releaseAll();

  if (debug) Serial.println("Game button released!");
}

#endif // _BTN_H
