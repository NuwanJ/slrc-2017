// Not used in the competition

void specialShoot(int k) {

  Serial.print(">> Target : "); Serial.println(k);

  moveRobot(finalX[k], finalY[k]);

  shootBall(DEF);
  motorReverse();
  delay(3000);

  moveRobot(finalX[k] - 2, finalY[k]);
  shootBall(DEF);

  motorReverse();
  delay(3000);

  moveRobot(finalX[k] - 2, finalY[k]);
  shootBall(DEF);

  delay(3000);
}
