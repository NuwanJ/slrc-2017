/*---------------------------------------------------------------------------
  Functions
  ---------------------------------------------------------------------------*/

// Contributor : harshana
// Last Update : 6/1/2018

/* Remarks ------------------------------------

  ----------------------------------------------*/

int fit(double front, double back, int flag, int baseSpeed) {
  int left, right;
  double thresh = 10;
  if (front < thresh && back > thresh) { // front is too close to wall. going forward may hit the wall. therefore spin
    beep(1);
    lcd.setCursor(0, 0);
    lcd.print("FrontTooClose");
    motorWrite(75 - 75 * flag, 75 + 75 * flag); delay(100); motorWrite(0, 0);

    left = 150; right = 150; // go forward a little

  } else if (front > thresh && back < thresh) { // back is too close. if go forward, front may cross the line. spin!
    beep(1);
    lcd.setCursor(0, 0);
    lcd.print("BackTooClose");
    motorWrite(150, 150); delay(100); motorWrite(0, 0);
    motorWrite(75 + 75 * flag, 75 - 75 * flag); delay(100); motorWrite(0, 0);

    left = 150; right = 150; // go forward a little

  } else if (front < thresh && back < thresh) { // side is too close!! move away
    beep(1);
    lcd.setCursor(0, 0);
    lcd.print("BothTooClose");
    motorWrite(75 - 75 * flag, 75 + 75 * flag); delay(100); motorWrite(0, 0);
    motorWrite(150, 150); delay(50); motorWrite(0, 0);
    left = 75 + 75 * flag; right = 75 - 75 * flag;

  } else if (abs(front - back) > 15) { // diff too much. do the last turn
    beep(2);
    if (currentTurn == -1) {
      motorWrite(-150, 150); delay(50); motorWrite(0, 0);
    } else {
      motorWrite(150, -150); delay(50); motorWrite(0, 0);
    }
    left = 100; right = 100;
  } else if (front >15 and back>15) { // too far away both
    motorWrite(75 + 75 * flag, 75 - 75 * flag); delay(50); motorWrite(0, 0);
    motorWrite(150, 150); delay(50); motorWrite(0, 0);
    left = 75 - 75 * flag; right = 75 + 75 * flag;

  } else {
    double P = (front - back) * flag * 30;
    double I = 0;

    int c = 1;
    for (int i = 0; i < 4; i++) {
      if ((hist[i][0] - hist[i][1] ) > 20) {
        continue;
      }
      I += hist[i][0] - hist[i][1];
      c += 1;
    }
    I /= c;

    I *= 0 * flag;
    Serial.print(P);
    Serial.print(" ");
    Serial.print(I);
    Serial.println("");

    left = baseSpeed + (P + I);
    right = baseSpeed - (P + I);
  }

  motorWrite(left, right);
  delay(50);
  motorWrite(0, 0);

}



void getReadingsFromRotating(double * dist) {
  double minReadingLeft, minReadingRight;
  int minAngleLeft = 0;
  int minAngleRight = 0;


  // finding the left front angle
  minAngleLeft = verifyMinAngle(0, 70, 7 , LEFT);
  minAngleLeft = verifyMinAngle(minAngleLeft - 5, minAngleLeft + 5, 2 , LEFT);
  rotateServo(LEFT, minAngleLeft);
  dist[0] = readSonar(0);
  minReadingLeft = dist[0];
  lcd.setCursor(0, 0);
  lcd.print(dist[0]);

  // finding the right front angle
  minAngleRight = verifyMinAngle(0, 70, 7 , RIGHT);
  minAngleRight = verifyMinAngle(minAngleRight - 5, minAngleRight + 5, 2, RIGHT);
  rotateServo(RIGHT, minAngleRight);
  dist[3] = readSonar(3);
  minReadingRight = dist[3];
  lcd.setCursor(10, 0);
  lcd.print(dist[3]);

  // turning according to the angles and distances got from front sonar
  if (currentlyFollowing) {
    if (minReadingLeft < 15) {
      motorWrite(150, -150);
      delay(50 * minAngleLeft / 10);
      motorWrite(100, 100);
      delay(50);
      motorWrite(0, 0);
      currentTurn = 1;
    } else {
      if (minReadingRight < 15) {
        currentlyFollowing = false;
      } else {
        motorWrite(150, 150);
        delay(250);
        motorWrite(-150, 150);
        delay(50);
        motorWrite(0, 0);
        currentTurn = -1;
      }
    }
  } else {
    if (minReadingRight < 15) {
      motorWrite(-150, 150);
      delay(50 * minAngleRight / 10);
      motorWrite(100, 100);
      delay(50);
      motorWrite(0, 0);
      currentTurn = -1;
    } else {
      if (minReadingLeft < 15) {
        currentlyFollowing = true;
      } else {
        motorWrite(150, 150);
        delay(250);
        motorWrite(150, -150);
        delay(50);
        motorWrite(0, 0);
        currentTurn = 1;
      }
    }
  }
}

int wallFollow(int baseSpeed) {

  if (currentlyFollowing) {
    ledOn(LED_GREEN);
  } else {
    ledOff(LED_GREEN);
  }

  // adjusting the history to add the new entry
  for (int i = 3; i >= 0; i--) {
    for (int j = 0; j < 4; j++) {
      hist[i + 1][j] = hist[i][j];
    }
  }

  // rotate the servo to initial position
  rotateServo(LEFT, 0);
  rotateServo(RIGHT, 0);

  // reading the values
  for (int i = 0; i < 4; i++) {
    dist[i] = readSonar(i);
    if (dist[i] > 200) {
      dist[i] = 200;
    }
    hist[0][i] = dist[i];
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(dist[0]);
  lcd.setCursor(10, 0);
  lcd.print(dist[3]);
  lcd.setCursor(0, 1);
  lcd.print(dist[1]);
  lcd.setCursor(10, 1);
  lcd.print(dist[2]);

  // check if the distances are ok
  if (!verify(dist)) {
    getReadingsFromRotating(dist);
    return 1;
  }
  if (currentlyFollowing) {
    fit(dist[0], dist[1], -1, baseSpeed);
  } else {
    fit(dist[3], dist[2], 1, baseSpeed);
  }


}

int verifyMinAngle(int minAngle, int maxAngle, int steps, int wall) {
  double minDist = 10000000;
  int ans;
  int index;
  if (wall == LEFT) {
    index = 0;
  } else {
    index = 3;
  }

  for (int i = minAngle; i < maxAngle + 1; i += (maxAngle - minAngle) / steps) {
    rotateServo(wall, i);
    dist[index] = readSonar(index);
    if (wall == LEFT) {
      lcd.setCursor(0, 0);
    } else {
      lcd.setCursor(10, 0);
    }
    lcd.print(dist[index]);

    if (dist[index] < minDist) {
      minDist = dist[index];
      ans = i;
    }
  }

  return ans;
}

bool verify(double * dist) {
  if (currentlyFollowing and dist[0] > 30) {
    return false;
  }
  if (!currentlyFollowing and dist[3] > 30) {
    return false;
  }
  return true;

}
