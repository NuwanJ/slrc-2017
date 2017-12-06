int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);
      //Serial.println(analogRead(A1));

      
      if (buttonStatus == 0 ) {
        mode = TEST;
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
        //lcdWrite(0,"Mode: Begin");
        break;


      case TEST:
        Serial.println("TEST");
        lcdWrite(0,"Mode: Test");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {


}
