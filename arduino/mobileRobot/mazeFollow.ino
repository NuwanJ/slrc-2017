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
    lcdWrite(0, "Maze:trnCW");
    alignToPath2(CW);
  }
  else if (arsum(sensor_values) == 0) {
    //goBack();
    if (lastReading <= -15) {
      lcdWrite(0, "Maze:trnCCW");
      alignToPath2(CCW);
    }
    else {
      lcdWrite(0, "Maze:turnBck");
      alignToPath2(CCW);
    }
  }
  else if (sensor_values[0] > 0) {
    lcdWrite(0, "Maze:GoFwd");
    goForward();
  }
  else {
    lcdWrite(0, "Maze:line");
    lineFollow(); //Just one step
  }
}
