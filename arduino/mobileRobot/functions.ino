/*---------------------------------------------------------------------------
  Functions

  void beep()
  void beep(int count)

  void buttonRead(n)    n = [BUTTON_0,BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4]
  
  void ledOb(n)         n = [LED_GREEN, LED_RED]
  void ledOff(n)        n = [LED_GREEN, LED_RED]
  void ledBlink(n,c)    n = [LED_GREEN, LED_RED], c = count

  void knightRider()
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

//-------------------------------------------------------------------------------------------------------------- Button Read

int buttonRead(int btn) {

  if (btn == BUTTON_3 || btn == BUTTON_4) {
    return 0;//(analogRead(btn) == 0);
  } else {
    return (1 - digitalRead(btn));
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

