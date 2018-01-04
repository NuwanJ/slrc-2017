/*---------------------------------------------------------------------------
  Functions

  void beep()
  void beep(int count)

  void buttonRead(n)    n = [BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4]

  void ledOb(n)         n = [LED_GREEN, LED_RED]
  void ledOff(n)        n = [LED_GREEN, LED_RED]
  void ledBlink(n,c)    n = [LED_GREEN, LED_RED], c = count

  void knightRider()
  ---------------------------------------------------------------------------*/



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



///----------------------------------------------------------------------------------------------------------- IESL Functions

//  50 | 25 | 00

void rotate90(int dir) {

  // Rotate CCW/CW until middle sensor left line
  linePos = readIRSensors(sensor_values);

  if (dir == CCW) {    // 25 -> 0 -> 50
    while (linePos <= CENTER_EDGE_READING) {
      motorWrite( -1 * baseSpeed, baseSpeed);
      linePos = readIRSensors(sensor_values);
      delay(10);
    }
  } else {             // 25 -> 50 -> 00
    while (linePos >= CENTER_EDGE_READING) {
      motorWrite(baseSpeed, -1 * baseSpeed);
      linePos = readIRSensors(sensor_values);
      delay(10);
    }
  }
  motorStop();
  delay(10);

  // Rotate CCW/CW until robot centered to new line segment

  linePos = readIRSensors(sensor_values);
  while (linePos != CENTER_EDGE_READING) {
    linePos = readIRSensors(sensor_values);

    if (dir == CCW) {
      if (linePos <= CENTER_EDGE_READING) error = 20;
      else error = linePos - CENTER_EDGE_READING;

    } else {
      if (linePos <= CENTER_EDGE_READING) error = -20;
      else error = -1 * (linePos - CENTER_EDGE_READING);

    }
    rightMotorSpeed = baseSpeed / 2 + (error * 10);
    leftMotorSpeed = baseSpeed / 2 - (error * 10);

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }

  motorStop();

}


// few functions used for IESL, copy paste if they are need to use
#ifdef IESL

void findShelf() {

  linePos = readIRSensors(sensor_values);

  // If the robot meets the end, condition satisfy
  while  (sum < 4) { //((allIn || ((linePos >= 30 || linePos <= 20) && sum == 4)) == 0) {
    lineFollow();
    Serial.println(linePos);
    delay(20);
    linePos = readIRSensors(sensor_values);
  }
  motorStop();
  motorWrite(-150, -150);
  delay(70);
  motorStop();
}


void backToPath() {
  //This is enough to take the 180 degree turn
  alignToPath(CCW);
}

/*
  void backToPath() {


  // Go little back before start turn
  motorWrite(-150, -150);
  delay(100);

  // Rotate CCW until robot left line
  linePos = readIRSensors(sensor_values);
  while (allOut == 0) {
    motorWrite(-1 * baseSpeed, baseSpeed);
    delay(10);
    linePos = readIRSensors(sensor_values);
  }
  motorStop();
  //delay(10);

  // Rotate CCW until robot centered to new line segment
  linePos = readIRSensors(sensor_values);

  while (linePos != CENTER_EDGE_READING) {
    if (linePos <= CENTER_EDGE_READING) error = 20;
    else error = linePos - CENTER_EDGE_READING;

    rightMotorSpeed = baseSpeed + (error * 10);
    leftMotorSpeed = baseSpeed - (error * 10);
    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
    linePos = readIRSensors(sensor_values);
  }
  motorStop();

  // Now go forward until robot meet the main line
  linePos = readIRSensors(sensor_values);
  while (leftEnd != 1 && rightEnd != 1) {
    lineFollow();
    delay(10);
    linePos = readIRSensors(sensor_values);
  }

  motorWrite(150, 150);
  delay(100);
  motorStop();
  }*/

