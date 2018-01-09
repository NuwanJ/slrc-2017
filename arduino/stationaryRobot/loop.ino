//--------------------------------------------------------------
// Command Map
//--------------------------------------------------------------
// a = motor on
// b = motor off
// c = release the ball
// d = shooting (full prograss)

// h = home
// x = unlock
// t = call test function
//--------------------------------------------------------------


void loop() {

  // read from port 0, send to port 2:   PC -> GRBL
  if (Serial.available()) {
    char inByte = Serial.read();

    if (inByte == 'a') {
      // Turn on motor
      Serial.println(">> Motor : ON");
      motorOn();

    } else if (inByte == 'b') {
      // Turn off motor
      Serial.println(">> Motor : OFF");
      motorOff();

    } else if (inByte == 'c') {
      // Release a TT Ball
      Serial.println(">> Spinner : Release");
      releaseBall();

    } else if (inByte == 'd') {
      // Shooting
      Serial.println(">> Shooting : Load");
      shootBall();

    } else if (inByte == 'x') {
      Serial.println(">> Robot : Unlock GRBL");
      unlock();

    } else if (inByte == 'h') {
      Serial.println(">> Robot : Homing GRBL");
      homing();

    } else if (inByte == 't') {      
      Serial.println(">> Robot : Test");
      test();

    } else {
      // Reply String to GRBL
      Serial2.write(inByte);
    }

  }

  // read from port 2, send to port 3:   Mobile -> Mega
  if (Serial3.available()) {
    char inByte = Serial3.read();

    // Incomming data need to process from here

    if (inByte == 'r' || inByte == 'g' || inByte == 'b') {
      Serial.println(">> Color Received");
      processColor(inByte);

    } else {
      Serial.write(inByte);
    }
    /*---------------------------------------------------------------------------
      char targetColor = '\0';
      char temp = '\0';

      while ((temp = Serial3.read()) != '\0')targetColor = temp;

      unsigned long time = millis();
      while (!mySerial.available() & (millis() - time < 10000)) {
      //wait
      }

      String responseFromGRBL = "";
      while (mySerial.available()) {
      responseFromGRBL = responseFromGRBL + mySerial.read();
      }
      if (0 == strcmp(responseFromGRBL.c_str() , "ok")) { //strcmp return 0 when equal
      Serial.write("done");
      }
      else {
      Serial.write("error");
      }
      Serial.flush();
      //---------------------------------------------------------------------------*/
  }


  // read from port 2, send to port 3:   GRBL -> PC
  if (Serial2.available()) {
    char inByte = Serial2.read();

    // Incomming data need to process from here
    Serial.write(inByte);
  }
}

