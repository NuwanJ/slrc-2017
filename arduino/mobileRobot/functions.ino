/*---------------------------------------------------------------------------
  Functions

  void beep()
  void beep(int count)

  void ledOb(n)         n = [LED_GREEN, LED_RED]
  void ledOff(n)        n = [LED_GREEN, LED_RED]
  void ledBlink(n,c)    n = [LED_GREEN, LED_RED], c = count
  ---------------------------------------------------------------------------*/



//-------------------------------------------------------------------------------------------------------------- Beep
void beep() {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(DELAY_BUZZER);
  digitalWrite(PIN_BUZZER, LOW);
  delay(DELAY_BUZZER);
}

void beep(int count) {
  for (int i = 0; i < count; i++) {
    beep();
  }
}

//-------------------------------------------------------------------------------------------------------------- LED On/ Off/ Blink
void ledOn(int n) {
  digitalWrite(n, HIGH);
}

void ledOff(int n) {
  digitalWrite(n, LOW);
}

void ledBlink(int n) {
  digitalWrite(n, HIGH);
  delay(DELAY_BLINK);
  digitalWrite(n, LOW);
}

void ledBlink(int n, int count) {

  for (int i = 0; i < count; i++) {
    ledBlink(n);
    delay(DELAY_BLINK);
  }

}








//-------------------------------------------------------------------------------------------------------------- Knight Rider : Just for fun
void knightRider() {

  lcdWrite(0, "  Knight Rider");

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(irPins[i], OUTPUT);
    digitalWrite(irPins[i], LOW);
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    digitalWrite(irPins[i], HIGH);
    delay(200);
    digitalWrite(irPins[i], LOW);
  }

  for (int i = 0; i <= NUM_SENSORS; i++) {
    digitalWrite(irPins[NUM_SENSORS - i], HIGH);
    delay(200);
    digitalWrite(irPins[NUM_SENSORS - i], LOW);
  }

}

