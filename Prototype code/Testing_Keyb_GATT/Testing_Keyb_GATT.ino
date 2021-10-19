#include <BleKeyboardGATT.h>
#include <GATTCallbacks.h>

BleKeyboard bleKeyboard("Testing");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
