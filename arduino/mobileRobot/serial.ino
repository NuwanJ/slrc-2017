/*---------------------------------------------------------------------------

  ---------------------------------------------------------------------------*/


void serialEvent() {

  while (Serial.available()) {

    digitalWrite(LED_RED, HIGH);

    int r = Serial.read();
    char inChar = (char)r;

    //-------------------------------------------------------------------------------------------------------------- b -> debug
    if (inChar == 'b') {
      byte val = 0;
      debug = ! debug;
      EEPROM.update(debug, debug);
      Serial.print(F(">> Print\t:")); Serial.println(debug);
    }

    //-------------------------------------------------------------------------------------------------------------- t -> test
    else if (inChar == 't') {

    }

    //-------------------------------------------------------------------------------------------------------------- 2,4,5,6,7,8,9-> bluetooth mode
    else if (mode == BLUETOOTH) {

      if  (inChar == '8')motorWrite(baseSpeed, baseSpeed);
      else if (inChar == '2')motorWrite(-1 * baseSpeed, -1 * baseSpeed);
      else if (inChar == '4')motorWrite(baseSpeed, -1 * baseSpeed);
      else if (inChar == '6')motorWrite(-1 * baseSpeed, baseSpeed);
    }
    digitalWrite(LED_RED, LOW);
  }
}

void serialEvent3() {

  while (Serial3.available()) {

    digitalWrite(LED_RED, HIGH);

    int r = Serial3.read();
    char inChar = (char)r;

#ifdef LCD_SERIAL_DEBUG
    // Need to implement
    Serial.println(inChar);
    lcdWrite(0, "");
#endif

    //-------------------------------------------------------------------------------------------------------------- s -> stopvnlv ,nvxcbvxcvmxcvmcxv
    if (inChar == 's') {
      mode = BEGIN;
      motorWrite(0, 0);
    }

    //-------------------------------------------------------------------------------------------------------------- t -> test
    else if (inChar == 't') {

    }

    digitalWrite(LED_RED, LOW);
  }
}

void SerialEvent3() {
  //This happens if the stationary bot says it finished shooting

  while (Serial3.available()) {
    digitalWrite(LED_RED, HIGH);

    int r = Serial3.read();
    char inChar = (char)r;

    if (inChar == 'd') {
      mode = RETURN_TO_MAZE;
    }
  }
  delay(50);
  digitalWrite(LED_RED, LOW);
}


void shoot(int color) {

  digitalWrite(LED_RED, HIGH);

  switch (color) {
    case COLOR_RED:
      Serial3.print('r');
      break;
    case COLOR_GREEN:
      Serial3.print('g');
      break;
    case COLOR_BLUE:
      Serial3.print('b');
      break;
  }
  timeOfShootCommand = millis();
  mode = WAIT_UNTIL_FEEDBACK;

  delay(150);
  digitalWrite(LED_RED, LOW);
}


