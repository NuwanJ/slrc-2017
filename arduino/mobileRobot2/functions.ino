/*---------------------------------------------------------------------------
  Functions

  void beep()
  void beep(int count)

  void buttonRead(n)    n = [BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4]

  void ledOn(n)         n = [LED_GREEN, LED_RED]
  void ledOff(n)        n = [LED_GREEN, LED_RED]
  void ledBlink(n,c)    n = [LED_GREEN, LED_RED], c = count

  void util_readSensorAndUpdateRejectListCW(int* sensor_vals, boolean reject[], int dir)
  void pr(int *sensor_values, boolean reject[])
  int util_nonRejectSum(int* array, boolean reject[])
  int alignToPath(int dir)

  ------------------------------------------------------------------------------------------------------------------------*/

/*
   Procedure to see whether there is a box and get the colour
*/

void backStep() {
  // for backToMaze only
  motorWrite(0, 0);
  motorReverse(150);
  delay(10);
  motorWrite(0, 0);
  delay(40);
}


void rotateServo(int deg) {

  // -85 <--- 0 ---> 85

  deg = max(-85, deg);
  deg = min(85, deg);

  deg = (-1 * deg) + 90 + 0; // 6 = +correction moves servo to < side

  servoMotor.attach(PIN_SERVO);
  servoMotor.write(deg);
  delay(500); // Need to give enough time to rotate eto it's destination
  servoMotor.detach();
}

