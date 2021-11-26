// constants won't change. They're used here to set pin numbers:
const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
const int btn4 = 5;
const int led = 13;

// variables will change:
bool btnState[4] = {1,1,1,1};
bool btnOldState[4] = {1,1,1,1};

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  Serial.begin(38400);
}

void loop() {
  // read the state of the pushbutton value:
  btnState[0] = digitalRead(btn1);
  btnState[1] = digitalRead(btn2);
  btnState[2] = digitalRead(btn3);
  btnState[3] = digitalRead(btn4);

  // Check for every button if state changed
  for (int i = 0; i < 4; i++) {
    if (btnState[i] != btnOldState[i]) {

      // If button is changed and now pressed, send button number [1...4]
      if (btnState[i] == false) {
        Serial.println(i+1);
        digitalWrite(led,HIGH);
      }

      // If button is changed and now released, check if all buttons are released. If so, send 0.
      if (btnState[i] == true) {
        if (btnState[0] && btnState[1] && btnState[2] && btnState[3]) {
          Serial.println(0);
          digitalWrite(led,LOW);
        }
      }

      // Update old state to compare next loop
      btnOldState[i] = btnState[i];
    }
  }

  delay(5);
}
