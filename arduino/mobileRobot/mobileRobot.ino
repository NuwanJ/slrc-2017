
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "define.h"

#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]

volatile int mode = BEGIN;

void setup() {

  Serial.begin(115200);
  Serial.println(">> Robot: Begin");


  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);

  //beginDebugger();
  motorsBegin();
  //irSensorsBegin();
  //colorSensorBegin();
  sonarSensorBegin();

}



void test() {

  //motorWrite(100, 100);

  Serial.print(readSonar(SONAR_1));
  Serial.print("\t");
  Serial.print(readSonar(SONAR_2));
  Serial.println();
  delay(500);
}

