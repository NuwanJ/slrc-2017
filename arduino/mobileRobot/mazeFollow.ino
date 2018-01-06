/* --------------------------------------------------------------------------
  Contributor : Gihan
  Last Update : 06/01/2018
  --------------------------------------------------------------------------*/


void mazeFollow() {

  pos = readIRSensors(sensor_values);
  error = (pos - CENTER_EDGE_READING);
  Serial.println(irLineString);

  if (sensor_values[5] == 1) {
    goForward();goForward();goForward();
    alignToPath(CW);
  }
  else if (allOut) {
    goForward();
    alignToPath(CCW);
  }
  else if (sensor_values[0] == 1) {
    goForward();
  }
  else {
    lineFollow(); //Just one step
  }
}
