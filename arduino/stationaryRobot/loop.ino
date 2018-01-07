
void loop() {

  // read from port 3, send to port 2:   Stationary <- GRBL   
  if (Serial3.available()) {
    int inByte = Serial3.read();

    // Reply String from GRBL
    
    //Serial2.write(inByte);
  }

  // read from port 2, send to port 3:   Mobile -> GRBL
  if (Serial2.available()) {
    int inByte = Serial2.read();

    // Incomming data need to process from here
    
    //Serial3.write(inByte);
  }
}

