/*---------------------------------------------------------------------------
  Functions
  ---------------------------------------------------------------------------*/

// Contributor : harshana
// Last Update : 6/1/2018

/* Remarks ------------------------------------
 *  These are the functions written by Hashana, dont mix with what Gihan has written on the file wallFollow2.ino
  ----------------------------------------------*/

int fit(double front, double back, int flag, int baseSpeed) {
  int left, right;
  double thresh = 10;
  if (front < thresh && back > thresh) { // front is too close to wall. going forward may hit the wall. therefore spin
    beep(1);
    motorWrite(75 - 75 * flag, 75 + 75 * flag); delay(50); motorWrite(0, 0);

    left = 150; right = 150; // go forward a little

  } else if (front > thresh && back < thresh) { // back is too close. if go forward, front may cross the line. spin!
    beep(1);
    motorWrite(75 + 75 * flag, 75 - 75 * flag); delay(50); motorWrite(0, 0);

    left = 150; right = 150; // go forward a little

  } else if (front < thresh && back < thresh) { // TODO: side is too close!! what to do???
    beep(1);
    motorWrite(75 - 75 * flag, 75 + 75 * flag); delay(50); motorWrite(0, 0);
    left = 0; right = 0;

  } else {
    if (abs(front - back) > 5) {
      beep(2);
      front = 0; back = 0;
      return ; //<<<<< @Harshana: There is a mistake on ur https://github.com/harshana95/slrc-2017/blob/master/arduino/mobileRobot/wallFollow.ino
    }
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

    left = baseSpeed - (P + I);
    right = baseSpeed + (P + I);
  }
  motorWrite(left, right);
  delay(50);
  motorWrite(0, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(left);
  lcd.setCursor(10, 0);
  lcd.print(right);
  lcd.setCursor(0, 1);
  lcd.print(front);
  lcd.setCursor(10, 1);
  lcd.print(back);

}


int wallFollowSonar(int baseSpeed) {
  int thresh = 10;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      hist[i][j] = hist[i + 1][j];
    }
  }

  for (int i = 0; i < 4; i++) {
    dist[i] = readSonar(i);
    if (dist[i] > 200) {
      dist[i] = 200;
    }
    hist[4][i] = dist[i];
  }
  
  
  
  
  
    int cost[2]; // cost to fit the robot. 0th-left 1st-right
    cost[0] = dist[0] + dist[1];
    cost[1] = dist[2] + dist[3];

    if (1 || cost[0] < cost[1]) { // easy to fit the robot to the left wall
      fit(dist[0], dist[1], -1, baseSpeed);
    } else { // easy to fit to right wall
      //fit(dist[3], dist[2], 1, baseSpeed);
    }
  
}



/*
int wallFollow(int baseSpeed) {
  int thresh = 10;
  int diff[4];

  for (int i = 0; i < 4; i++) {
    dist[i] = readSonar(i);
    if (dist[i] > 200) {
      motorWrite(0, 0);
      return -1;
    }
    diff[i] = thresh - dist[i];
  }
  followLeft(dist[0], dist[1]);
}
*/
int fitpid(int front, int back, int flag, int baseSpeed) {

  return 0;
}

int fit(int front, int back, int flag, int baseSpeed) {
  int left, right;
  if (front > 0 && back < 0) { // front is too close to wall. going forward may hit the wall. therefore spin
    motorWrite(75 - 75 * flag, 75 + 75 * flag);
    delay(50);
    motorWrite(0, 0);

    left = 150; right = 150; // go forward a little
  } else if (back > 0 && front < 0) { // back is too close. if go forward, front may cross the line. spin!
    motorWrite(75 + 75 * flag, 75 - 75 * flag);
    delay(50);
    motorWrite(0, 0);

    left = 150; right = 150; // go forward a little
  } else if (front > 0 && back > 0) { // TODO: side is too close!! what to do???
    motorWrite(75 - 75 * flag, 75 + 75 * flag);
    delay(50);
    motorWrite(0, 0);
    left = 0;
    right = 0;

  } else if (back == front) { // oriented towards the wall.
    left = baseSpeed;
    right = baseSpeed;
  } else if (back < front) {
    left = 150;
    right = 0;
  } else { // oriented outwards to the wall
    int val = -1 * (front * 50 + back * 10); // more weight to the front sensor
    left = baseSpeed - val * flag;
    right = baseSpeed + val * flag;

    left = 0;
    right = 150;
  }
  motorWrite(left, right);
  delay(50);
  motorWrite(0, 0);

}

int fitToLeft(int * diff, int baseSpeed) {
  fit(diff[0], diff[1], -1, baseSpeed);
  //fitpid(diff[0], diff[1], -1, baseSpeed);
}


int fitToRight(int * diff, int baseSpeed) {
  fit(diff[3], diff[2], 1, baseSpeed);
}
