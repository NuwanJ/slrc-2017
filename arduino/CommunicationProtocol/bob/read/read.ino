//Receiver Code

char str;
char str2;
int ls;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  int i=0;

  fuckingEventListener2();

}

char fuckingEventListener2(){
  if (Serial1.available()) {
     //allows all serial sent to be received together
      str = Serial1.read();
      //if (str-0 < 70) ls=0;
      //else ls=1;
      //digitalWrite(LED_BUILTIN, ls);
      Serial.write(str);
      //Serial.write(ls);
  }
  if (Serial.available()) {
     //allows all serial sent to be received together
      str = Serial.read();
      //if (str-0 < 70) ls=0;
      //else ls=1;
      //digitalWrite(LED_BUILTIN, ls);
      Serial1.write(str);
      //Serial1.write(ls);
  }
  return str;
}

