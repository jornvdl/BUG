/*
 * Title ADC measurement code
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(0, INPUT); //set the battery pin as input
  pinMode(2, INPUT);
  pinMode(19,INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(0));
  Serial.print("\n");
  delay(100);
  if(digitalRead(19) == HIGH){
    digitalWrite(4,LOW);
    esp_deep_sleep_start();
  }
}
