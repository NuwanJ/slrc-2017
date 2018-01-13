
#include <Arduino.h>
#include "define.h"

#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

//#include <Ultrasonic.h>

#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]
LiquidCrystal lcd(22, 26, 36, 38, 40, 42);    //RS,EN,D4,D5,D6,D7

Servo servoMotor;

volatile int mode = BEGIN;

void setup() {

  Serial.begin(115200);
  Serial.println(">> Robot: Begin...");

  pinMode(PIN_RW, OUTPUT);
  digitalWrite(PIN_RW , LOW);

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  ledOn(LED_RED);

  // Rotate to initilize position
  rotateServo(4);

  beginDebugger();
  motorBegin();
  lcdBegin();
  irSensorBegin();
  colorSensorBegin();
  sonarSensorBegin();

  ledOff(LED_RED);
  beep();

}

void test() {

}
