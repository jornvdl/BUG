#include <BleKeyboardGATT.h>


BleKeyboard bleKeyboard("Gamer-BUG","TU Delft");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bleKeyboard.begin();
  pinMode(18, INPUT);
  int colour[3] = {0x0F, 0x0E, 0x0D}; //random vars
  int layout = 0x0F;  // 16, all on
  int keybind = 0x20; //space
  int timeout = 600;
  bleKeyboard.setTimeout(&timeout);
  bleKeyboard.setKey(&keybind);
  bleKeyboard.setColour(&colour[0]);
  bleKeyboard.setLayout(&layout);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(18) == HIGH) {
    Serial.print("timeout: ");
    Serial.print(*bleKeyboard.getTimeout());
    Serial.print(" | key: ");
    Serial.print(*bleKeyboard.getKey()); // Don't use this, use bleKeyboard.Press() instead
    Serial.print(" | layout: ");
    Serial.print(*bleKeyboard.getLayout());
    Serial.print(" | colour[r,g,b]: [");
    Serial.print(*bleKeyboard.getColour());
    Serial.print(",");
    Serial.print(*(bleKeyboard.getColour()+1));
    Serial.print(",");
    Serial.print(*(bleKeyboard.getColour()+2));
    Serial.println("]");
    
  }
}
