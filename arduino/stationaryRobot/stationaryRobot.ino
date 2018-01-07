
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

//#include <EEPROM.h>
//#include <Wire.h>
//#include <SoftwareSerial.h>
#include "define.h"

Servo servoMotor;

void setup() {

  Serial.begin(115200);

  Serial2.begin(115200); // Communicate with Mobile Robot
  Serial3.begin(115200); // Communicate with GRBL

  //Basic configurations
  pinMode(PIN_STEPPER_EN, INPUT);

  test();
}

void test() {

  analogWrite(PIN_SPINNER, SPINNER_PWM);
  delay(1000);
  analogWrite(PIN_SPINNER, 0);

}
