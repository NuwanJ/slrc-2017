String msg = "";
void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial.println("Starting...");
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}




void SerialEvent() {
  while (Serial.available()) {
    Serial.print((char)Serial.read());
  }
}
void Serial3Event() {
  while (Serial3.available()) {
    Serial.print((char)Serial3.read());
  }
}
