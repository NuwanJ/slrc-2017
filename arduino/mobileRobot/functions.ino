/*---------------------------------------------------------------------------
  Functions

  void beep()
  void beep(int count)

  void buttonRead(n)    n = [BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4]

  void ledOb(n)         n = [LED_GREEN, LED_RED]
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

void rotateServo(int n, int deg) {

  deg = max(10, deg);
  deg = min(170, deg);

  if (n == LEFT) {
    //  < =90  ^=10    \|/=170
    leftServo.attach(18);
    leftServo.write(deg);
  } else {
    rightServo.attach(19);
    rightServo.write(180 - deg);
  }
  delay(500);

  leftServo.detach();
  rightServo.detach();
}


int findBox() {
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

  boolean reject[] = {true, true, true, true, true, true};

  //Turn until the sensor panel leaves the first line.
  Serial.println("Turn until the sensor panel leaves the first line.");
  while (reject[cornerSensor]) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    delay(50);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
  }
  motorWrite(0, 0);



  beep(2);
  delay(500);

  //Turn until the sensor panel finds the new line.
  Serial.println("Turn until the sensor panel finds the new line.");
  while (util_nonRejectSum(sensor_values, reject) == 0) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    delay(20);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);

  }


  Serial.println("Take the sensor panel a little more into the new line");
  //Take the sensor panel a little more into the new line
  motorWrite(motorSpeeds[0], motorSpeeds[1]);
  delay(20);
  motorWrite(0, 0);
  delay(50);

  beep(3);
  delay(500);


  //Now align the robot to the line
  int i = 0;

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
  lcdWrite(1, "----");

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

