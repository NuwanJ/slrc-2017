///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~START


float irWall_SensorAdaptiveFactor = 0.1;
float irWall_kP = 5.0f, irWall_kD = 10.0f, irWall_kI = 3.0f;
float irWall_kF = -100.0f;

float irWall_expectedReading = 800.0f;
float wallExcistThresh = 850.0f;

bool recheck = false;

bool foundWhite = true;
bool passedInitialWhiteArea = false;

void irWall_ReadSensors() {
  for (int x = 9; x > 0; x--) {
    irWall_LeftSensorHistory[x] = irWall_LeftSensorHistory[x - 1];
    irWall_RightSensorHistory[x] = irWall_RightSensorHistory[x - 1];
    irWall_FrontSensorHistory[x] = irWall_FrontSensorHistory[x - 1];
  }
  irWall_LeftSensorHistory[0] = 1024 - analogRead(irWall_LeftSensorPin);
  irWall_RightSensorHistory[0] = 1024 - analogRead(irWall_RightSensorPin);
  irWall_FrontSensorHistory[0] = 1024 - analogRead(irWall_FrontSensorPin);


  irWall_LeftSensorHistory[0] = (irWall_LeftSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_LeftSensorHistory[1]);
  irWall_RightSensorHistory[0] = (irWall_RightSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_RightSensorHistory[1]);
  irWall_FrontSensorHistory[0] = (irWall_FrontSensorHistory[0] * irWall_SensorAdaptiveFactor) + ((1 - irWall_SensorAdaptiveFactor) * irWall_FrontSensorHistory[1]);

  // Moved lcd part to irWall_Follow, to reduce processing power -Nuwan
}

void irWall_ReadSensors(int iterations) {
  for (int i = 0; i < iterations; i++)irWall_ReadSensors();
}


void irWall_Follow(int baseSpeed, int side) {

  irWall_ReadSensors(10);


  float* ir_hist;
  if (side == LEFT) {
    ir_hist = irWall_LeftSensorHistory;
  } else {
    ir_hist = irWall_RightSensorHistory;
  }
  float P = (ir_hist[0] - irWall_expectedReading) / 10;
  float D = (ir_hist[0] - ir_hist[1]);
  float I = 0.0f;
  for (int x = 1; x < 10; x++)I += ir_hist[x] - irWall_expectedReading;
  I *= 0.001;

  if (P > 0) {
    irWall_kP = 15.0f;
    irWall_kD = 50.0f;
    irWall_kI = 10.0f;
  }
  float  F = exp(-(irWall_FrontSensorHistory[0] / 100 - 7.2));
  F = F * F;
  Serial.print(P * irWall_kP);  Serial.print(" "); Serial.print( D * irWall_kD ); Serial.print(" "); Serial.print(irWall_kI * I); Serial.print(" ");
  Serial.print(irWall_kF * F); Serial.print(" ");
  float PID = P * irWall_kP + D * irWall_kD + irWall_kI * I + irWall_kF * F;
  Serial.print(PID); Serial.println("");

  if (abs(PID) > baseSpeed) {
    PID = (PID / abs(PID)) * baseSpeed;
  }

  if (side == LEFT) {
    motorWrite(baseSpeed - PID, baseSpeed + PID);
  } else {
    motorWrite(baseSpeed + PID, baseSpeed - PID);
  }
  delay(30);
  //motorWrite(0, 0);
  //delay(10);
}

void adjustServo(bool following) {
  if (following) {
    rotateServo(30);
  } else {
    rotateServo(-30);
  }
}

void checkIR() {
  readIRSensors(sensor_values);
  int x = 1;
  int y = 0;
  for (int i = 0; i < 6; i++) {
    x *= sensor_values[i];
    y += sensor_values[i];
  }
  if (x == 0) {
    foundWhite = false;
    passedInitialWhiteArea = true;
  }
  if (y > 0) {
    foundWhite = true;
  }
}

int wallFollow(int baseSpeed) {

  irWall_ReadSensors(10);

  // recheck if we get a smaller reading from the unused IR wall following sensor
  if (currentlyFollowing and (irWall_RightSensorHistory[0] < irWall_LeftSensorHistory[0])) {
    beep(2);
    recheck = true;
    is_changed = false;
  } else if (!currentlyFollowing and (irWall_RightSensorHistory[0] > irWall_LeftSensorHistory[0])) {
    beep(2);
    recheck = true;
    is_changed = false;
  } else {
    recheck = false;
  }

  // if not initialized, initialize.
  if (!is_init) {

    lcd.setCursor(0, 1);
    lcd.print("init");
    rotateServo(0);
    irWall_ReadSensors(100);

    // do we need to check if the robot is in correct orientation??
    if (irWall_RightSensorHistory[0] < wallExcistThresh) {
      currentlyFollowing = false;
      is_init = true;
      lcd.setCursor(0, 0);
      lcd.print(irWall_RightSensorHistory[0]);
    } else if (irWall_LeftSensorHistory[0] < wallExcistThresh) {
      currentlyFollowing = true;
      is_init = true;

      lcd.setCursor(0, 0);
      lcd.print(irWall_LeftSensorHistory[0]);
    }
    motorWrite(100, 100);
    delay(60);
    motorWrite(0, 0);
    adjustServo(currentlyFollowing);
    return 0;
  }

  // check if there are both left and right walls. if so, switch the wall
  if ((irWall_LeftSensorHistory[0] < wallExcistThresh and irWall_RightSensorHistory[0] < wallExcistThresh) or recheck) {

    if (!is_changed) {
      // rotate the servo to 0 position and check again
      motorWrite(0, 0);
      rotateServo(0);
      irWall_ReadSensors(10);
      if (irWall_LeftSensorHistory[0] < wallExcistThresh and irWall_RightSensorHistory[0] < wallExcistThresh) {
        currentlyFollowing = !currentlyFollowing;
        is_changed = true;
      } else if (currentlyFollowing and (irWall_RightSensorHistory[0] < irWall_LeftSensorHistory[0])) {
        currentlyFollowing = !currentlyFollowing;
        is_changed = true;
      } else if (!currentlyFollowing and (irWall_RightSensorHistory[0] > irWall_LeftSensorHistory[0])) {
        currentlyFollowing = !currentlyFollowing;
        is_changed = true;
      }

      adjustServo(currentlyFollowing);
    }
  } else {
    is_changed = false;
  }

  checkIR();
  if (passedInitialWhiteArea and foundWhite) {
    mode = FINISH_WALL;
    return 0;
  }

  if (currentlyFollowing) {
    ledOn(LED_GREEN);
    irWall_Follow(baseSpeed, LEFT);
  } else {
    ledOff(LED_GREEN);
    irWall_Follow(baseSpeed, RIGHT);
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(irWall_LeftSensorHistory[0]);
  lcd.setCursor(8, 1);
  lcd.print(irWall_RightSensorHistory[0]);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END
