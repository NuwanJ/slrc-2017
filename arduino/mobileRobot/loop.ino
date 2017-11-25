int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {

      } else {
        delay(10);
      }
      break;


  
    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      test();
      delay(2000);

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
        Serial.println("BEGIN");
        break;

        
      case TEST:
        Serial.println("TEST");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {


}
