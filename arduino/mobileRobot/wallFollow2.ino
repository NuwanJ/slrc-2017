

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~START

// Pin numbers moved to define.h tab, otherwise it gives some compile errors

float irWall_SensorAdaptiveFactor = 0.1;
float irWall_kP = 10.0f, irWall_kD = 0.0f, irWall_kI = 0.0f;

float irWall_expectedReading = 700.0f;


void irWall_ReadSensors() {
  for (int x = 9; x > 0; x--) {
    irWall_LeftSensorHistory[x] = irWall_LeftSensorHistory[x-1];
    irWall_RightSensorHistory[x] = irWall_RightSensorHistory[x-1];
    irWall_FrontSensorHistory[x] = irWall_FrontSensorHistory[x-1];
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
  /*
   * GIHAN'S single iteration of PID algo
   * Should be used with both HARSHANA's wallFollow(int baseSpeed) and GIHAN's irWall_WallFollow()
   */
  
  irWall_ReadSensors(10);


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


void irWall_WallFollow() {
  /*
   * GIHAN'S FUNCTION. Do Not mix with HARSHANA's wallFollow(int baseSpeed)
   */
  
  int currentSide = RIGHT;
  while (true) {
    irWall_ReadSensors(10);
    if (currentSide==RIGHT && irWall_RightSensorHistory[0] >= irWall_LeftSensorHistory[0]) {
      motorWrite(0, 0);
      int i = 0, shouldTurn = 1;
      for (i = 0; i < 10; i++) {
        goForward();
        irWall_ReadSensors(10);
        if (irWall_RightSensorHistory[0] >= irWall_LeftSensorHistory[0])shouldTurn++;
      }
      if (shouldTurn > 8) {

        currentSide = LEFT;
        beep(3);
      }
    }
    irWall_Follow(80, currentSide);
  }
}




int wallFollow(int baseSpeed) {
  /*
   * HARSHANA'S FUNCTION. Do Not mix with GIHAN's irWall_WallFollow()
   */
  
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

  }

  if (currentlyFollowing) {
    rotateServo(LEFT, 45);
    ledOn(LED_GREEN);
    irWall_Follow(baseSpeed, LEFT);
  } else {
    ledOff(LED_GREEN);
    irWall_Follow(baseSpeed, RIGHT);
  }

}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~IR WALL FOLLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END



