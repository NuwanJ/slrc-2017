/* -------------------------------------------------------------------------- -

  -------------------------------------------------------------------------- -* /

  // Contributor : Harshana
  // Last Update : 28/11/2017

  /* Remarks ------------------------------------




  ---------------------------------------------*/



//
// 02/01/2017

void mazeFollow() {
  pos = readIRSensors(sensor_values);
  error = (pos - CENTER_EDGE_READING);
  Serial.println(irLineString);

  if (sensor_values[5] > 0) {
    motorWrite(150, 150);
    delay(100);
    turnCW(-90);
    lcdWrite(0, "Maze:turn-90");
  }
  else if (arsum(sensor_values) == 0) {
    goBack();
    if (lastReading <= -15) {
      motorWrite(150, 150);
      delay(100);
      turnCW(90);
      lcdWrite(0, "Maze:turn90");
    }
    else {
      //lcdWrite(0, "Maze:turnBck");
      //turnCW(180);
    }
  }
  else if (sensor_values[0] > 0) {
    lcdWrite(0, "Maze:goFwd");
    //    goForward();
    lineFollow(); //This is wrong, remove this and uncomment goForward()
    delay(100);
  }
  else {
    lcdWrite(0, "Maze:line");
    lineFollow(); //Just one step
  }
}
