#include <BleKeyboardGATT.h>


BleKeyboard bleKeyboard("Gamer-BUG","TU Delft");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bleKeyboard.begin();
  pinMode(18, INPUT);
  int timeout = 600;
  bleKeyboard.setTimeout(&timeout);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(18) == HIGH) {
    Serial.print("timeout: ");
    Serial.println(*bleKeyboard.getTimeout());
  }
}
