
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "define.h"

#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

#include <LiquidCrystal.h>

Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //RS,EN,D4,D5,D6,D7

volatile int mode = BEGIN;

void setup() {

  Serial.begin(115200);
  Serial.println(">> Robot: Begin");

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);

  //beginDebugger();
  motorBegin();
  lcdBegin();
  //irSensorBegin();
  //colorSensorBegin();
  sonarSensorBegin();
  //beginDebugger();
}



void test() {

  //motorWrite(100, 100);

  Serial.print(readSonar(SONAR_1));
  Serial.print("\t");
  Serial.print(readSonar(SONAR_2));
  Serial.println();
  delay(500);
}

