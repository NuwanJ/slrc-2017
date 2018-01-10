void setup() {
   Serial.begin(115200);
}

void loop() {
  float adaptingParameter=0.1;
  float reading=0;
  while(true){
    //159,141
    reading=(reading*(1.0f-adaptingParameter))+ (adaptingParameter*(1024.0f-analogRead(A0)));
    Serial.println(reading);
    delay(100);
  }
}