int findBox() {
  motorWrite(0, 0);
  delay(1000);
  float ir_FrontThresoldForBox = 500.0f;


  int TRIES = 12; //This is a TUNE-ABLE parameter
  float COLOUR_CONFIDENCE = 0.7; ////This is a TUNE-ABLE parameter
  int STEPS = 13; //This is the number of steps the robot is going to go forward looking for a box;
  int boxFound = 0;
  int rFound = 0, gFound = 0, bFound = 0;

  /*

    irWall_ReadSensors(10);
    Serial.print("The IR reading of box infront is: ");
    Serial.println(irWall_FrontSensorHistory[0]);

    if(irWall_FrontSensorHistory[0]>ir_FrontThresoldForBox){
      return COLOR_OPEN;
    }

  */
  readIRSensors(sensor_values);
  int s = 0;
  while (allOut & s < STEPS) {
    motorWrite(120, 120);
    delay(20);
    motorWrite(0, 0);
    delay(50);
    readIRSensors(sensor_values);
    s++;
  }

  if (!isBoxFound())return COLOR_OPEN;
  else {
    for (int t = 0; t < TRIES; t++) {
      switch (readBoxColor()) {
        case COLOR_RED:
          rFound++;
        case COLOR_GREEN:
          gFound++;
        case COLOR_BLUE:
          bFound++;
      }
    }
    if (rFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_RED;
    if (gFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_GREEN;
    if (bFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_BLUE;
  }
  return COLOR_OPEN;
}
int findBoxOld() {
  /*
     This function checks whether there is a box or not,
     The robot will go fowards for a few steps to check
  */
  int TRIES = 10; //This is a TUNE-ABLE parameter
  float COLOUR_CONFIDENCE = 0.7; ////This is a TUNE-ABLE parameter
  int STEPS = 10; //This is the number of steps the robot is going to go forward looking for a box;
  int boxFound = 0;


  for (int s = 0; s < STEPS; s++) {
    goForward();
    if (isBoxFound() || isBoxFound() || isBoxFound()) {
      int rFound = 0, gFound = 0, bFound = 0;

      for (int t = 0; t < TRIES; t++) {
        switch (readBoxColor()) {
          case COLOR_RED:
            rFound++;
          case COLOR_GREEN:
            gFound++;
          case COLOR_BLUE:
            bFound++;
        }
      }
      if (rFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_RED;
      if (gFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_GREEN;
      if (bFound > (int)(COLOUR_CONFIDENCE * TRIES))return COLOR_BLUE;


    }

  }
  return COLOR_OPEN;

}











//------------------------------------------------------------------------------------------------------------------------------
void util_readSensorAndUpdateRejectListCW(int* sensor_vals, boolean reject[], int dir) {
  if (dir == CW) {
    readIRSensors(sensor_vals);
    if (sensor_vals[5] == 0) reject[5] = false;
    for (int x = 4; x > -1; x--) {
      if ( (!reject[x + 1]) and (sensor_vals[x] == 0)) {
        reject[x] = false;
      }
    }
    printArray(SERIAL_PORT, sensor_vals, 6);
    printArray(SERIAL_PORT, reject, 6);
  }
  else {
    readIRSensors(sensor_vals);
    if (sensor_vals[0] == 0) reject[0] = false;
    for (int x = 1; x < 6; x++) {
      if ( (!reject[x - 1]) and (sensor_vals[x] == 0)) {
        reject[x] = false;
      }
    }
  }
}

void pr(int *sensor_values, boolean reject[]) {
  Serial.print("S: "); Serial.print(sensor_values[0]); Serial.print(sensor_values[1]); Serial.print(sensor_values[2]); Serial.print(sensor_values[3]); Serial.print(sensor_values[4]); Serial.print(sensor_values[5]); Serial.print('\n');
  Serial.print("R: "); Serial.print(reject[0]); Serial.print(reject[1]); Serial.print(reject[2]); Serial.print(reject[3]); Serial.print(reject[4]); Serial.print(reject[5]); Serial.print('\n');
}


int util_nonRejectSum(int* array, boolean reject[]) {
  int summ = 0;
  for (int x = 0; x < 6; x++)if (!reject[x])summ += array[x];
  return summ;
}


void alignToPath(int dir) {
  /*
     New version, uses rejection techniques
     Use this to replace
            void alignToPath(int dir)
  */

  beep(1);
  delay(250);
  int motorSpeeds[] = { 150, -150};
  int cornerSensor = 5;
  if (dir == CCW) {
    motorSpeeds[0] *= -1;
    motorSpeeds[1] *= -1;
    cornerSensor = 0;
  }

  readIRSensors(sensor_values);
  while (sensor_values[cornerSensor] == 1) {
    goForward();
    readIRSensors(sensor_values);
    if (checkEnd())return;
  }

  boolean reject[] = {true, true, true, true, true, true};

  //Turn until the sensor panel leaves the first line.
  Serial.println("Turn until the sensor panel leaves the first line.");
  while (reject[cornerSensor]) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    delay(50);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
    if (allIn)if (checkEnd())return;
  }
  motorWrite(0, 0);

  delay(500);

  //Turn until the sensor panel finds the new line.
  Serial.println("Turn until the sensor panel finds the new line.");
  int i = 0;
  while (util_nonRejectSum(sensor_values, reject) == 0) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    delay(20);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
    i++;
    if (i >= 10) {
      //for(int x=0;x<6;x++)reject[x]=false;
    }
  }


  Serial.println("Take the sensor panel a little more into the new line");
  //Take the sensor panel a little more into the new line
  motorWrite(motorSpeeds[0], motorSpeeds[1]);
  delay(20);
  motorWrite(0, 0);
  delay(500);


  //Now align the robot to the line
  i = 0;

  while (true && i < 10) {
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
    int s = 0;
    for (int x = 0; x < 6; x++) {
      if (!reject[x]) {
        s += ( (10 * x - 25) * sensor_values[x]);
      }
    }

    if (s > 5) {
      motorWrite(100, -100);
    }
    else if (s < - 5) {
      motorWrite(-100, 100);
    }
    else {
      motorWrite(0, 0);
      break;
    }

    delay(50);
    motorWrite(0, 0);
    delay(20);
    i = i + 1;
    beep(1);
  }
  //The sensor panel is alligned to the line, move forward

}





//-------------------------------------------------------------------------------------------------------------- Beep
void beep() {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(DELAY_BUZZER);
  digitalWrite(PIN_BUZZER, LOW);
  delay(DELAY_BUZZER);
}

void beep(int count) {
  for (int i = 0; i < count; i++) {
    beep();
  }
}

//-------------------------------------------------------------------------------------------------------------- Button Read

int buttonRead(int btn) {

  if (btn == BUTTON_3 || btn == BUTTON_4) {
    return 0;//(analogRead(btn) == 0);
  } else {
    return (1 - digitalRead(btn));
  }
}

//-------------------------------------------------------------------------------------------------------------- LED On/ Off/ Blink
void ledOn(int n) {
  digitalWrite(n, HIGH);
}

void ledOff(int n) {
  digitalWrite(n, LOW);
}

void ledBlink(int n) {
  digitalWrite(n, HIGH);
  delay(DELAY_BLINK);
  digitalWrite(n, LOW);
}

void ledBlink(int n, int count) {

  for (int i = 0; i < count; i++) {
    ledBlink(n);
    delay(DELAY_BLINK);
  }
}

//---------------------------------------------------------------------------------------------------
void beginBigBox() {
  readIRSensors(sensor_values);
  while (allIn) {
    goForward();
    readIRSensors(sensor_values);
  }
}

//-------------------------------------------------------------------------------------------------------

boolean checkEnd() {
  int T = 4;
  int allInCount = 0;
  for (int tt = 0; tt < T; tt++) {
    int sum = 0;
    for (int x = 0; x < 6; x++)sum += irHistory[tt][x];
    if (sum == 6)allInCount++;
  }

  if (allInCount == T - 1) {
    mode = FINISH_MAZE;
    return true;
  }
  else {
    return false;
  }



}


float sign(float x) {
  if (x > 0.0001f)return 1.0f;
  if (x < -0.0001f)return -1.0f;
  return 0.0f;
}



// Discontinued function
void rotateServo(int n, int deg) {
  /*deg = max(-90, deg);
    deg = min(90, deg);

    deg = 90 - deg;
    if (n == LEFT) {
    //  < =90  ^=10 a   \|/=170
    leftServo.attach(18);
    leftServo.write(deg);
    } else {
    rightServo.attach(19);
    rightServo.write(180 - deg);
    }
    delay(500);

    leftServo.detach();
    rightServo.detach();*/
}


void fff() {
  readIRSensors(sensor_values);
  while (arsum(sensor_values) >= 4) {
    motorWrite(150, 150);
    delay(10);
    motorWrite(0, 0);
    delay(40);
    readIRSensors(sensor_values);
  }
  readIRSensors(sensor_values);



  while (sensor_values[0] == 0) {
    motorWrite(150, 150);
    delay(10);
    motorWrite(0, 0);
    delay(40);
    readIRSensors(sensor_values);
  }
  motorWrite(0, 0);
  delay(200);

  alignToPath(CCW);

  readIRSensors(sensor_values);
  while (arsum(sensor_values) < 5) {
    lineFollow();
    delay(10);
    motorWrite(0, 0);
    delay(40);
    readIRSensors(sensor_values);
  }
  beep(1);

  float boxThres = 700.0f;
  int state = 0;
  int cc = 0;
  int cEnter, cLeave, cEnd;




  readIRSensors(sensor_values);
  for (int x = 0; x < 10; x++) {
    lineFollow();
    delay(20);
    motorWrite(0, 0);
    delay(40);
    readIRSensors(sensor_values);
    cc++;
    irWall_ReadSensors(10);

  }

  while (arsum(sensor_values) < 4) {
    lineFollow();
    delay(20);
    motorWrite(0, 0);
    delay(40);
    readIRSensors(sensor_values);
    cc++;

    irWall_ReadSensors(10);

    //  Serial.println(irWall_LeftSensorHistory[0]);
    if (state == 0) {
      if (irWall_LeftSensorHistory[0] < boxThres) {
        state = 1;
        cEnter = cc;
      }
    }
    else if (state == 1) {
      if (irWall_LeftSensorHistory[0] > boxThres) {
        state = 2;
        cLeave = cc;
      }
    }
    else if (state = 2) {
      readIRSensors(sensor_values);
      if (arsum(sensor_values) >= 4) {
        cEnd = cc;
        motorWrite(0, 0);
        break;
      }
    }
  }

  motorWrite(0, 0);
  beep(10);
  Serial.print("Enter :"); Serial.print(cEnter); Serial.print(" ");
  Serial.print(" Leave :"); Serial.print(cLeave); Serial.print(" ");
  Serial.print(" End :"); Serial.print(cEnd); Serial.println(" ");

}

