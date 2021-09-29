// constants won't change. They're used here to set pin numbers:
const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
const int btn4 = 5;
const int led = 13;

// variables will change:
int btnState1 = 0;         // variable for reading the pushbutton status
int btnState2 = 0;         // variable for reading the pushbutton status
int btnState3 = 0;         // variable for reading the pushbutton status
int btnState4 = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  btnState1 = digitalRead(btn1);
  btnState2 = digitalRead(btn2);
  btnState3 = digitalRead(btn3);
  btnState4 = digitalRead(btn4);

  Serial.print(btnState1);
  Serial.print(",");
  Serial.print(btnState2);
  Serial.print(",");
  Serial.print(btnState3);
  Serial.print(",");
  Serial.println(btnState4);

  if (btnState1 and btnState2 and btnState3 and btnState4) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }

  delay(50);
}
