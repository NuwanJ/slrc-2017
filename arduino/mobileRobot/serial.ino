/*---------------------------------------------------------------------------

  ---------------------------------------------------------------------------*/

/*
  -- Command Map -----------------------------------


  --------------------------------------------------
*/

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

