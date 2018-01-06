/*---------------------------------------------------------------------------
  Functions
---------------------------------------------------------------------------*/

// Contributor : harshana
// Last Update : 5/1/2018

/* Remarks ------------------------------------



----------------------------------------------*/

int fitpid(int front, int back, int flag, int baseSpeed){
  
  return 0;
}

int fit(int front, int back, int flag, int baseSpeed){
  int left,right;
  if (front>0 && back<0){ // front is too close to wall. going forward may hit the wall. therefore spin
    motorWrite(75-75*flag,75+75*flag);
    delay(50);
    motorWrite(0,0);
    
    left=150;right=150; // go forward a little
  }else if (back>0 && front<0){ // back is too close. if go forward, front may cross the line. spin!
    motorWrite(75+75*flag,75-75*flag);
    delay(50);
    motorWrite(0,0);
    
    left=150;right=150; // go forward a little
  }else if (front>0 && back>0){ // TODO: side is too close!! what to do???
    motorWrite(75-75*flag,75+75*flag);
    delay(50);
    motorWrite(0,0);
    l eft = 0;
    right = 0;
  }else if (back == front){ // oriented towards the wall.
    left = baseSpeed;
    right = baseSpeed;
  }else if (back < front){
    left=150;
    right=0;  
  }else{ // oriented outwards to the wall
    int val = -1*(front*50 + back*10); // more weight to the front sensor
    left = baseSpeed - val*flag;
    right = baseSpeed + val*flag;

    left=0;
    right=150;
  }
  motorWrite(left,right);
  delay(50);
  motorWrite(0,0);
    
}

int fitToLeft(int * diff, int baseSpeed){
  fit(diff[0], diff[1], -1, baseSpeed);
  //fitpid(diff[0], diff[1], -1, baseSpeed);
}


int fitToRight(int * diff, int baseSpeed){
  fit(diff[3], diff[2], 1, baseSpeed);
}

int wallFollow(int baseSpeed){
  int thresh = 10;
  int diff[4];
  
  for (int i=0;i<4;i++){
    dist[i] = readSonar(i);
    if (dist[i]>200){
      motorWrite(0,0);
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

  if (1 || cost[0] < cost[1]){ // easy to fit the robot to the left wall
    fitToLeft(diff, baseSpeed);
  }else{ // easy to fit to right wall
    //fitToRight(diff, baseSpeed);
  }
  
  
}
