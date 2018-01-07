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
      return;u
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


int wallFollow(int baseSpeed) {
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