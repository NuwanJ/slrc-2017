
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
  
  //beginDebugger();
  //motorsBegin();
  //irSensorsBegin();
  //colorSensorBegin();
  //sonarSensorBegin();

}



void test() {


}

