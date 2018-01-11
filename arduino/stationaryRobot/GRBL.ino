

void moveRobot(int x, int y) {

  Serial2.print("G1");
  Serial2.print("X");
  Serial2.print(x);
  Serial2.print("Y");
  Serial2.print(y);
  Serial2.println("F300"); // Suitable feed rate

  // Wait until robot finish it's rotation

  while (isRobotMoving()) {
    delay(100);
  }
}

boolean isRobotMoving() {
  // LOW = ON, HIGH = OFF
  boolean r = digitalRead(PIN_STEPPER_EN);
  //Serial.println(r);
  return  (r == LOW);
}


void homing() {
  Serial.println(">> Homming Begin...");
  Serial2.println("$H");
  delay(1000);

  while (isRobotMoving()) {
    delay(100);
  }
  Serial.println(">> Homming Complete");

}

void unlock(){
   Serial2.println("$X");
}









/*------------------------------------------------------------------------------

  G0/G00  Rapid positioning

  Switch to rapid linear motion mode (seek).
  Used to get the tool somewhere quickly without cutting --- moves the machine as quickly as possible along each axis --- an axis
  which needs less movement will finish before the others, so one cannot count on the movement being a straight line. All Grbl versions
  Carbide Motion

  G1/G01  Linear interpolation

  Switch to linear motion at the current feed rate. Used to cut a straight line --- the interpreter will determine
  the acceleration needed along each axis to ensure direct movement from the original to the destination point at no more
  than the current Feed rate (F see below).

  ------------------------------------------------------------------------------*/


