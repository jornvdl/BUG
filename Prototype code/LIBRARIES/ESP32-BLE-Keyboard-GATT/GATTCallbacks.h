extern int keystroke;
extern int colour;
extern bool layout[4];
extern int timeout;


// When new key is received, update global variable and acknowledge.
class keyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *keyCharacteristic) {
    std::string value = keyCharacteristic->getValue();

    if (value.length()>0) {
      
    }
  }
};

// When new colour is received, update global variable and acknowledge.
class colourCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *colourCharacteristic) {
    std::string value = colourCharacteristic->getValue();

    if (value.length()>0) {
      
    }
  }
};

// When new layout is received, update global variable and acknowledge.
class ledCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *ledCharacteristic) {
    std::string value = ledCharacteristic->getValue();

    if (value.length()>0) {
      
    }
  }
};

// When new timeout is received, update global variable and acknowledge.
class timeoutCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *timeoutCharacteristic) {
    std::string value = timeoutCharacteristic->getValue();

    if (value.length()>0) {
      
    }
  }
};

// When state is received, check is reset (then do this) or call. Reply with (resetted) states.
class stateCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *stateCharacteristic) {
    std::string value = stateCharacteristic->getValue();

    if (value.length()>0) {
      
    }
  }
};