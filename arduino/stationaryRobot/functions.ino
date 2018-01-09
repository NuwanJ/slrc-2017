
void releaseBall() {

  servoMotor.attach(PIN_SERVO);

  servoMotor.write(SERVO_RELEASE);
  delay(2000); // Let some time to turn and release the TT Ball
  servoMotor.write(SERVO_LOAD);
  delay(1000);
  servoMotor.detach();

}

void shootBall() {

  motorOn();
  delay(5000);

  //------------------------------------------------------------------- Release

  servoMotor.attach(PIN_SERVO);

  servoMotor.write(SERVO_RELEASE);
  delay(2000); // Let some time to turn and release the TT Ball
  servoMotor.write(SERVO_LOAD);
  //--------------------------------------------------------------------

  motorOff();

  delay(1000);
  servoMotor.detach();
}



void processColor(char c) {

  if (c == 'r') {
    Serial.println(">> Target : Red Box");
    moveRobot(x[RED_BOX], y[RED_BOX]);
    Serial.println(">> Shooting : Red Box");
    //shootBall();

    // Reply as done
    writeMobile("d");
    Serial.println(">> Done");

  } else if (c == 'g') {
    Serial.println(">> Target : Green Box");
    moveRobot(x[GREEN_BOX], y[GREEN_BOX]);
    Serial.println(">> Shooting : Green Box");
    //shootBall();

    // Reply as done
    writeMobile("d");
    Serial.println(">> Done");

  } else if (c == 'b') {
    Serial.println(">> Target : Blue Box");
    moveRobot(x[BLUE_BOX], y[BLUE_BOX]);
    Serial.println(">> Shooting : Blue Box");
    //shootBall();

    // Reply as done
    writeMobile("d");
    Serial.println(">> Done");
  }

}

void motorOn() {
  analogWrite(PIN_SPINNER, SPINNER_PWM);
}

void motorOff() {
  analogWrite(PIN_SPINNER, 0);
}



