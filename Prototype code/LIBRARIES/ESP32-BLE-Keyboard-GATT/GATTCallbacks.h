

extern int keystroke;
extern int colour;
extern int led;
extern int timeout;


// When new key is received, update global variable and acknowledge.
class keyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *keyCharacteristic) {
    std::string value = keyCharacteristic->getValue();

    if (value.length()>0) {
      //ESP_LOGD(LOG_TAG, "New key value!");
    }
  }
};

// When new colour is received, update global variable and call Neopixel update. Acknowledge.
class colourCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *colourCharacteristic) {
    std::string value = colourCharacteristic->getValue();

    if (value.length()>0) {
      //ESP_LOGD(LOG_TAG, "New colour value!");
    }
  }
};

// When new layout is received, update global variable and call Neopixel update. Acknowledge.
class ledCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *ledCharacteristic) {
    std::string value = ledCharacteristic->getValue();

    if (value.length()>0) {
      //ESP_LOGD(LOG_TAG, "New layout value!");
    }
  }
};

// When new layout is received, update global variable and reset timer. Acknowledge.
class timeoutCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *timeoutCharacteristic) {
    std::string value = timeoutCharacteristic->getValue();

    if (value.length()>0) {
      //ESP_LOGD(LOG_TAG, "New timeout value!");
    }
  }
};

// When state is received, check is reset (then do this) or call. Reply with (resetted) states.
class stateCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *stateCharacteristic) {
    std::string value = stateCharacteristic->getValue();

    if (value.length()>0) {
      //ESP_LOGD(LOG_TAG, "New state value!");
    }
  }
};