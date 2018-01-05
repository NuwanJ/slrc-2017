/*---------------------------------------------------------------------------
  Functions
---------------------------------------------------------------------------*/

// Contributor : harshana
// Last Update : 5/1/2018

/* Remarks ------------------------------------



----------------------------------------------*/
int fit(int front, int back, int flag, int baseSpeed){
  int left,right;
  if (front<0 && back>0){ // front is too close to wall. going forward may hit the wall. therefore spin
    motorWrite(-50*flag,50*flag);
    left=30;right=30; // go forward a little
  }else if (back<0 && front>0){ // back is too close. if go forward, front may cross the line. spin!
    motorWrite(50*flag,-50*flag);
    left=30;right=30; // go forward a little
  }else if (front<0 && front<0){ // TODO: side is too close!! what to do???
    left = 0;
    right = 0;
  }else if (back > front){ // oriented towards the wall.
    left = baseSpeed;
    right = baseSpeed;
  }else{ // oriented outwards to the wall
    int val = diff[0]*20 + diff[1]*10; // more weight to the front sensor
    left = baseSpeed - val*flag;
    right = baseSpeed + val*flag;
  }
  motorWrite(left,right);
}

int fitToLeft(int * diff, int baseSpeed){
  fit(diff[0], diff[1], 1, baseSpeed);
}


int fitToRight(int * diff, int baseSpeed){
  fit(diff[3],diff[2],-1,baseSpeed);
}

int wallFollow(int baseSpeed){
  int thresh = 5;
  int diff[4];
  
  for (int i=0;i<4;i++){
    dist[i] = readSonar(i);
    diff[i] = dist[i] - thresh;
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
  
  motorWrite(0,0);
  delay(1000);
  int cost[2]; // cost to fit the robot. 0th-left 1st-right
  cost[0] = abs(diff[0]) + abs(diff[1]);
  cost[1] = abs(diff[2]) + abs(diff[3]);

  if (cost[0] < cost[1]){ // easy to fit the robot to the left wall
    fitToLeft(diff, baseSpeed);
  }else{ // easy to fit to right wall
    fitToRight(diff, baseSpeed);
  }
  
  
}
