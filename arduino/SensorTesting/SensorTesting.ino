void setup() {
   Serial.begin(115200);
}

void loop() {
  float learningRate=0.2;
  float reading=0;
  while(true){
    //159,141
    reading=(reading*(1.0f-learingRate))+ (learningRate*analogRead(A0));
    Serial.println(reading);
  }
}
