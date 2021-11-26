
#include <Arduino.h>

void setup() {
    Serial1.begin(115200); // baudrate
    Serial.begin(115200);

}

void loop() {
    // Transmit on pin A6 (Tx of Serial 1) every byte
    // received over the USB connection (Serial)
    //
    while (Serial.available()) Serial1.write(Serial.read());
    Serial1.flush();

    // Tranmit over the USB link (Tx of Serial) every byte 
    // received on pin A7 (Rx of Serial1)
    //
    while (Serial1.available()) Serial.write(Serial1.read());
    Serial.flush();
}

/*
#include <Arduino.h>
int baud;
int old_baud;
void setup() {

  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  //baud = SerialUSB.getBaud();
  //old_baud = baud;
  Serial1.begin(115200);
  while (!Serial);
  while (!SerialUSB);
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
 /*
  baud = SerialUSB.getBaud();
  if (baud != old_baud) {
    Serial1.begin(baud);
    while (!Serial);
    old_baud = baud;
    //     SerialUSB.println(baud);
  }*//*
  if (SerialUSB.available() > 0)
  {
    char c = SerialUSB.read();
    Serial1.write(c);
  }
  if (Serial1.available() > 0) {
    char c = Serial1.read();
    SerialUSB.write(c);
  }
}*/
