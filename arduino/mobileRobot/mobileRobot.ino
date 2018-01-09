
#include <Arduino.h>

#include "define.h"

#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>
//#include <Ultrasonic.h>
#include <Servo.h>

#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]
LiquidCrystal lcd(22, 26, 36, 38, 40, 42);    //RS,EN,D4,D5,D6,D7

Servo leftServo;
Servo rightServo;

//Ultrasonic sonar0(pinTrig[0], pinEcho[0]);

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

  //leftServo.attach(18);


  ledOn(LED_RED);

  beginDebugger();
  motorBegin();
  lcdBegin();
  irSensorBegin();
  colorSensorBegin();
  sonarSensorBegin();

  ledOff(LED_RED);


  for (int i = 30; i < 130; i+=10) {
    rotateServo(LEFT, i);
    
    rotateServo(RIGHT, i);
  }

  for (int i = 130; i >30; i-=10) {
    rotateServo(LEFT, i);
    rotateServo(RIGHT, i);
  }


}

void test() {

  //readBoxColor();
  //lcdIRSensorUpdate();
  //alignToPath(CW);
  //lcdSonarUpdate();


  /*
    boolean found = isBoxFound();

    if (found) {

      // Suggestion : while (all are not same) take 5

      readBoxColor();
      if (boxColor == 1)Serial.println("R");
      else if (boxColor == 2)Serial.println("G");
      else if (boxColor == 3)Serial.println("B");
      else Serial.println("None");

      // Send the char to Stationary robot
      // Mode = WAIT_UNTIL_FEEDBACK
      // ------------------------
    } else {
      Serial.println("0");
    }

  */
  lcdBoxSensorUpdate();
  delay(500);
}
