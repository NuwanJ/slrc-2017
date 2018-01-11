void setup() {
  Serial.begin(115200);
}

float irWall_LeftSensorHistory[10];
float irWall_RightSensorHistory[10];

float irWall_SensorAdaptiveFactor = 0.1;
float irWall_kP = 10.0f, irWall_kD = 0.0f, irWall_kI = 0.0f;

float irWall_expectedReading = 80.0f;

void loop() {
  float adaptingParameter = 0.1;
  float reading = 0;
  while (true) {
    for (int x = 9; x > 0; x--) {
      irWall_LeftSensorHistory[x] = irWall_LeftSensorHistory[x-1];
      irWall_RightSensorHistory[x] = irWall_RightSensorHistory[x-1];
    }
    irWall_LeftSensorHistory[0] = 1024 - analogRead(A11);

    irWall_LeftSensorHistory[0] = (irWall_LeftSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_LeftSensorHistory[1]);
      
    //159,141
    reading = (reading * (1.0f - adaptingParameter)) + (adaptingParameter * (1024.0f - analogRead(A11)));
    Serial.print(analogRead(A11));
    Serial.print(" ");
    Serial.print(irWall_LeftSensorHistory[0]);
    Serial.print(" ");
    Serial.println(reading);
    delay(100);
  }
}
