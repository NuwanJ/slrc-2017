/*---------------------------------------------------------------------------
  /* --------------------------------------------------------------------------
  Contributor : Harshana
  Last Update : 06/01/2018
  /* --------------------------------------------------------------------------*/

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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(diff[0]);
  lcd.setCursor(0, 1);
  lcd.print(diff[1]);
  lcd.setCursor(10, 0);
  lcd.print(diff[3]);
  lcd.setCursor(10, 1);
  lcd.print(diff[2]);

  int cost[2]; // cost to fit the robot. 0th-left 1st-right
  cost[0] = diff[0] + diff[1];
  cost[1] = diff[2] + diff[3];

  if (1 || cost[0] < cost[1]) { // easy to fit the robot to the left wall
    fitToLeft(diff, baseSpeed);
  } else { // easy to fit to right wall
    //fitToRight(diff, baseSpeed);
  }


}


/*
 * THE CODE BELOW THIS SHOULD NOT BE MIXED WITH HARSHANA'S CODE
 */






/*
   followLeft() is a new function, dont mix this with Harshana's functions
   DO NOT mix the wall_kI,wall_kP,wall_kD with the PID paarameters for maze following :-)
   06/01/2018
*/
float wall_kI = 0.0f, wall_kP = 1.0f, wall_kD = 0.0f;
float prevF[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float prevB[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

int iterWallFollow = 0;

void followLeft(float front, float back) {
  util_ShiftRight(front, back);
  if (iterWallFollow < 10)iterWallFollow++;
  else {
    if (abs(prevF[0] - prevF[1]) > 20) {
      prevF[0] = prevF[1] + 0.7 * (prevF[1] - prevF[2]) + 0.3 * (prevF[2] - prevF[3]);
    }
    if (abs(prevB[0] - prevB[1]) > 20) {
      prevB[0] = prevB[1] + 0.7 * (prevB[1] - prevB[2]) + 0.3 * (prevB[2] - prevB[3]);
    }

    float P_a = prevF[0] - prevB[0];
    float P_b = prevF[0] + prevB[0] - 20.0f;

    float kk = 0.5; //~~~~~~~~~  TUNE-ABLE PARAMETER... kk in (0,1);

    float P = P_a * kk + (1 - kk) * P_b;

    P*=wall_kP;
    motorWrite((int)(sign(P)*100)+P,(int)(sign(-1*P)*100)-P);
    delay(30);
    motorWrite(0,0);
    delay(30);
  }


}


float sign(float x){
  if(x>0.0001f)return 1.0f;
  if(x<-0.0001f)return -1.0f;
  return 0.0f;
}

void util_ShiftRight(float front, float back) {
  for (int x = 9; x > 0; x--) {
    prevF[x] = prevF[x - 1];
    prevB[x] = prevB[x - 1];
  }
  prevF[0] = front;
  prevB[0] = back;
}
