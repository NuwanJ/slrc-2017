// Contributor : Nuwan
// Last Update : 22/12/2017

/* Remarks ------------------------------------

  Functions

  void lineFollowingBegin()
  void lineFollow()
  int calculatePID()

  ---------------------------------------------*/


void lineFollowBegin() {
  //lineType = BLACK;
}

void lineFollow() {

  pos = readIRSensors(sensor_values);
  error = (pos - CENTER_EDGE_READING);

  if (error != lastError) {

    if (debug == true) {
      Serial.println(irLineString);

      lcd.clear();
      lcd.setCursor(0, 1); //col, row
      lcd.print("IR: " + irLineString);
    }

    //PID Calculating
    int motorSpeed = calculatePID(error);

    //Assigning motor speeds
    int rightMotorSpeed = baseSpeed + motorSpeed;
    int leftMotorSpeed = baseSpeed - motorSpeed;

    //Remapping motor speed
    //motorWrite(leftMotorSpeed, rightMotorSpeed);

    lastError = error;
  }

}
int calculatePID(int error) {

  int P = error * kP;
  int I = I + (error * kI);
  int D = (error - lastError) * kD;

  lastError = error;

  return (P + I + D);

}





