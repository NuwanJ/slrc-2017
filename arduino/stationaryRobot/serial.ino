const char* convertColorToGCode(char color) {
  //This function has to be modified to iutput G CODE

  if (color == 'r')return "RED";
  else if (color == 'g')return "GREEN";
  else return "BLUE";
}

void serialEvent() {
  //This is the communication between the UNO and the MEGA
  if (Serial.available()) {
    /*char targetColor = '\0';
      char temp = '\0';

      while ((temp = Serial.read()) != '\0')targetColor = temp;

      unsigned long time = millis();
      while (!mySerial.available() & (millis() - time < 10000)) {
      //wait
      }

      String responseFromGRBL = "";
      while (mySerial.available()) {
      responseFromGRBL = responseFromGRBL + mySerial.read();
      }
      if (0==strcmp(responseFromGRBL.c_str() , "ok")) { //strcmp return 0 when equal
      Serial.write("done");
      }
      else {
      Serial.write("error");
      }
      Serial.flush();
    */
  }
}






