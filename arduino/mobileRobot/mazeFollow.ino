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

  if (sensor_values[5] == 1) {
    motorWrite(0, 0);
    Serial.println(">>>>>>");
    Serial.println(irLineString);
    delay(1000);
    lcdWrite(0, "Maze:trnCW");
    //    delay(1000);
    alignToPath2(CW);
  }
  else if (allOut) {
    alignToPath2(CCW);
  }
  else if (sensor_values[0] > 0) {
    lcdWrite(0, "Maze:GoFwd");
    //    delay(1000);
    goForward();
  }
  else {
    lcdWrite(0, "Maze:line");
    lineFollow(); //Just one step
  }
}
