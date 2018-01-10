/*---------------------------------------------------------------------------
  Functions

  void turnCW(int deg)
  int arsum(int ar[])
  int arsum(unsigned int ar[])
  goForward()
  goBack()

  ---------------------------------------------------------------------------*/




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
  delay(20);
  motorWrite(0,0);
  delay(50);

}


void takeOneStepBack() {
  //The robot should go one step forward. This is to ignore the turns to left while following lines
  motorWrite(-200, -200);
  delay(20);
  motorWrite(0,0);
  delay(50);

}

void goBack() {
  //The robot should go back just one step
  motorWrite(-200, -200);
}

