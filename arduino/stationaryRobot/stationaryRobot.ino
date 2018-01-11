
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#include <EEPROM.h>
#include "define.h"

Servo servoMotor;

void setup() {

  Serial.begin(115200);

  Serial2.begin(115200); // Communicate with GRBL
  Serial3.begin(9600); // Communicate with Mobile Robot

  //Basic configurations
  pinMode(PIN_STEPPER_EN, INPUT);
  pinMode(PIN_SPINNER, OUTPUT);

  // RGB Indicator Pins
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  // Motor Direction Pins
  pinMode(PIN_MA, OUTPUT);
  pinMode(PIN_MB, OUTPUT);

  analogWrite(PIN_SPINNER, 0);

  Serial.println(">> Robot : Begin");

  // Motor Direction Set
  digitalWrite(PIN_MA, LOW);
  digitalWrite(PIN_MB, HIGH);

  servoMotor.attach(PIN_SERVO);
  servoMotor.write(SERVO_LOAD);
  delay(1000);
  servoMotor.detach();

}

void test() {

  //homing();
  //moveRobot(20, 3);

}
