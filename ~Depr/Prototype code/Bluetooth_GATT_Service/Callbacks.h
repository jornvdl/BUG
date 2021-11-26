// Fix these with fact settings
int keystroke = 0xDA;   // Keystroke, 0xDA is arrow up
int color = 0xF007;     // 0xF007 is red, half intensity
int led = 0x8;          // 0x8 is only upper led
int timeout = 600;      // timeout, in seconds (set by setupChar)

class keyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *keyCharacteristic) {
      std::string value = keyCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New key value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);
        keystroke = value[0];
        Serial.println();
        Serial.print("Keystroke: ");
        Serial.println(keystroke);
        Serial.println("*********");
      }
    }
};

class stateCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *stateCharacteristic) {
      std::string value = stateCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New state value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
        stateCharacteristic->setValue("I return the state");
      }
    }
};

class colorCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *colorCharacteristic) {
      std::string value = colorCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New color value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

class ledCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *ledCharacteristic) {
      std::string value = ledCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New led value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

class setupCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *setupCharacteristic) {
      std::string value = setupCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New setup value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};