void util_readSensorAndUpdateRejectListCW(int* sensor_vals, boolean reject[], int dir) {
  if (dir == CW) {
    readIRSensors(sensor_vals);
    if (sensor_vals[5] == 0) reject[5] = false;
    for (int x = 4; x > -1; x--) {
      if ( (!reject[x + 1]) and (sensor_vals[x] == 0)) {
        reject[x] = false;
      }
    }
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


int util_nonRejectSum(int* array, boolean reject[]) {
  int summ = 0;
  for (int x = 0; x < 6; x++)if (!reject[x])summ += array[x];
  return summ;
}


void alignToPath2(int dir) {
  /*
     New version, uses rejection techniques
     Use this to replace 
            void alignToPath(int dir)
  */


  int motorSpeeds[] = {150, 0};
  int cornerSensor = 5;
  if (dir == CCW) {
    motorSpeeds[0] = 0;
    motorSpeeds[1] = 150;
    cornerSensor = 0;
  }

  boolean reject[] = {true, true, true, true, true, true};

  //Turn until the sensor panel leaves the first line.
  while (!reject[cornerSensor] & (sensor_values[cornerSensor] == 1)) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    readIRSensors(sensor_values);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
  }

  //Turn until the sensor panel finds the new line.
  while (sensor_values[cornerSensor] == 0) {
    motorWrite(motorSpeeds[0], motorSpeeds[1]);
    delay(20);
    motorWrite(0, 0);
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
  }

  //Take the sensor panel a little more into the new line
  motorWrite(motorSpeeds[0], motorSpeeds[1]);
  delay(100); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Tune-able parameter
  motorWrite(0, 0);

  //Now align the robot to the line
  for (int i = 0; i < 5; i++) {
    util_readSensorAndUpdateRejectListCW(sensor_values, reject, dir);
    float s = 0.0f;
    for (int x = 0; x < 6; x++) {
      if (!reject[x]) {
        s += (5 * (x - 2.5) * sensor_values[x]);
      }
    }
    s *= 1.0; //<<<<<<<<<<<<<<<<<<<<<< A TUNE-ABLE PARAMETER
    motorWrite(s * -1, s);
    delay((6 - i) * 10);
  }
  //The sensor panel is alligned to the line, move forward

}
void alignToPath(int dir) {
  /*
     Gihan's 03/01/2017 version
     This should be used to replace the Nuwan's IESL version

     (Test this function for 90deg turns and remove this line)
  */

  if (dir == CW) {
    readIRSensors(sensor_values);
    //Turn until the sensor panel leaves the first line.
    while (sensor_values[5] != 0) {
      motorWrite(150, 0);
      delay(20);
      motorWrite(0, 0);
      readIRSensors(sensor_values);
    }
    //Turn until the sensor panel finds the new line.
    while (sensor_values[5] == 0) {
      motorWrite(150, 0);
      delay(20);
      motorWrite(0, 0);
      readIRSensors(sensor_values);
    }

    //Take the sensor panel a little more into the new line
    motorWrite(150, 0);
    delay(100); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Tune-able parameter
    motorWrite(0, 0);

    //Now align the robot to the line
    for (int i = 0; i < 5; i++) {
      int r = readIRSensors(sensor_values) - 25;
      motorWrite(r, -1 * r);
      delay((6 - i) * 10);
    }
    //The sensor panel is alligned to the line, move forward

  }
  else { //<<<<<<<<<<<<<<<<<<<<<<<<<CCW
    readIRSensors(sensor_values);
    //Turn until the sensor panel leaves the first line.
    while (sensor_values[5] != 0) {
      motorWrite(0, 150);
      delay(20);
      motorWrite(0, 0);
      readIRSensors(sensor_values);
    }
    //Turn until the sensor panel finds the new line.
    while (sensor_values[5] == 0) {
      motorWrite(0, 150);
      delay(20);
      motorWrite(0, 0);
      readIRSensors(sensor_values);
    }

    //Take the sensor panel a little more into the new line
    motorWrite(0, 150);
    delay(100); //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Tune-able parameter
    motorWrite(0, 0);

    //Now align the robot to the line
    for (int i = 0; i < 5; i++) {
      int r = readIRSensors(sensor_values) - 25;
      motorWrite(-1 * r, r);
      delay((6 - i) * 10);
    }
    //The sensor panel is alligned to the line, move forward

  }
}




/*void alignToPath(int dir) {
   Nuwan's IESL version,

  // Rotate CCW/CW until middle sensor left line
  linePos = readIRSensors(sensor_values);

  // Away from line before take the turn
  if (allOut == false) {
    motorWrite(150, 150);
    delay(10);
    linePos = readIRSensors(sensor_values);
  }
  // Rotate CCW/CW until robot centered to new line segment

  linePos = readIRSensors(sensor_values);
  while (linePos != CENTER_EDGE_READING) {
    linePos = readIRSensors(sensor_values);

    if (dir == CCW) {
      if (linePos <= CENTER_EDGE_READING) error = 20;
      else error = linePos - CENTER_EDGE_READING;

    } else {
      if (linePos <= CENTER_EDGE_READING) error = -20;
      else error = -1 * (linePos - CENTER_EDGE_READING);

    }
    rightMotorSpeed = baseSpeed / 2 + (error * 10);
    leftMotorSpeed = baseSpeed / 2 - (error * 10);

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }

  motorStop();
#endif


#ifdef TEMP

//-------------------------------------------------------------------------------------------------------------- Knight Rider : Just for fun
void knightRider() {

  lcdWrite(0, "  Knight Rider");

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(irPins[i], OUTPUT);
    digitalWrite(irPins[i], LOW);
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    digitalWrite(irPins[i], HIGH);
    delay(200);
    digitalWrite(irPins[i], LOW);
  }

  for (int i = 0; i <= NUM_SENSORS; i++) {
    digitalWrite(irPins[NUM_SENSORS - i], HIGH);
    delay(200);
    digitalWrite(irPins[NUM_SENSORS - i], LOW);
  }

}


#endif
