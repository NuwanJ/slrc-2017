/* -------------------------------------------------------------------------- -

  -------------------------------------------------------------------------- -* /

  // Contributor : Harshana
  // Last Update : 28/11/2017

  /* Remarks ------------------------------------




  ---------------------------------------------*/



//
// 02/01/2017

void mazeFollow() {
  readIRSensors(sensor_values);
  Serial.println(irLineString);
  if (sensor_values[5] > 0) turnCW(-90);
  else if (arsum(sensor_values) == 0) {
    goBack();
    if (lastReading <= -15) {
      turnCW(90);
    }
    else {
      turnCW(180);
    }
  }
  else if (sensor_values[0] > 0) {
    goForward();
  }
  else {
    lineFollow(); //Just one step
  }
}
