int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:


      if (buttonRead(BUTTON_0) == 1) {
        // Button0 Option
        delay(150);
        mode = BEGIN_BIG_BOX;

      } else if (buttonRead(BUTTON_1) == 1) {
        // Button1 Option
        beep();
        mode = ENTER_WALL_FOLLOW;
        delay(150);

      } else if (buttonRead(BUTTON_2) == 1) {
        // Button2 Option
        beep();
        mode = BEFORE_FINAL_TASK;
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
      Serial3.print('h');
      break;

    //-------------------------------------------------------------------------------------------------------------- Explore the Maze
    case MAZE_FOLLOW:

      // Need to write a check statement here to find the white color box
      // If box found, mode= ENTER_WALL_FOLLOW
      mazeFollow();

      break;

    //-------------------------------------------------------------------------------------------------------------- WAIT_UNTIL_FEEDBACK
    case WAIT_UNTIL_FEEDBACK:
      if (millis() - timeOfShootCommand > 25000) {
        // Overflow option for max safety, adjust 12000 if necessary
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

      // Copied from FINISH_MAZE
      motorWrite(150, 150);
      readIRSensors(sensor_values);

      while (allIn == 1) {
        delay(10);
        readIRSensors(sensor_values);
      }
      motorWrite(0, 0);
      delay(300);
      beep(5);
      mode = WALL_FOLLOW;

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
      motorWrite(0, 0);
      beep(5);
      delay(3000);

      motorWrite(150, 150);
      readIRSensors(sensor_values);

      while (allIn == 1) {
        delay(10);
        readIRSensors(sensor_values);
      }
      motorWrite(0, 0);
      delay(300);
      beep(5);
      mode = WALL_FOLLOW;

    // ----------------------------------------------------------------------------------------------------------------Finished wall follow

    case FINISH_WALL:
      motorWrite(0, 0);
      beep(5);
      break;

    case BEFORE_FINAL_TASK:

      readIRSensors(sensor_values);
      if (allIn == 0) {
        motorWrite(0, 0);
        mode = FINAL_TASK;
      } else {
        // Go forward
        motorWrite(150, 150);
        delay(10);
        motorWrite(0, 0);
        delay(20);
      }

    case FINAL_TASK:
      // Go forward until cross line

      readIRSensors(sensor_values);

      if ((sensor_values[0] + sensor_values[5]) >= 1) { //Implement
        motorWrite(150, 150);
        delay(300);

        motorWrite(0, 0);
        delay(1000);
        beep(3);
        mode = FINAL_TASK_FORWARD;
      } else {
        // Need to implement to take 90deg turns
        lineFollow();
      }

      break;

    //--------------------------------------------------------------------------------------------------------------
    case FINAL_TASK_FORWARD:
      fff();
    case FINAL_TASK_FORWARD2:

      readIRSensors(sensor_values);
      irWall_ReadSensors();

      if (allIn == 1) {
        motorWrite(0, 0);
        delay(1000);
        beep(3);
        mode = FINAL;
        // Need to send some detail to stationary robot

        Serial.print("Enter: ");
        Serial.println(finalEnterCounterValue);

        Serial.print("Leave: ");
        Serial.println(finalLeaveCounterValue);

        Serial.print("End: ");
        Serial.println(finalCounter);

        // time taken = finalCounter
        int finalBoxPosition = (finalEnterCounterValue + finalLeaveCounterValue) / 2;

        //int boxRegion = map(finalBoxPosition)

      } else {
        lineFollow();

        finalCounter += 1;

        if ((irWall_LeftSensorHistory[0] < FINAL_BOX_FIND_THRESHOLD) && finalEnterCounterValue == 0) { // FINAL_BOX_FIND_THRESHOLD should be update
          // Enter to box region
          finalEnterCounterValue = finalCounter;

        } else if ((irWall_LeftSensorHistory[0] > FINAL_BOX_FIND_THRESHOLD) && finalEnterCounterValue != 0) {
          // Exit from the box region
          finalLeaveCounterValue = finalCounter;

        } else {
          //Nothing
        }
        delay(10);
      }
      break;

    //--------------------------------------------------------------------------------------------------------------
    case FINAL:
      mode = BEGIN;
      break;

    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      test();

      break;

  }
  displayLoopStatus(mode);
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
