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

  if (!(error != previousErrors[0])) {

    if (debug == true) {
      Serial.println(irLineString);

      lcd.clear();
      lcd.setCursor(0, 1); //col, row
      lcd.print("IR: " + irLineString);
    }

    //PID Calculating
    int motorSpeed = calculatePID(error);

    //Assigning motor speeds
    int rightMotorSpeed = baseSpeed - motorSpeed;
    int leftMotorSpeed = baseSpeed + motorSpeed;

    //Remapping motor speed
    motorWrite(leftMotorSpeed, rightMotorSpeed, true);

  }

  for (int x = 9; x > 0; x--)previousErrors[x] = previousErrors[x - 1];
  previousErrors[0] = error;

}

float kP = 20, kD = 5, kI = 0.5;
//kP=18 works

int calculatePID(int error) {
  int P = error * kP;

  int I = 0;
  for (int x = 0; x < 10; x++) I += previousErrors[x];
  I *= kI;

  int D = (error - previousErrors[0]) * kD;

  /*  for (int x = 9; x > 0; x--)previousErrors[x] = previousErrors[x - 1];
    previousErrors[0] = error;*/
  /*This part is removed assuming the calculatePID() is called only from within lineFollow() */

  return (int)(P + I + D);

}





