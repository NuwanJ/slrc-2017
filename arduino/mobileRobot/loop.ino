int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:

      //knightRider();

      if (buttonRead(BUTTON_0) == 1) {
        // Button0 Option
        delay(150);
        mode = TEST;

      } else if (buttonRead(BUTTON_1) == 1) {
        // Button1 Option
        beep();

        mode = WALL_FOLLOW;

        delay(150);

      } else if (buttonRead(BUTTON_3) == 1) {
        // Button1 Option
        mode = MAZE_FOLLOW;

      } else if (buttonRead(BUTTON_4) == 1) {
        // Button2 Option
         beep();
        mode = WALL_FOLLOW;

      } else {
        delay(10);
      }
      break;

    //-------------------------------------------------------------------------------------------------------------- Explore the Maze
    case MAZE_FOLLOW:
      mazeFollow();
      break;


    //-------------------------------------------------------------------------------------------------------------- Follow the wall
    case WALL_FOLLOW:
      wallFollow(150); // give the base speed
      delay(300);
      break;

    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      test();
      break;

  }
  displayLoopStatus(mode);
}

boolean detectColorChange(unsigned int *sensor_values) {
  if (sensor_values[0] == 1 && sensor_values[NUM_SENSORS - 1] == 1) {
    return true;
  } else {
    return false;
  }
}

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

      case WALL_FOLLOW:
        Serial.println(F(">>WallFollow"));
        lcdWrite(0, "Mode:WallFollow");
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


}
