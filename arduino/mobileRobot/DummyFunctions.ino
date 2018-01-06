/*---------------------------------------------------------------------------
  Functions

  void turnCW(int deg)
  int arsum(int ar[])
  int arsum(unsigned int ar[])
  goForward()
  goBack()

  ---------------------------------------------------------------------------*/


void turnCW(int deg) {
  //This function should turn the robot CW by deg
  //Should work for both positive and negative values of deg

  if (deg == 45) {
    motorWrite(100, -100);
    delay(500);
  }
  else if (deg == 90) {
    motorWrite(100, -100);
    delay(750);

  }
  else if (deg == -90) {
    motorWrite(-100, 100);
    delay(750);

  }
  else if (deg == 180) {
    motorWrite(100, -100);
    delay(1500);

  }
  motorWrite(0, 0);
}

int arsum(int ar[]) {
  //This should work for both arrays and pointers
  int ssum = 0;
  for (int x = 0; x < 6; x++)ssum += ar[x];
  return ssum;
}

int arsum(unsigned int ar[]) {
  //This should work for both arrays and pointers
  int ssum = 0;
  for (int x = 0; x < 6; x++)ssum += ar[x];
  return ssum;
}

void goForward() {
  //The robot should go one step forward. This is to ignore the turns to left while following lines
  motorWrite(200, 200);

}


void goBack() {
  //The robot should go back just one step
  motorWrite(-200, -200);
}

