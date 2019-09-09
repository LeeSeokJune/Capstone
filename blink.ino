void setup() {
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  delay(1000);
  digitalWrite(4, HIGH);
  Serial.println("high");
  delay(1000);
  digitalWrite(4, LOW);
  Serial.println("low");
}
