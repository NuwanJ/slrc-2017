
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#include <EEPROM.h>
#include "define.h"

Servo servoMotor;

void setup() {

  Serial.begin(115200);

  Serial2.begin(115200); // Communicate with GRBL
  Serial3.begin(115200); // Communicate with Mobile Robot

  //Basic configurations
  pinMode(PIN_STEPPER_EN, INPUT);
  pinMode(PIN_SPINNER, OUTPUT);

  analogWrite(PIN_SPINNER, 0);

  Serial.println(">> Robot : Begin");

}

void test() {

  //homing();
  moveRobot(20, 3);

}
