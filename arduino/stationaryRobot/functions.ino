

void releaseBall() {

  servoMotor.attach(PIN_SERVO);
  servoMotor.write(SERVO_RELEASE);
  delay(1000); // Let some time to turn and release the TT Ball
  servoMotor.write(SERVO_LOAD);
  delay(1000);
  servoMotor.detach();

}

void shootBall( ) {

  // Turn on the spinner motor
  //spinnerMotor.write(SPINNER_SHOOT);

  // Give some time to reach it's speed
  delay(1500);

  // Release a Ball from the storage
  //relaeseBall();

  // Turn off the Spinner motor
  //spinnerMotor.write(SPINNER_SLOW);
}


void moveRobot(int x, int y) {

  Serial3.print("G1");
  Serial3.print("X");
  Serial3.print(x);
  Serial3.print("Y");
  Serial3.print(y);
  Serial3.println("F100"); // Suitable feed rate

  // Wait until robot finish it's rotation
  
  while(isRobotMoving()){
    delay(10);
  }
}

boolean isRobotMoving(){
// LOW = ON, HIGH = OFF
 return  (digitalRead(PIN_STEPPER_EN)==LOW);
}

/*------------------------------------------------------------------------------

G0/G00	Rapid positioning

Switch to rapid linear motion mode (seek). 
Used to get the tool somewhere quickly without cutting --- moves the machine as quickly as possible along each axis --- an axis 
which needs less movement will finish before the others, so one cannot count on the movement being a straight line.	All Grbl versions
Carbide Motion

G1/G01	Linear interpolation

Switch to linear motion at the current feed rate. Used to cut a straight line --- the interpreter will determine 
the acceleration needed along each axis to ensure direct movement from the original to the destination point at no more 
than the current Feed rate (F see below).

------------------------------------------------------------------------------*/

