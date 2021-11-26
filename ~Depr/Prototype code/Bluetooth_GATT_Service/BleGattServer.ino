void setBLE() {
  BLEDevice::init(BLEname);
  bleKeyboard.begin();
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  // Define BLE characteristics
  BLECharacteristic *keyCharacteristic = pService->createCharacteristic(
                                         KEY_UUID,
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ
                                       );

  BLECharacteristic *colorCharacteristic = pService->createCharacteristic(
                                         COLOR_UUID,
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ
                                       );

  BLECharacteristic *ledCharacteristic = pService->createCharacteristic(
                                         LED_UUID,
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ
                                       );

  BLECharacteristic *setupCharacteristic = pService->createCharacteristic(
                                         SETUP_UUID,
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_READ
                                       );

  BLECharacteristic *stateCharacteristic = pService->createCharacteristic(
                                         STATE_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  // Create callbacks
  keyCharacteristic->setCallbacks(new keyCallbacks());
  colorCharacteristic->setCallbacks(new colorCallbacks());
  ledCharacteristic->setCallbacks(new ledCallbacks());
  setupCharacteristic->setCallbacks(new setupCallbacks());
  stateCharacteristic->setCallbacks(new stateCallbacks());

  // Initial read-values on characteristics.
  keyCharacteristic->setValue(keystroke);
  colorCharacteristic->setValue(color);
  ledCharacteristic->setValue(led);
  setupCharacteristic->setValue(timeout);
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}
