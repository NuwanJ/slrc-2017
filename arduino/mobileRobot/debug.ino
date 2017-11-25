

void beginDebugger() {
  Serial3.begin(115200);

}

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

