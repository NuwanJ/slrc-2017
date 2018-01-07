

void releaseBall() {

  myservo.attach(9PIN_SERVO);
  servoMotor.write(SERVO_RELEASE);
  delay(1000); // Let some time to turn and release the TT Ball
  servoMotor.write(SERVO_LOAD);
  delay(1000);
  myservo.detach();

}

void shootBall( ) {

  // Turn on the spinner motor
  spinnerMotor.write(SPINNER_SHOOT);

  // Give some time to reach it's speed
  delay(1500);

  // Release a Ball from the storage
  relaeseBall();

  // Turn off the Spinner motor
  spinnerMotor.write(SPINNER_SLOW);
}

