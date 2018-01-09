
/* --------------------------------------------------------------------------
  Contributor : Gihan
  Last Update : 06/01/2018
  --------------------------------------------------------------------------*/
  
boolean util_missedWallToLeft() {
  //A small calculation to see whether there was a turn to right
  int a = 0, b = 0;
  for (int x = 0; x < 5; x++) {
    a = max(a, irHistory[x][0]);
    b = max(b, irHistory[x][1]);
  }
  return (a + b) == 2;
}

void mazeFollow() {

  pos = readIRSensors(sensor_values);
  error = (pos - CENTER_EDGE_READING);
  Serial.println(irLineString);

  if (allIn) {
    if(checkEnd())return;
  }

  if (sensor_values[5] == 1) {
    goForward(); goForward(); goForward();goForward(); goForward(); goForward();
    alignToPath(CW);
  }
  else if (allOut) {
    if (util_missedWallToLeft()) {
      goForward();
      alignToPath(CCW); // take a 90deg CCW turn
    }
    else {
      motorWrite(0, 0);
      int boxColor = findBox();

      if (boxColor != COLOR_OPEN)shoot(boxColor);
      else mode = RETURN_TO_MAZE;

    }
  }
  else if (sensor_values[0] == 1) {
    goForward();
  }
  else {
    lineFollow(); //Just one step
  }
}

void returnToMaze() {
  readIRSensors(sensor_values);
  while (!allOut) {
    takeOneStepBack();
    readIRSensors(sensor_values);
  }
  while (allOut) {
    takeOneStepBack();
    readIRSensors(sensor_values);
  }
  //  for (int s = 0; s < 5; s++)goForward();  //   s < (TUNE-ABLE parameter);
  alignToPath(CCW);

}


void temp_debugFunctionBoxDetection(int boxColor) {
  switch (boxColor) {
    case COLOR_RED:
      lcdWrite(0, "R box");
      delay(1000);
      beep();
      lcdBoxSensorUpdate();
      delay(1000);
      return;
    case COLOR_GREEN:
      lcdWrite(0, "G box");
      delay(1000);
      return;
    case COLOR_BLUE:
      lcdWrite(0, "B box");
      delay(1000);
      beep();
      lcdBoxSensorUpdate();
      delay(1000);
      return;
    case COLOR_OPEN:
      lcdWrite(0, "No box");
      delay(1000);
      beep();
      lcdBoxSensorUpdate();
      delay(1000);
      return;
  }
}



