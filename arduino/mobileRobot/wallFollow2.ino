/* --------------------------------------------------------------------------
  Contributor : Gihan
  Last Update : 06/01/2018
  These are the functions written by Hashana, dont mix with what Gihan has written on the file wallFollow.ino

  --------------------------------------------------------------------------*/




/*
   followLeft() is a new function, dont mix this with Harshana's functions
   DO NOT mix the wall_kI,wall_kP,wall_kD with the PID paarameters for maze following :-)
   06/01/2018
*/
float wall_kI = 0.0f, wall_kP = 1.0f, wall_kD = 0.0f;
float prevF[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float prevB[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
int iterWallFollow = 0;
float f = 0, b = 0;

float ff() {
  return f = (float)readSonar(0);
}

float bb() {
  return b = (float)readSonar(1);
}


void followLeftSimple() {
  followLeftSimpleIteration();
}

void showFrontLeftSonar() {
  float dd=10000;
  for(int x=0;x<5;x++){
    dd=min(dd,readSonar(0));
    delay(50);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0); //col, row
  lcd.print(dd);
}

void followLeftSimpleIteration() {
  for (int i = 0; i < 5; i++) {
    delay(1000);
    int diff = ff() - bb();

    lcd.clear();
    lcd.setCursor(0, 0); //col, row
    lcd.print(f);

    lcd.setCursor(0, 1); //col, row
    lcd.print(b);


    if (abs(diff) > 0) {
      if (diff > 0) {
        motorWrite(-150, 150);
      }
      else {
        motorWrite(150, -150);
      }
      delay(80 - (15 * i));
      motorWrite(0, 0);
      beep(2);
      delay(1000);

    }
  }

  motorWrite(150, 150);
  lcdWrite(0, "GoFwd");
  delay(200);
  motorWrite(0, 0);
  delay(100);

}



void followLeft(float front, float back) {
  util_ShiftRight(front, back);
  if (iterWallFollow < 10)iterWallFollow++;
  else {
    iterWallFollow++;
    if (abs(prevF[0] - prevF[1]) > 20) {
      prevF[0] = prevF[1] + 0.7 * (prevF[1] - prevF[2]) + 0.3 * (prevF[2] - prevF[3]);
    }
    if (abs(prevB[0] - prevB[1]) > 20) {
      prevB[0] = prevB[1] + 0.7 * (prevB[1] - prevB[2]) + 0.3 * (prevB[2] - prevB[3]);
    }

    float P_a = prevF[0] - prevB[0];
    float P_b = prevF[0] + prevB[0] - 30.0f;

    float kk = 0.5; //~~~~~~~~~  TUNE-ABLE PARAMETER... kk in (0,1);

    float P = P_a * kk + (1 - kk) * P_b;

    P *= wall_kP;

    motorWrite((int)(sign(P) * 50) + P, (int)(sign(-1 * P) * 50) - P);
    Serial.print((int)(sign(P) * 100) + P); Serial.print(" - "); Serial.println((int)(sign(-1 * P) * 100) - P);
    delay(30);
    motorWrite(0, 0);
    delay(30);
    motorWrite(100, 100);
    delay(100);
    motorWrite(0, 0);
    delay(30);
  }



  Serial.print("wall follow iter: "); Serial.println(iterWallFollow);
  Serial.print("F: "); Serial.print(prevF[0]); Serial.print(" "); Serial.print(prevF[1]); Serial.print(" "); Serial.println(prevF[2]);
  Serial.print("B: "); Serial.print(prevB[0]); Serial.print(" "); Serial.print(prevB[1]); Serial.print(" "); Serial.println(prevB[2]);
}


float sign(float x) {
  if (x > 0.0001f)return 1.0f;
  if (x < -0.0001f)return -1.0f;
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





void followLeft2(){
  for(int i=0;i<9;i++){
    prevF[i+1]=prevF[i];
    prevB[i+1]=prevB[i];
  }
  ff();
  bb();
}


void checkFrontRightSonar(){
  Serial.println(ff());
  delay(100);
}

