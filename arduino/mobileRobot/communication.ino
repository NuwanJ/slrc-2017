/*
   Two mega boards communicate with each other with Serial3
*/

void shoot(int color) {
  switch (color) {
    case COLOR_RED:
      Serial3.println('r');
      break;
    case COLOR_GREEN:
      Serial3.println('g');
      break;
    case COLOR_BLUE:
      Serial3.println('b');
      break;
  }
  timeOfShootCommand = millis();
  mode = WAIT_UNTIL_FEEDBACK;

}


void SerialEvent3() {
  /*
     This happens if the stationary bot says it finished shooting
  */
  mode = RETURN_TO_MAZE;
}

