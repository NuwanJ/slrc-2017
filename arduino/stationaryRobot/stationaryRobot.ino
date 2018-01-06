
#include <Arduino.h>
#include <SoftwareSerial.h>

//#include <EEPROM.h>
//#include <Wire.h>
//#include <SoftwareSerial.h>
#include "define.h"

volatile int mode = BEGIN;

SoftwareSerial mySerial(10, 11); // RX, TX This is the communication between the UNO and the GRBL

void setup() {
  Serial.begin(115200);
}

void test() {


}
