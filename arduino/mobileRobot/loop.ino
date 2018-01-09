

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
    
      if (buttonRead(BUTTON_0) == 1) {
        // Button0 Option
        delay(150);
        mode = TEST;

      } else if (buttonRead(BUTTON_1) == 1) {
        // Button1 Option
        beep();
        mode = BEGIN_BIG_BOX;
        delay(150);

      } else if (buttonRead(BUTTON_2) == 1) {
        // Button2 Option
        beep();
        mode = WALL_FOLLOW;
        delay(150);

      } else if (buttonRead(BUTTON_3) == 1) {   // Temporally not working
        beep();

      } else if (buttonRead(BUTTON_4) == 1) {   // Temporally not working
        // Button2 Option
        beep();

      } else {
        delay(10);
      }
      break;
    //-------------------------------------------------------------------------------------------------------------- Start here
    case BEGIN_BIG_BOX:
      beginBigBox();
      mode = MAZE_FOLLOW;
      break;

    //-------------------------------------------------------------------------------------------------------------- Explore the Maze
    case MAZE_FOLLOW:

      // Need to write a check statement here to find the white color box
      // If box found, mode= ENTER_WALL_FOLLOW
      mazeFollow();

      break;

    //-------------------------------------------------------------------------------------------------------------- WAIT_UNTIL_FEEDBACK
    case WAIT_UNTIL_FEEDBACK:
      if (millis() - timeOfShootCommand > 20000) {
        beep(3);
        mode = RETURN_TO_MAZE;
      }

      delay(1000);
      beep();
      break;

    //-------------------------------------------------------------------------------------------------------------- RETURN_TO_MAZE
    case RETURN_TO_MAZE:
      returnToMaze();
      mode = MAZE_FOLLOW;

      break;

    //-------------------------------------------------------------------------------------------------------------- Enter to the wall following mode
    case ENTER_WALL_FOLLOW:

      // Do necessary arrangements to enter wall following mode
      // after, mode = WALL_FOLLOW;
      delay(300);
      break;

    //-------------------------------------------------------------------------------------------------------------- Follow the wall
    case WALL_FOLLOW:

      // Need to implement a statement to detect the end of the wall section, then need to align the robot to path again and line follow
      // Then mode = ??

      wallFollow(150); // base speed
      delay(100);

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow the Line
    case LINE_FOLLOW:
      lineFollow();
      delay(50);

      break;

    //-------------------------------------------------------------------------------------------------------------- Finish the maze
    case FINISH_MAZE:
      while (true) {
        beep(3);
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      test();

      break;

  }
  displayLoopStatus(mode);
}




