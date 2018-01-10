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
  motorWrite(0, 0);
  delay(50);

}


void takeOneStepBack() {
  //The robot should go one step forward. This is to ignore the turns to left while following lines
  motorWrite(-200, -200);
  delay(20);
  motorWrite(0, 0);
  delay(50);

}

void goBack() {
  //The robot should go back just one step
  motorWrite(-200, -200);
}
























// !!! Don't add functions here, this section is only for display status !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void displayLoopStatus(int mode) {

  if (mode != oldMode) {
    oldMode = mode;
    Serial.println(F("--------------------------------------------------"));
    switch (mode) {
      case BEGIN:
        Serial.println(F("BEGIN"));
        //lcdWrite(0,"Mode: Begin");
        break;

      case MAZE_FOLLOW:
        Serial.println(F(">>MazeFollow"));
        lcdWrite(0, "Mode:MazeFollow");
        break;

      case WAIT_UNTIL_FEEDBACK:
        Serial.println(F(">>Wait until a feedback"));
        lcdWrite(0, "Mode:WaitFeed");
        break;

      case ENTER_WALL_FOLLOW:
        Serial.println(F(">>Enter to wall following mode"));
        lcdWrite(0, "Mode:EnterWall");
        break;

      case LINE_FOLLOW:
        Serial.println(F(">>LineFollow"));
        lcdWrite(0, "Mode:LineFollow");
        break;

      case WALL_FOLLOW:
        Serial.println(F(">>WallFollow"));
        lcdWrite(0, "Mode:WallFollow");
        break;

      case RETURN_TO_MAZE:
        Serial.println(F(">>Return to Maze"));
        lcdWrite(0, "Mode:ReturnMaze");
        break;

      case TEST:
        Serial.println(F("TEST"));
        lcdWrite(0, "Mode: Test");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {
  //TODO: Need to implement a debugging

}

