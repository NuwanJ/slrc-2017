///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~START

float irWall_LeftSensorHistory[10];
float irWall_RightSensorHistory[10];

float irWall_SensorAdaptiveFactor = 0.1;
float irWall_kP = 15.0f, irWall_kD = 0.0f, irWall_kI = 0.0f;

float irWall_expectedReading = 70.0f;

int irWall_LeftSensorPin = A10;
int irWall_RightSensorPin = A9;
bool is_init = false;
bool is_changed = false;

void irWall_ReadSensors() {
  for (int x = 9; x > 0; x--) {
    irWall_LeftSensorHistory[x - 1] = irWall_LeftSensorHistory[x];
    irWall_RightSensorHistory[x - 1] = irWall_RightSensorHistory[x];
  }
  irWall_LeftSensorHistory[0] = 1024 - analogRead(irWall_LeftSensorPin);
  irWall_RightSensorHistory[0] = 1024 - analogRead(irWall_RightSensorPin);

  irWall_LeftSensorHistory[0] = (irWall_LeftSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_LeftSensorHistory[1]);
  irWall_RightSensorHistory[0] = (irWall_RightSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_RightSensorHistory[1]);

}


void irWall_Follow(int baseSpeed, int side) {

  for (int x = 0; x < 10; x++) {
    irWall_ReadSensors();
  }


  float* ir_hist;
  if (side == LEFT) {
    ir_hist = irWall_LeftSensorHistory;
  } else {
    ir_hist = irWall_RightSensorHistory;
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(irWall_LeftSensorHistory[0]);
  lcd.setCursor(8, 1);
  lcd.print(irWall_RightSensorHistory[0]);
  float P = ir_hist[0] - irWall_expectedReading;
  float D = ir_hist[0] - ir_hist[1];
  float I = 0.0f;
  for (int x = 1; x < 10; x++)I += ir_hist[x] - irWall_expectedReading;

  Serial.print(P); Serial.print(" "); Serial.print(0); Serial.print(" "); Serial.print(D); Serial.println(" ");

  float PID = P * irWall_kP + D * irWall_kD + irWall_kI * I;
  if (side == LEFT) {
    motorWrite(baseSpeed - PID, baseSpeed + PID);
  } else {
    motorWrite(baseSpeed + PID, baseSpeed - PID);
  }
  delay(30);
}

int wallFollow(int baseSpeed) {
  for (int x = 0; x < 10; x++) {
    irWall_ReadSensors();
  }
  if (!is_init) {

    // do we need to check if the robot is in correct orientation??
    if (irWall_RightSensorHistory[0] < irWall_LeftSensorHistory[0]) {
      currentlyFollowing = false;
      //irWall_expectedReading = irWall_RightSensorHistory[0];
    } else {
      currentlyFollowing = true;
      //irWall_expectedReading =irWall_LeftSensorHistory[0];
    }
    is_init = true;
    return 0;
  }

  // check if there are both left and right walls. if so, switch the wall
  if (abs(irWall_LeftSensorHistory[0] - irWall_expectedReading) < 10 and abs(irWall_RightSensorHistory[0] - irWall_expectedReading) < 10) {
    if (!is_changed) {
      currentlyFollowing = !currentlyFollowing;
      is_changed = true;
    }
  } else {
    is_changed = false;

  }

  if (currentlyFollowing) {
    ledOn(LED_GREEN);
    irWall_Follow(baseSpeed, LEFT);
  } else {
    ledOff(LED_GREEN);
    irWall_Follow(baseSpeed, RIGHT);
  }

}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END






float sign(float x) {
  if (x > 0.0001f)return 1.0f;
  if (x < -0.0001f)return -1.0f;
  return 0.0f;
}




