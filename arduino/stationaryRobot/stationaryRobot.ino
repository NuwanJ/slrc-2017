
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

//#include <EEPROM.h>
//#include <Wire.h>
//#include <SoftwareSerial.h>
#include "define.h"

Servo servoMotor;
Servo spinnerMotor;

volatile int mode = BEGIN;

//SoftwareSerial mySerial(10, 11); // RX, TX This is the communication between the UNO and the GRBL

void setup() {
  Serial.begin(9600);

  spinnerMotor.attach(PIN_SPINNER);
  spinnerMotor.write(SPINNER_LOW);
}

void test() {

//test
}
