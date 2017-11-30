/*---------------------------------------------------------------------------
  Functions
    
  void beginDebugger() 
  void lcdBegin()
  
  void debugger(String txt)
  void printArray(int [DEBUG_PORT | SERIAL_PORT], int* array, int length) 
  void  lcdWrite(int line, String txt)
---------------------------------------------------------------------------*/


void beginDebugger() {
  Serial3.begin(115200);

}

//-------------------------------------------------------------------------------------------------------------- Debugger
void debugger(String txt) {
  Serial3.println(txt);
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
}

//-------------------------------------------------------------------------------------------------------------- LCD Display
void lcdBegin() {
  lcd.begin(16, 2);
  lcd.print("Robot : Begin");
}

void lcdWrite(int line, String txt) {
  // Only first 16 letters will display
  lcd.setCursor(0, line); //col, ro
  lcd.print(txt);

}

