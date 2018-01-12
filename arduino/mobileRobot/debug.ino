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
  Serial3.println("Hello");
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

void printArray(int port, boolean arr[], int n) {
  for (int i = 0; i < n; i++) {
    Serial.print(arr[i]);
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


void lcdWrite0(int line, String txt) {
  // Only first 16 letters will display
  lcd.clear();
  lcd.setCursor(0, line); //col, row
  lcd.print(txt);

}

void lcdWrite(int line, String txt) {
  // Only first 16 letters will display
  lcd.clear();
  lcd.setCursor(0, line); //col, row
  lcd.print(txt);
  delay(15);
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
  /*
  for (int i = 0; i < 4; i++) {
    sonarDist[i] = readSonar(i);
  }

  sonarDist[2] = readSonar(2);
  sonarDist[3] = readSonar(3);

  lcd.clear();

  // Upper Right
  lcd.setCursor(10, 0);     //16-(String(sonarDist[2]).length())
  lcd.print(sonarDist[3]);
  // Lowe Right
  lcd.setCursor(10, 1);
  lcd.print(sonarDist[2]);

  sonarDist[0] = readSonar(0);
  sonarDist[1] = readSonar(1);
  // Upper Left
  lcd.setCursor(0, 0);
  lcd.print(sonarDist[0]);

  //Lower Left
  lcd.setCursor(0, 1);
  lcd.print(sonarDist[1]);

  delay(20);
  */
}


void lcdIRSharpUpdate(){

  // Reading values
  irWall_ReadSensors();

  lcd.clear();

  // Front
  lcd.setCursor(6, 0);
  lcd.print(irWall_FrontSensorHistory[0]);

  // Left - Right
  lcd.setCursor(0, 1);
  lcd.print(irWall_LeftSensorHistory[0]);
  lcd.setCursor(8, 1);
  lcd.print(irWall_RightSensorHistory[0]);

}

void lcdBoxSensorUpdate() {

  // Update latest status
  isBoxFound();

  lcd.clear();

  lcd.setCursor(0, 0); //col, row
  lcd.print("Box: ");
  lcd.print(boxFound);
  lcd.print(" (");
  lcd.print(boxSensor);
  lcd.print(")");

  lcd.setCursor(0, 1); //col, row

  if (boxFound) {
    readBoxColor();

    if (boxColor == 1) lcd.print("R ");
    else if (boxColor == 2) lcd.print("G ");
    else if (boxColor == 3) lcd.print("B ");
    else Serial.println("None");

    lcd.print(raw_blue);
    lcd.print(" ");
    lcd.print(raw_red);
    lcd.print(" ");
    lcd.print(raw_green);
  }
}
