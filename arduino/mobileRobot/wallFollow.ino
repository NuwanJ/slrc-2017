/*---------------------------------------------------------------------------
  Functions
  ---------------------------------------------------------------------------*/

// Contributor :
// Last Update : 27/11/2017

/* Remarks ------------------------------------



  ----------------------------------------------*/


int fitToLeft(int * diff, int baseSpeed) {
  int left, right;
  if (diff[3] < 0 && diff[2] > 0) { // front left is too close to wall. going forward may hit the wall. therefore spin on the spot
    left = -50;
    right = 50;
    motorWrite(1 * left, 1 * right);
    left = 30; right = 30; // go a forward a little
  } else if (diff[2] < 0 && diff[3] > 0) { // back left is too close. if go forward, front may cross the line. spin!
    left = 50;
    right = -50;
    motorWrite(1 * left, 1 * right);
    left = 30; right = 30; // go a forward a little
  } else if (diff[2] < 0 && diff[3] < 0) { // TODO: left side is too close!! what to do???
    left = 0;
    right = 0;
  } else if (diff[2] > diff[3]) { // oriented towards the wall.
    left = baseSpeed;
    right = baseSpeed;
  } else { // oriented outwards to the left wall
    int val = diff[3] * 20 + diff[2] * 10; // more weight to the front sensor
    left = baseSpeed - val;
    right = baseSpeed + val;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(diff[3]);
  lcd.setCursor(0, 1);
  lcd.print(diff[2]);

  lcd.setCursor(0, 0);
  lcd.print(left);
  lcd.setCursor(10, 1);
  lcd.print(right);

  motorWrite(1 * left, 1 * right);
}


int fitToRight(int * diff, int baseSpeed) {

}

int wallFollow(int baseSpeed) {
  int thresh = 5;
  int diff[4];

  for (int i = 0; i < 4; i++) {
    dist[i] = readSonar(i);
    diff[i] = dist[i] - thresh;
  }

  int cost[2]; // cost to fit the robot. 0th-left 1st-right
  cost[0] = abs(diff[2]) + abs(diff[3]);
  cost[1] = abs(diff[0]) + abs(diff[1]);

  if (cost[0] < cost[1]) { // easy to fit the robot to the left wall
    fitToLeft(diff, baseSpeed);
  } else { // easy to fit to right wall
    fitToRight(diff, baseSpeed);
  }


}
