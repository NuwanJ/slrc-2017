

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "define.h"

#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

#include <LiquidCrystal.h>

Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]
LiquidCrystal lcd(22, 26, 36, 38, 40, 42);    //RS,EN,D4,D5,D6,D7

volatile int mode = BEGIN;


const int PIN_RW = 24;

void setup() {

  Serial.begin(115200);
  Serial.println(">> Robot: Begin");

  pinMode(PIN_RW, OUTPUT);
  digitalWrite(PIN_RW , LOW);

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  ledOn(LED_RED);
  beginDebugger();
  motorBegin();
  lcdBegin();
  irSensorBegin();
  //colorSensorBegin();
  sonarSensorBegin();

  ledOff(LED_RED);
}



void test() {

  /*motorWrite(160, 160);
  delay(500);

  motorWrite(-160, -160);
  delay(500);
  */
  
  //lcdMotorUpdate();
  //debugger("Test");
  //lcdSonarUpdate();
  lcdIRSensorUpdate();
  delay(500);
}

