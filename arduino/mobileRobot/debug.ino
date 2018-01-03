/*---------------------------------------------------------------------------
  Functions

  void beginDebugger()
  void lcdBegin()

  void debugger(String txt)
  void printArray(int [DEBUG_PORT | SERIAL_PORT], int* array, int length)
  void lcdWrite(int line, String txt)

  void lcdIRSensorUpdate()    Read and display IR sensor readings
  void lcdMotorUpdate()       Display Motor Speeds
  void lcdSonarUpdate()       Measure & display sonar readings
  ---------------------------------------------------------------------------*/


void beginDebugger() {
  Serial3.begin(9600);
  delay(50);
}

//-------------------------------------------------------------------------------------------------------------- Debugger
void debugger(String txt) {
  Serial3.println(txt);
  delay(50);
}

void printArray(int port, int* arr, int n) {

  if (port == DEBUG_PORT) {

    for (int i = 0; i < n; i++) {
      Serial3.print(arr[i]);
      if (arr[i] > 99)
        Serial3.print(" ");
      else if (arr[i] > 9 or arr[i] < 0)
        Serial3.print("  ");
      else
        Serial3.print("   ");
      if ((i + 1) % 6 == 0) Serial3.println("");
    }
    Serial3.println("");

  } else {

    for (int i = 0; i < n; i++) {
      Serial.print(arr[i]);
      if (arr[i] > 99)
        Serial.print(" ");
      else if (arr[i] > 9 or arr[i] < 0)
        Serial.print("  ");
      else
        Serial.print("   ");
      if ((i + 1) % 6 == 0) Serial.println("");
    }
    Serial.println("");
  }
  delay(50);
}

//-------------------------------------------------------------------------------------------------------------- LCD Display
void lcdBegin() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Robot : Begin..");
  delay(50);
}


void lcdWrite(int line, String txt) {
  // Only first 16 letters will display
  lcd.clear();
  lcd.setCursor(0, line); //col, row
  lcd.print(txt);

}



void lcdWriteInt(int line, int txt) {
  // Only first 16 letters will display
  lcd.clear();
  lcd.setCursor(0, line); //col, row
  lcd.print(txt);

}


void lcdIRSensorUpdate() {
  readIRSensors(sensor_values);
  //Serial.println(irLineString);
  lcd.clear();
  lcd.setCursor(0, 1); //col, row
  lcd.print("IR: " + irLineString);
  delay(20);
}

void lcdMotorUpdate() {

  String temp = "";
  lcd.clear();
  lcd.setCursor(0, 1); //col, row
  lcd.print("L:");

  lcd.setCursor(3, 1);
  lcd.print(leftSpd);

  lcd.setCursor(8, 1);
  lcd.print("R:");

  lcd.setCursor(11, 1);
  lcd.print(rightSpd);

  delay(20);
}

void lcdSonarUpdate() {

  for (int i = 0; i < 4; i++) {
    sonarDist[i] = readSonar(i);
  }

  sonarDist[0] = readSonar(0);
  sonarDist[1] = readSonar(1);

  lcd.clear();

  // Upper Right
  lcd.setCursor(10, 0);     //16-(String(sonarDist[2]).length())
  lcd.print(sonarDist[0]);
  // Lowe Right
  lcd.setCursor(10, 1);
  lcd.print(sonarDist[1]);

  sonarDist[3] = readSonar(3);
  sonarDist[4] = readSonar(4);
  // Upper Left
  lcd.setCursor(0, 0);
  lcd.print(sonarDist[3]);

  //Lower Left
  lcd.setCursor(0, 1);
  lcd.print(sonarDist[2]);

  delay(20);
}
