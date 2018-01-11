//--------------------------------------------------------------
// Command Map
//--------------------------------------------------------------
// a = motor on
// b = motor off
// c = release the ball
// d = shooting (full prograss)

// h = home
// u = unlock
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

    } else if (inByte == 'u') {
      Serial.println(">> Robot : Unlock GRBL");
      unlock();

    } else if (inByte == 'h') {
      Serial.println(">> Robot : Homing GRBL");
      homing();

    } else if (inByte == 't') {
      Serial.println(">> Robot : Test");
      test();

      //------------------------------------------------------------------------------RGB

    } else if (inByte == 'R') {
      Serial.println(">> Robot : Red");
      processColor('r');

    } else if (inByte == 'K') {
      Serial.println(">> Robot : Green");
      processColor('g');

    } else if (inByte == 'B') {
      Serial.println(">> Robot : Blue");
      processColor('b');

      //------------------------------------------------------------------------------

    } else {
      // Reply String to GRBL
      Serial.write(inByte);
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
  }

  /*
    // read from port 2, send to port 3:   Mobile -> PC
    if (Serial3.available()) {
      char inByte = Serial3.read();
      // Incomming data need to process from here
      Serial.write(inByte);

      if (inByte == 'r') {
        Serial.println(">> Robot : Red");
        processColor('r');

      } else if (inByte == 'g') {
        Serial.println(">> Robot : Green");
        processColor('g');

      } else if (inByte == 'b') {
        Serial.println(">> Robot : Blue");
        processColor('b');

      }
    }
*/
    // Printing commands that come FROM the GRBL->Mega
    if (Serial2.available()) {
      char inByte = Serial2.read();
      // Incomming data need to process from here
      Serial.write(inByte);
    }
}
